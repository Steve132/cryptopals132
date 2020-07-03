
add_library(cryptopals132
	bytes.hpp
	bytes.cpp
	base64_string.cpp
	base64_string.hpp
	hex_string.cpp
	hex_string.hpp
	verify_plaintext.cpp
	verify_plaintext.hpp
)

target_compile_features(cryptopals132 PUBLIC cxx_std_17)
