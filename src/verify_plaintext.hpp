#ifndef VERIFY_PLAINTEXT_HPP
#define VERIFY_PLAINTEXT_HPP

#include "bytes.hpp"
#include <memory>

namespace cp
{
class PlaintextVerifier
{
protected:
	class Impl;
	std::unique_ptr<Impl> impl;
public:
	PlaintextVerifier();
	~PlaintextVerifier();
	
	float score(const cp::bytes& b) const;
};

}

#endif
