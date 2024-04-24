#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>
#include <stdarg.h>

#include <Windows.h>

#define DEBUG_LOG(txt,...)(Debug_Log(txt,__FILE__, __LINE__,__VA_ARGS__)

class Log
{
public:
	static bool openOnce;

	Log();
	Log(const char* fileName);
	~Log();

	void OpenFile(const char* & filename);
	std::string Print(const std::string format, ...);
	std::string StrReorganization(const std::string format, va_list params);

private:

	std::fstream fileOpen;
	void CloseFile();
};

void Debug_Log(std::string text, std::string FileName, int line, ...);