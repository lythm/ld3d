#pragma once

#include <boost/lexical_cast.hpp>

namespace ld3d
{
	class Logger
	{
	public:

		Logger(std::function<void (const std::string& log)> io = std::function<void (const std::string&)>())
		{
			_write = io;
		}
		virtual ~Logger(void){}

		template<typename T>
		Logger&															operator<<(const T& value)
		{
			print(boost::lexical_cast<std::string>(value));
			return *this;
		}
#if defined(_WIN32)
		template<>
		Logger& operator<< <bool>(const bool& value)
		{
			value ? print("true") : print("false");
			return *this;
		}
#endif
	private:
		void															print(const std::string& str)
		{
			_write ? _write(str) : (void)0;
		}
	private:
		std::function<void (const std::string& log)>					_write;
	};
    
#ifdef __APPLE__
    template<>
    Logger& Logger::operator<< <bool>(const bool& value)
    {
        value ? print("true") : print("false");
        return *this;
    }
#endif


}