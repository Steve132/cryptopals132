#include<iostream>
#include "hex_string.hpp"
#include "repeating_key.hpp"



int main(int argc,char** argv)
{
	std::string plaintext=R"RAW(Burning 'em, if you ain't quick and nimble
	I go crazy when I hear a cymbal)RAW";
	cp::bytes bytes=cp::from_printable(plaintext);
	
	cp::bytes key=cp::from_printable("ICE");
	
	cp::bytes cipher=cp::RepeatingKey::encrypt(bytes,key);
	
	std::cout << cp::to_printable(cipher) << std::endl;
	
	cp::bytes plain=cp::RepeatingKey::decrypt(cipher,key);
	
	std::cout << cp::to_printable(plain) << std::endl;
	
	return 0;
}

