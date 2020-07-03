#include<iostream>
#include "base64_string.hpp"
#include "hex_string.hpp"

int main(int argc,char** argv)
{
	cp::bytes a=cp::hex_string("1c0111001f010100061a024b53535009181c");
	cp::bytes b=cp::hex_string("686974207468652062756c6c277320657965");
	std::cout << cp::hex_string(a ^ b) << std::endl;
	return 0;
}
