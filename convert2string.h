#pragma once
#include <string>
#include <tchar.h>
#include <Windows.h>

std::string convert2string(TCHAR * STR)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

	std::string str(chRtn);

	delete[] chRtn;

	return str;
}