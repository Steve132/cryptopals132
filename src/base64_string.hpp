#ifndef BASE64_STRING_HPP
#define BASE64_STRING_HPP

#include "bytes.hpp"
#include <string_view>

namespace cp
{
	struct base64_string: public std::string
	{
	private:
		static const std::string alphabet;
		static const std::array<std::byte,256>& invalpha();
		static std::array<std::byte,256> build_invalpha();
	public:
		using std::string::operator[];
		
		operator bytes() const;
		base64_string(const bytes&);
		base64_string(const std::string_view& s="");
	};
	
	std::istream& operator>>(std::istream&,base64_string&);
	//std::ostream& operator<<(std::ostream&,const base64_string&);
}

#endif
