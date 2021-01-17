
#include<iostream>
#include "hex_string.hpp"
#include "verify_plaintext.hpp"
#include <numeric>
#include <algorithm>
#include "key_based.hpp"

int main(int argc,char** argv)
{
	cp::bytes a=cp::hex_string("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	
	cp::bytes z=a;
	
	cp::PlaintextVerifier pverify;
	
	std::vector<uint8_t> candidate_ids(256);
	std::iota(candidate_ids.begin(),candidate_ids.end(),0);
	
	auto score_func=[&z,&a,&pverify](uint8_t i){
		std::fill(z.begin(),z.end(),std::byte{i});
		cp::bytes result=a ^ z;
		return pverify.score(result);
	};
	
	uint8_t selected_key=*key_based::max_element(candidate_ids.begin(),candidate_ids.end(),score_func);
	
	std::fill(z.begin(),z.end(),std::byte{selected_key});
	cp::bytes result=a ^ z;
	std::cout << selected_key << ": " << cp::to_printable(result) << std::endl;
	
	return 0;
}

/*
 * 	
 f or*(unsigned int i=0;i<256;i++)
 {
 std::fill(z.begin(),z.end(),std::byte{i});
 cp::bytes result=a ^ z;
 float sc=pverify.score(result);
 scores[i]=sc;
 }
 
 std::vector<size_t> scores_id(256);
 std::iota(scores_id.begin(),scores_id.end(),0);
 std::sort(scores_id.begin(),scores_id.end(),[&scores](size_t a,size_t b)
 {
 return scores[a] < scores[b];
 });*/
