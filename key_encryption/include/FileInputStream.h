#pragma once

#include <fstream>
#include <string>

class FileInputStream
{
public:
	FileInputStream(const std::string& filePath);

	bool IsEOF() const;

	uint8_t ReadByte();

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size);

private:

	mutable std::ifstream m_stream;
};
