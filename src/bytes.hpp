#ifndef BYTES_HPP
#define BYTES_HPP

#include<cstddef>
#include<vector>
#include<array>


namespace cp
{

using bytes=std::vector<std::byte>;
std::string printable(const bytes& b);
}

cp::bytes operator^(const cp::bytes& b,const cp::bytes& a);

#endif
