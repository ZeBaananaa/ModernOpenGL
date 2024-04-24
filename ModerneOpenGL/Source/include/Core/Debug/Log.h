#pragma once
#include <filesystem>

class Log
{
public:
	Log();
	~Log();

private:
	void OpenFile(std::filesystem::path const& filename);
	void Print(const char* format); // variadique todo
};