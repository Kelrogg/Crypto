#pragma once

#include <fstream>
#include <string>

class FileOutputStream
{
public:
	FileOutputStream(const std::string& filePath);

	void WriteByte(uint8_t data);

	void WriteBlock(const void* srcData, std::streamsize size);

private:
	std::ofstream m_stream;
};
