#include "hex_string.hpp"
#include<iostream>
using namespace cp;

const std::string hex_string::alphabet="0123456789ABCDEF";
const std::array<std::byte,256>& hex_string::invalpha()
{
	static std::array<std::byte,256> ia=build_invalpha();
	return ia;
}
std::array<std::byte,256> hex_string::build_invalpha()
{
	std::array<std::byte,256> ia;
	ia.fill(std::byte{0xFF});
	for(int i=0;i<10;i++)
	{
		ia[(int)('0'+i)]=static_cast<std::byte>(i);
	}
	for(int i=0;i<6;i++)
	{
		ia[(int)('a'+i)]=static_cast<std::byte>(i+10);
		ia[(int)('A'+i)]=static_cast<std::byte>(i+10);
	}
	return ia;
}

hex_string::operator bytes() const
{
	const std::array<std::byte,256>& ia=invalpha();
	bytes b(size()/2);
	size_t ci=0;
	for(size_t i=0;i<b.size();i++)
	{
		std::byte bo=ia[operator[](ci++)];
		bo <<= 4;
		bo|=ia[operator[](ci++)];
		b[i]=bo;
	}
	return b;
}
hex_string::hex_string(const bytes& b)
{
	resize(b.size()*2);
	
	for(size_t i=0;i<b.size();i++)
	{
		std::uint8_t bv=static_cast<std::uint8_t>(b[i]);
		operator[](i*2)=hex_string::alphabet[(bv >> 4) & 0xF];
		operator[](i*2+1)=hex_string::alphabet[bv & 0xF];
	}
}

hex_string::hex_string(const std::string_view& s):std::string(s)
{
	const std::array<std::byte,256>& ia=invalpha();
	bool result=(s.size() & 1)==0;
	for(unsigned int i=0;i<s.size();i++)
	{
		result=result && (ia[s[i]]!=std::byte{0xFF});
	}
	if(!result) throw std::runtime_error(std::string("'")+*this+"' is not a hex string!");
}

std::istream& cp::operator>>(std::istream& inp,hex_string& hs)
{
	std::string s;
	inp >> s;
	hs=hex_string(s);
	return inp;
}
