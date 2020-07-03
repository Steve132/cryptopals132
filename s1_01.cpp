#include<iostream>
#include "base64_string.hpp"
#include "hex_string.hpp"

int main(int argc,char** argv)
{
	cp::bytes z={std::byte{0xAA},std::byte{0xBB},std::byte{0xCC}};
	
	cp::base64_string b(z);
	
	cp::bytes z2(b);
		
	std::cout << cp::hex_string(z2) << std::endl;
	cp::bytes s1=cp::hex_string("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
	std::cout << cp::base64_string(s1) << std::endl;
	return 0;
}
