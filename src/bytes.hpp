#ifndef BYTES_HPP
#define BYTES_HPP

#include<cstddef>
#include<vector>
#include<array>


namespace cp
{

using bytes=std::vector<std::byte>;

std::string to_printable(const bytes& b);
bytes from_printable(const std::string_view& sv);

unsigned int popcount(const bytes& a);
unsigned int hamming(const bytes& a,const bytes& b);

}

cp::bytes operator^(const cp::bytes& b,const cp::bytes& a);


#endif
