
add_library(cryptopals132
	bytes.hpp
	bytes.cpp
	base64_string.cpp
	base64_string.hpp
	hex_string.cpp
	hex_string.hpp
	verify_plaintext.cpp
	verify_plaintext.hpp
	repeating_key.cpp
	repeating_key.hpp
	xor_search.cpp
	xor_search.hpp
)

target_compile_features(cryptopals132 PUBLIC cxx_std_17)
