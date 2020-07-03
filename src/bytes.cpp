#include "bytes.hpp"
#include<algorithm>
#include<sstream>
#include<cctype>

template<class Func>
static cp::bytes pointwise_binary(Func f,const cp::bytes& a,const cp::bytes& b)
{
	if(a.size() != b.size()) throw std::runtime_error("Sizes are not the same");
	cp::bytes c(a.size());
	std::transform(a.cbegin(),a.cend(),b.cbegin(),c.begin(),f);
	return c;
}

cp::bytes operator^(const cp::bytes& a,const cp::bytes& b)
{
	return pointwise_binary([](const std::byte& ab,const std::byte& bb)
	{
		return ab ^ bb;
	},a,b);
}

std::string cp::printable(const bytes& ba)
{
	static const std::string hxalpha="0123456789ABCDEF";
	std::ostringstream oss;
	for(auto& b:ba)
	{
		if(std::isprint((int)b)) oss << (char)b;
		else oss << "\\x" << hxalpha[static_cast<uint32_t>(b>>4)] << hxalpha[static_cast<uint32_t>(b & std::byte{0xF})];
	}
	return oss.str();
}
