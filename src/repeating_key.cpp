#include "repeating_key.hpp"
#include "xor_search.hpp"
#include <algorithm>
#include <numeric>
#include "key_based.hpp"

using namespace std;


cp::bytes cp::RepeatingKey::encrypt(const cp::bytes& plaintext,const cp::bytes& key)
{
	cp::bytes ciphertext=plaintext;
	size_t ki=0;
	for(std::byte& b : ciphertext)
	{
		b ^= key[ki++];
		if(ki>=key.size()) ki=0;
	}
	return ciphertext;
}
cp::bytes cp::RepeatingKey::decrypt(const cp::bytes& ciphertext,const cp::bytes& key)
{
	return encrypt(ciphertext,key);
}






static double normalized_hamming(const cp::bytes& a,size_t ksize)
{
	cp::bytes prev(a.begin(),a.begin()+ksize);
	
	double tot=0;
	
	size_t N=(a.size()/ksize);
	if(N > 8) N=8;
	for(size_t si=1;si<(N-1);si++)
	{
		cp::bytes cur(a.begin()+si*ksize,a.begin()+si*ksize+ksize);
		tot+=cp::hamming(cur,prev);
		prev=cur;
	}
	return tot/(ksize*(N));
}
static std::vector<size_t> select_keysize_candidates(const cp::bytes& a,size_t n,size_t m)
{
	std::vector<size_t> candidates(m);
	std::iota(candidates.begin(),candidates.end(),2);
	
	//key_based::nth_element(candidates.begin(),candidates.begin()+n,candidates.end(),
	//	[&a](size_t ks){ return normalized_hamming(a,ks); });
	
	key_based::sort(candidates.begin(),candidates.end(),
					[&a](size_t ks){ return normalized_hamming(a,ks); });
	
	
	candidates.resize(n);
	return candidates;
}

static std::vector<cp::bytes> transpose(const cp::bytes& f,size_t ksize)
{
	size_t chunksize=f.size()/ksize;
	
	std::vector<cp::bytes> out_transposed(ksize);
	for(cp::bytes& bo : out_transposed) 
	{
		bo.reserve(chunksize);
	}
	for(size_t i=0;i<f.size();i++)
	{
		out_transposed[i % ksize].push_back(f[i]);
	}
	return out_transposed;
}


std::vector<cp::bytes> cp::RepeatingKey::crack(cp::bytes& ciphertext)
{
	std::vector<size_t> key_sizes=select_keysize_candidates(ciphertext,10,40);
	std::vector<cp::bytes> out_bests;
	for(size_t potential_size:key_sizes)
	{
		std::vector<cp::bytes> transposed=transpose(ciphertext,potential_size);
		cp::bytes key(potential_size);
		double sc_tot=0.0;
		for(size_t tbi=0;tbi<potential_size;tbi++)
		{
			uint8_t kpb;
			double sc=find_possible_xor_encryption(transposed[tbi],kpb);
			key[tbi]=(std::byte)kpb;
			sc_tot+=sc;
		}
		out_bests.push_back(key);
	}
	return out_bests;
}
