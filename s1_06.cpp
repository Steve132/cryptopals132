#include<iostream>
#include "hex_string.hpp"
#include "repeating_key.hpp"
#include "key_based.hpp"
#include <fstream>
#include <iterator>
#include <sstream>
#include "base64_string.hpp"



int main(int argc,char** argv)
{
	std::cout << "The hamming distance is: " << 
		cp::hamming(cp::from_printable("wokka wokka!!!"),cp::from_printable("this is a test"))
		<< std::endl;
		
	std::ifstream inputfile("../data/6.txt");
	std::ostringstream oss;
	oss << inputfile.rdbuf();
	cp::bytes input=cp::base64_string(oss.str());
	

	std::vector<cp::bytes> possibilities=cp::RepeatingKey::crack(input);
	
	for(const cp::bytes& key : possibilities)
	{
		cp::bytes ref=cp::RepeatingKey::decrypt(input,key);
		std::cout << "k: " << cp::to_printable(key) << std::endl;
		std::cout << "pt: " << cp::to_printable(ref) << std::endl;
	}

	return 0;
}

