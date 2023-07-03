#pragma once
#include <string>

class StringHasher
{
public:

	// Transforms the given string to its hashed form.
	std::string hash(std::string plainText);

	// Checks whether the given password is the same as the saved password.
	bool verify(std::string plainText, std::string cipheredText);

private:
	std::string sha256(std::string plainText);
};