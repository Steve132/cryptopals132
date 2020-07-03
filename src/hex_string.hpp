#ifndef HEX_STRING_HPP
#define HEX_STRING_HPP

#include "bytes.hpp"
#include <string_view>

namespace cp
{
	struct hex_string: public std::string
	{
	private:
		static const std::string alphabet;
		static const std::array<std::byte,256>& invalpha();
		static std::array<std::byte,256> build_invalpha();
	public:
		using std::string::operator[];

		operator bytes() const;
		hex_string(const bytes&);
		hex_string(const std::string_view& s="");
	};
	
	std::istream& operator>>(std::istream&,hex_string&);
	//std::ostream& operator<<(std::ostream&,const hex_string&);
}

#endif
