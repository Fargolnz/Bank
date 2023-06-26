#include "StringHasher.h"
#include <iostream>
#include <string>
#include <openssl/evp.h>

using namespace std;

string StringHasher::hash(string plainText)
{
	string hashedPassword = sha256(plainText);

	return hashedPassword;
}

bool StringHasher::verify(string plainText, string cipheredText)
{
	string hashedPlainText = sha256(plainText);

	return hashedPlainText == cipheredText;
}

string StringHasher::sha256(string plainText)
{
	string input = plainText;
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len;

	EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
	EVP_DigestUpdate(mdctx, input.c_str(), input.length());
	EVP_DigestFinal_ex(mdctx, hash, &hash_len);
	EVP_MD_CTX_free(mdctx);

	string hashedPlainText;

	for (unsigned int i = 0; i < hash_len; i++) 
	{
		char buf[3];
		sprintf_s(buf, "%02x", hash[i]);
		hashedPlainText += buf;
	}

	return hashedPlainText;
}
