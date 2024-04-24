#include "Log.h"

Log::Log()
{
}

Log::Log(const char* fileName)
{
	OpenFile(fileName);
}

Log::~Log()
{
	CloseFile();
}

void Log::OpenFile(const char*& fileName)
{
	fileOpen.open(fileName);

	if (!fileOpen.is_open())
	{
		Print("unknow file");
	}
}

bool CheckPrintArg(const char c)
{
	if (c == 'd' || c == 'f')
	{
		return true;
	}
	else
		return false;
}
std::string Log::Print(const std::string format,...)
{
	va_list params;
	va_start(params, format);

	int nbValue = 0;

	std::string result ="";
	for (int i = 0; i < format.length();++i)
	{
		if (format[i] == '%' && i != format.length()-1)
		{
			char c = format[i + 1];
			if (CheckPrintArg(c))
			{
				++nbValue;

				if (c == 'd')
				{
					result += std::to_string(va_arg(params, int));
				}
				else if (c == 'f')
				{
					result += std::to_string(va_arg(params, double));
				}
				
				++i;
			}
			else
			{
				std::cout << "error type arg : %" << c << std::endl;
				break;
			}

		}
		else
		{
			result += format[i];
		}
	}
	va_end(params);
	std::cout << result << std::endl;
	
	if (fileOpen.is_open())
	{
		result += "\n";
		fileOpen << result;
	}

	return result;
}


void Log::CloseFile()
{
	if (fileOpen.is_open())
	{
		fileOpen.close();
	}
}

void Debug_Log(std::string text, std::string FileName, int line, ...)
{
	Log log;
	va_list args;
	va_start(args, line);

	text = log.Print(text, args);
	text = FileName + "(" + std::to_string(line) + "): " + text;

	va_end(args);
	OutputDebugStringA(text.c_str());
}
