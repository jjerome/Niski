#include "utils/Log.h"
#include "utils/DataDirectory.h"

//
// What the fuck kind of name is this
#include <iostream>
#include <iomanip>
#define _CRT_SECURE_NO_WARNINGS 1

using namespace Niski::Utils;

logWriter& logWriter::getLogWriter(void)
{
	static std::wstring path;

	if (path.empty())
	{
		std::wostringstream name;
		std::time_t time = std::time(nullptr);
		DataDirectory* dir = DataDirectory::getDataDirectory();
		name << dir->getPath(L"logs") << '\\';
		name << std::put_time(std::localtime(&time), L"%Y-%m-%d");
		name << L".log";

		path = name.str();
	}

	static logWriter log(path);
	return log;
}

logWriter::logWriter(const std::wstring& filename)
{
	file_.open(filename.c_str(), std::fstream::app);

	//
	// If we fail to open the log file, 
	// there's really no other way to notify the user
	Niski::Utils::Assert(file_.is_open(), "Failed to open log file.", __FILE__, __FUNCSIG__, __LINE__);

	write(L"================ Log File Started ================", writeTimeInfo | writeNewLine);
}

logWriter::~logWriter(void)
{
	if(file_.is_open())
	{
		write(L"================ Log File Ended ================", writeTimeInfo | writeNewLine | forceFlush);

		file_.close();
	}
}

void logWriter::write(const std::wstring& message, uint16_t flags)
{
	std::wstring data;

	if(flags & writeTimeInfo)
	{
		//
		// write log information (date) before the message
		data += writeLogInformation();
	}

	data += message;

	if(flags & writeNewLine)
	{
		if(data[data.length() - 1] != '\n')
		{
			data += L'\n';
		}
	}

	//
	// Lock to write/flush
	mutex_.lock();
	{
		file_.write(data.c_str(), data.length());

		if(flags & forceFlush)
		{
			file_.flush();
		}
	}
	mutex_.unlock();

	wprintf(data.c_str());
}

std::wstring logWriter::writeLogInformation(void)
{
	std::time_t time = std::time(nullptr);
	std::tm* localTime = std::localtime(&time);

	//
	// TODO: Is wostringstream really necessary for this?
	std::wostringstream str;

	//
	// Write the current date in the format mon/day/year
	str << std::put_time(localTime, L"%d/%m/%y - %H:%M:%S ");

	return str.str();
}