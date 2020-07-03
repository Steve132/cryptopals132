#include "verify_plaintext.hpp"
#include <cctype>
#include <algorithm>
using namespace cp;

static bool isprintable(const cp::bytes& ba)
{
	bool result=true;
	for(auto& b:ba)
	{
		result=result && std::isprint ((char)b);
	}
	return result;
}

class cp::PlaintextVerifier::Impl
{
public:
	
	std::array<std::uint8_t,256> table;
	Impl()
	{
		uint8_t c=0;
		std::fill(std::begin(table),std::end(table),0xFF);
		for(int i=0;i<256;i++)
		{
			if(std::isprint(i) && table[std::tolower(i)]==0xFF) 
			{
				table[std::tolower(i)]=c++;
			}
		}
	}
	template<class Iter>
	double variance(Iter be,Iter ed) const {
		size_t n=(ed-be);
		if(n == 0)
			return 0.0;
		double sum = 0;
		double sq_sum = 0;
		for(size_t i = 0; i < n; ++i) {
			double a = static_cast<double>(table[(uint8_t)(*be++)]);
			sum += a;
			sq_sum += a * a;
		}
		double mean = sum / n;
		double v= sq_sum / n - mean * mean;
		return v;
	}
	float score(const cp::bytes& b) const
	{
		return std::count_if(b.begin(),b.end(),[](std::byte a) { return std::isalpha((int)a);});
		//if(!isprintable(b)) return -1000.0;
		//return variance(b.cbegin(),b.cend());
	}
};
	

PlaintextVerifier::PlaintextVerifier():impl(new Impl)
{}
PlaintextVerifier::~PlaintextVerifier()
{}
	
float PlaintextVerifier::score(const cp::bytes& b) const
{
	return impl->score(b);
}

