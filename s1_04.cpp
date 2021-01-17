#include<iostream>
#include<fstream>
#include "hex_string.hpp"
#include "verify_plaintext.hpp"
#include <algorithm>
#include "key_based.hpp"
#include <iterator>
#include "xor_search.hpp"


int main(int argc,char** argv)
{
	std::ifstream inputfile("../data/s01_04.txt");
	
	std::vector<cp::bytes> all_tests(
		(std::istream_iterator<cp::hex_string>(inputfile)),
		std::istream_iterator<cp::hex_string>());
		
	key_based::sort(all_tests.begin(),all_tests.end(),
			[](const cp::bytes& b) { 
				uint8_t sk; return 
				cp::find_possible_xor_encryption(b,sk);
			});
	for(const cp::bytes& found_encoded : all_tests)
	{
		uint8_t selected_key;
		cp::find_possible_xor_encryption(found_encoded,selected_key);
		cp::bytes z(found_encoded.size(),std::byte{selected_key});
		cp::bytes result=found_encoded ^ z;
		std::cout << (int)selected_key << ": " << cp::to_printable(result) << std::endl;
	}
	
	return 0;
}

