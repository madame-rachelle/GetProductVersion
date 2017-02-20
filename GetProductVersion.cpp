// GetProductVersion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>

#pragma comment(lib, "version.lib")

struct LANGANDCODEPAGE
{
	WORD wLanguage;
	WORD wCodePage;
};

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "GetProductVersion.exe <executable>" << std::endl;
		return 255;
	}

	char data[16 * 1024];
	if (!GetFileVersionInfoA(argv[1], 0, 16 * 1024, data))
	{
		std::cout << "Could not get file version info from " << argv[1] << std::endl;
		return 254;
	}

	LANGANDCODEPAGE *lpTranslate;
	UINT cbTranslate;
	if (!VerQueryValueA(data, "\\VarFileInfo\\Translation", (void**)&lpTranslate, &cbTranslate))
	{
		std::cout << "Could not get file version info from " << argv[1] << std::endl;
		return 253;
	}

	for (size_t i = 0; i < (cbTranslate / sizeof(struct LANGANDCODEPAGE)); i++)
	{
		char bull[1024];
		sprintf_s(bull, "\\StringFileInfo\\%04x%04x\\ProductVersion", lpTranslate[i].wLanguage, lpTranslate[i].wCodePage);

		char *str;
		UINT strlen;
		if (!VerQueryValueA(data, bull, (void**)&str, &strlen))
		{
			std::cout << "Could not get file version info from " << argv[1] << std::endl;
			return 253;
		}
		std::cout << str << std::endl;
		break;
	}

	/*
	VS_FIXEDFILEINFO *fileinfo;
	UINT fileinfolength;
	if (!VerQueryValueA(data, "\\", (void**)&fileinfo, &fileinfolength))
	{
		std::cout << "Could not get file version info from " << argv[1] << std::endl;
		return 253;
	}
	std::cout << (fileinfo->dwProductVersionMS >> 16) << "." << (fileinfo->dwProductVersionMS & 0xffff) << std::endl;
	*/

    return 0;
}

