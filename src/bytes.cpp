#include "bytes.hpp"
#include<algorithm>
#include<sstream>
#include<cctype>
#include "hex_string.hpp"
#include<bitset>

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

static const std::string hxalpha="0123456789ABCDEF";
std::string cp::to_printable(const bytes& ba)
{
	std::ostringstream oss;
	for(auto& b:ba)
	{
		if(((char)b)=='\\') oss << "\\\\";
		else if(std::isprint((int)b)) oss << (char)b;
		else oss << "\\x" << hxalpha[static_cast<uint32_t>(b>>4)] << hxalpha[static_cast<uint32_t>(b & std::byte{0xF})];
	}
	return oss.str();
}

cp::bytes cp::from_printable(const std::string_view& sv)
{
	cp::bytes out;
	out.reserve(sv.size());

	for(size_t i=0;i<sv.size();i++)
	{
		char s=sv[i];
		if(s=='\\')
		{
			if(sv[i+1]=='\\')
			{
				out.push_back((std::byte)'\\');
			}
			else if(sv[i+1]=='x' || sv[i+1]=='X')
			{
				cp::bytes nextbyte=cp::hex_string(sv.substr(i+2,i+4));
				out.push_back(nextbyte.front());
			}
			else throw std::runtime_error("Error, improper backslash terminator in printable.");
		}
		else
		{
			out.push_back((std::byte)s);
		}
	}
	
	out.shrink_to_fit();
	return out;
}


static inline unsigned int popcnt(const size_t a)
{
	return std::bitset<sizeof(size_t)*8>(a).count();
}

unsigned int cp::popcount(const cp::bytes& b)
{
	unsigned int cnt=0;
	size_t I=b.size()/sizeof(size_t);
	const size_t* pt=reinterpret_cast<const size_t*>(b.data());
	for(size_t i=0;i<I;i++)
	{
		cnt+=popcnt(pt[i]);
	}
	size_t R=b.size() % sizeof(size_t);
	for(size_t i=0;i<R;i++)
	{
		cnt+=popcnt((size_t)b[sizeof(size_t)*I+i]);
	}
	return cnt;
}

unsigned int cp::hamming(const cp::bytes& b,const cp::bytes& a)
{
	return popcount(a ^ b);
}

