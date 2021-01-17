#include<algorithm>
#include<numeric>
#include "xor_search.hpp"
#include "verify_plaintext.hpp"
#include "key_based.hpp"

double cp::find_possible_xor_encryption(const cp::bytes& a,uint8_t& selected_key)
{
	cp::bytes z=a;
	
	cp::PlaintextVerifier pverify;
	
	std::vector<uint8_t> candidate_ids(256);
	std::iota(candidate_ids.begin(),candidate_ids.end(),0);
	
	auto score_func=[&z,&a,&pverify](uint8_t i){
		std::fill(z.begin(),z.end(),std::byte{i});
		cp::bytes result=a ^ z;
		return pverify.score(result);
	};
	
	selected_key=*key_based::max_element(candidate_ids.begin(),candidate_ids.end(),score_func);
	return score_func(selected_key);
}
