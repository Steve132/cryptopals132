#include "base64_string.hpp"
using namespace cp;

const std::string base64_string::alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const std::array<std::byte,256>& base64_string::invalpha()
{
	static std::array<std::byte,256> ia=build_invalpha();
	return ia;
}
std::array<std::byte,256> base64_string::build_invalpha()
{
	std::array<std::byte,256> ia;
	ia.fill(std::byte{0xFF});
	ia[(int)'=']=static_cast<std::byte>(0);
	for(size_t i=0;i<base64_string::alphabet.size();i++)
	{
		ia[(int)base64_string::alphabet[i]]=(std::byte)i;
	}
	return ia;
}

base64_string::operator bytes() const
{
	size_t num_chars=std::string::size();
	num_chars-=(*std::string::crbegin()=='=') ? 1 : 0;
	num_chars-=(*(std::string::crbegin()+1)=='=') ? 1 : 0;
	
	size_t num_bytes=(num_chars*3)/4;
	
	bytes b(num_bytes);
	const std::array<std::byte,256>& ia=invalpha();
	size_t ci=0;
	
	for(size_t i=0;i<num_bytes;i+=3)
	{
		uint32_t v=0;
		for(size_t c=0;c<4;c++)
		{
			v<<=6;
			v|=(uint32_t)ia[operator[](ci++)] & 0x3F;
		}
		for(size_t bi=0;bi<3;bi++)
		{
			b[i+bi]=static_cast<std::byte>((v>>(8*(2-bi))) & 0xFF);
		}
	}
	return b;
}

base64_string::base64_string(const bytes& b)
{
	size_t num_groups=b.size()/3;
	size_t brem=b.size() % 3;
	size_t num_characters=num_groups*4;
	if(b.size() % 3) num_characters+=4;
	
	resize(num_characters,'=');

	size_t i;
	for(i=0;i<num_groups;i++)
	{
		uint32_t v=0;
		for(size_t bi=0;bi<3;bi++)
		{
			v|=((uint32_t)b[i*3+bi]);
			v<<=8;
		}
		for(size_t ci=0;ci<4;ci++)
		{
			int index=(v >> (6*(3-ci)+8)) & 0x3F;
			operator[](4*i+ci)=base64_string::alphabet[index];
		}
	}
	if(brem)
	{
		uint32_t v=0;
		for(size_t bi=0;bi<brem;bi++)
		{
			v|=((uint32_t)b[i*3+bi]);
			v<<=8;
		}
		for(size_t ci=0;ci<(1+brem);ci++)
		{
			int index=(v >> (6*(3-ci)+8)) & 0x3F;
			operator[](4*i+ci)=base64_string::alphabet[index];
		}
	}
}

base64_string::base64_string(const std::string_view& s):std::string(s)
{
	const std::array<std::byte,256>& ia=invalpha();
	bool result=(s.size() % 4)!=1;
	for(unsigned int i=0;i<s.size();i++)
	{
		result=result && (ia[s[i]]!=std::byte{0xFF});
	}
	if(!result) throw std::runtime_error(std::string("'")+*this+"' is not a base64 string!");
}

std::istream& cp::operator>>(std::istream& inp,base64_string& hs)
{
	std::string s;
	inp >> s;
	hs=base64_string(s);
	return inp;
}

