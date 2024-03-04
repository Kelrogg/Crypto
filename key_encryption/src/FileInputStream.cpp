#include "FileInputStream.h"

FileInputStream::FileInputStream(const std::string& filePath)
	: m_stream(filePath, std::ios::binary)
{
	if (!m_stream.is_open())
	{
		throw std::runtime_error("Failed to open file '" + filePath + "'.");
	}
}

bool FileInputStream::IsEOF() const
{
	if (m_stream.bad())
	{
		throw std::ios::failure("Unable to check end of file: Stream is in unrecoverable bad state");
	}

	m_stream.peek();
	return m_stream.eof();
}

uint8_t FileInputStream::ReadByte()
{
	if (!m_stream)
	{
		throw std::ios::failure("Unable to read byte: Stream is in failure state");
	}

	return static_cast<uint8_t>(m_stream.get());
}

std::streamsize FileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (dstBuffer == nullptr)
	{
		throw std::invalid_argument("Destination buffer pointer is nullptr");
	}

	return m_stream.read(reinterpret_cast<char*>(dstBuffer), size).gcount();
}