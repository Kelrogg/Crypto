#include <iostream>
#include "mod_math_lib.h"
#include "CaesarCryptography.h"

constexpr size_t BufferSize = 10000;

CaesarCryptography::CaesarCryptography(int mod, const std::string& key)
	: m_mod(mod)
	, m_key(key)
{
}

void CaesarCryptography::Encrypt(FileInputStream& input, FileOutputStream& output, bool decrypt)
{
	uint8_t* block = new uint8_t[BufferSize]();
	std::streamsize readSize = 1;

	while (!input.IsEOF() && readSize)
	{
		readSize = input.ReadBlock(block, BufferSize);

		if (decrypt)
		{
			DecryptBlock(block, readSize);
		}
		else
		{
			EncryptBlock(block, readSize);
		}

		output.WriteBlock(block, readSize);
	}

	delete[] block;
}

void CaesarCryptography::EncryptBlock(uint8_t* block, size_t size)
{
	for (size_t i = 0; i < size; ++i, m_k = ++m_k % m_key.size())
	{
		block[i] = mod_add(block[i], m_key[m_k], m_mod);
	}
}

void CaesarCryptography::DecryptBlock(uint8_t* block, size_t size)
{
	for (size_t i = 0; i < size; ++i, m_k = ++m_k % m_key.size())
	{
		block[i] = mod_sub(block[i], m_key[m_k], m_mod);
	}
}
