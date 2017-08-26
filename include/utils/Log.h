#ifndef __UTILS_LOG_H__
#define __UTILS_LOG_H__

#include <fstream>
#include <sstream>
#include <cstdint>
#include <mutex>
#include "utils/Assert.h"
#include "utils/Helpers.h"

namespace Niski
{
	namespace Utils
	{
		class logWriter
		{
		public:
			enum options
			{
				writeTimeInfo = 1,
				writeNewLine,
				forceFlush,
			};

		public:
			static logWriter& getLogWriter(void);

		public:
			logWriter(const std::wstring& filename);
			~logWriter(void);

			void write(const std::wstring& message, uint16_t flags);

		private:
			std::wstring writeLogInformation(void);

		private:
			std::wofstream file_;
			std::mutex mutex_;
		};

		//
		// General information content (hardware, operating system information, etc)
		void inline information(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[Info] " << message.c_str();

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// General information content (hardware, operating system information, etc)
		void inline information(const std::wstring& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[Info] " << message;

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// A less serious warning - typically means the program has
		// solved the problem, but you should be aware of it
		void inline bitch(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[Bitch] " << message.c_str();

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// A less serious warning - typically means the program has
		// solved the problem, but you should be aware of it
		void inline bitch(const std::wstring& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[Bitch] " << message;

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// A warning - things might get messed up because the program
		// attempted to solve a problem that isn't obvious
		void inline warning(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[Warning] " << message.c_str();

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// A warning - things might get messed up because the program
		// attempted to solve a problem that isn't obvious
		void inline warning(const std::wstring& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[Warning] " << message;

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// SNAFU
		void inline error(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();


			std::wostringstream data;
			data << L"[Error] " << message.c_str();

			//
			// TODO: Should we be forcing a flush to the disk or hope a FATAL happens?
			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// SNAFU
		void inline error(const std::wstring& message)
		{
			logWriter& log = logWriter::getLogWriter();


			std::wostringstream data;
			data << L"[Error] " << message;

			//
			// TODO: Should we be forcing a flush to the disk or hope a FATAL happens?
			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// FUBAR
		void inline fatal(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[FATAL] " << message.c_str();

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine | logWriter::forceFlush);
		}

		//
		// FUBAR
		void inline fatal(const std::wstring& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::wostringstream data;
			data << L"[FATAL] " << message;

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine | logWriter::forceFlush);
		}
	}
}

#endif