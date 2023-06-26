#pragma once
#include <string>

class StringHasher
{
public:
	std::string hash(std::string plainText);
	bool verify(std::string plainText, std::string cipheredText);

private:
	std::string sha256(std::string plainText);
};