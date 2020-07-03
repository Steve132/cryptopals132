#include<iostream>
#include<fstream>
#include "hex_string.hpp"
#include "verify_plaintext.hpp"
#include <algorithm>
#include "key_based.hpp"
#include <iterator>

double find_possible_xor_encryption(const cp::bytes& a,uint8_t& selected_key)
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

int main(int argc,char** argv)
{
	system("pwd");
	std::ifstream inputfile("../data/s01_04.txt");
	
	std::vector<cp::bytes> all_tests(
		(std::istream_iterator<cp::hex_string>(inputfile)),
		std::istream_iterator<cp::hex_string>());
		
	key_based::sort(all_tests.begin(),all_tests.end(),
			[](const cp::bytes& b) { 
				uint8_t sk; return 
				find_possible_xor_encryption(b,sk);
			});
	for(const cp::bytes& found_encoded : all_tests)
	{
		uint8_t selected_key;
		find_possible_xor_encryption(found_encoded,selected_key);
		cp::bytes z(found_encoded.size(),std::byte{selected_key});
		cp::bytes result=found_encoded ^ z;
		std::cout << (int)selected_key << ": " << cp::printable(result) << std::endl;
	}
	
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
