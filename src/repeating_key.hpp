#ifndef REPEATING_KEY_HPP
#define REPEATING_KEY_HPP

#include"bytes.hpp"

namespace cp
{
class RepeatingKey
{
public:
	static cp::bytes encrypt(const cp::bytes& plaintext,const cp::bytes& key);
	static cp::bytes decrypt(const cp::bytes& ciphertext,const cp::bytes& key);
	
	static std::vector<cp::bytes> crack(cp::bytes& ciphertext);
};	
	
};

#endif
