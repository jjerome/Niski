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
			logWriter(const std::string& filename);
			~logWriter(void);

			void write(const std::string& message, uint16_t flags);

		private:
			std::string writeLogInformation(void);

		private:
			std::ofstream file_;
			std::mutex mutex_;
		};

		//
		// General information content (hardware, operating system information, etc)
		void inline information(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::ostringstream data;
			data << "[Info] " << message;

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// A less serious warning - typically means the program has
		// solved the problem, but you should be aware of it
		void inline bitch(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::ostringstream data;
			data << "[Bitch] " << message;

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// A warning - things might get messed up because the program
		// attempted to solve a problem that isn't obvious
		void inline warning(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::ostringstream data;
			data << "[Warning] " << message;

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// SNAFU
		void inline error(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();


			std::ostringstream data;
			data << "[Error] " << message.c_str();

			//
			// TODO: Should we be forcing a flush to the disk or hope a FATAL happens?
			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine);
		}

		//
		// FUBAR
		void inline fatal(const std::string& message)
		{
			logWriter& log = logWriter::getLogWriter();

			std::ostringstream data;
			data << "[FATAL] " << message.c_str();

			log.write(data.str(), logWriter::writeTimeInfo | logWriter::writeNewLine | logWriter::forceFlush);
		}
	}
}

#endif