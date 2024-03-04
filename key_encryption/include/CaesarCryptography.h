#pragma once

#include <string>
#include "FileInputStream.h"
#include "FileOutputStream.h"

class CaesarCryptography
{
public:
	CaesarCryptography(int mod, const std::string& key);

	void Encrypt(FileInputStream& input, FileOutputStream& output, bool decrypt = false);

private:
	void EncryptBlock(uint8_t* block, size_t size);
	void DecryptBlock(uint8_t* block, size_t size);

	std::string m_key;
	int m_mod;
	uint8_t m_k = 0;
};
