#include "FileOutputStream.h"

FileOutputStream::FileOutputStream(const std::string& filePath)
	: m_stream(filePath, std::ios::binary)
{
	if (!m_stream.is_open())
	{
		throw std::runtime_error("Failed to open file '" + filePath + "'.");
	}
}

void FileOutputStream::WriteByte(uint8_t data)
{
	m_stream.put(data);
}

void FileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	if (srcData == nullptr)
	{
		throw std::invalid_argument("Source data buffer pointer is nullptr");
	}

	m_stream.write(reinterpret_cast<const char*>(srcData), size);
}
