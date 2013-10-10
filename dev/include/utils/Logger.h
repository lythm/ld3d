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
		template<>
		Logger&															operator<<(const bool& value)
		{
			value ? print("true") : print("false");
			return *this;
		}


	private:
		void															print(const std::string& str)
		{
			_write ? _write(str) : (void)0;
		}
	private:
		std::function<void (const std::string& log)>					_write;
	};


}