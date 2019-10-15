#include "LewisException.h"
#include <sstream>


LewisException::LewisException( int line,const char* file ) noexcept
	:
	line( line ),
	file( file )
{}

const char* LewisException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* LewisException::GetType() const noexcept
{
	return "Lewis Exception";
}

int LewisException::GetLine() const noexcept
{
	return line;
}

const std::string& LewisException::GetFile() const noexcept
{
	return file;
}

std::string LewisException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}