// GetProductVersion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#pragma comment(lib, "version.lib")

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

	VS_FIXEDFILEINFO *fileinfo;
	UINT fileinfolength;
	if (!VerQueryValueA(data, "\\", (void**)&fileinfo, &fileinfolength))
	{
		std::cout << "Could not get file version info from " << argv[1] << std::endl;
		return 253;
	}

	std::cout << (fileinfo->dwProductVersionMS >> 16) << "." << (fileinfo->dwProductVersionMS & 0xffff) << std::endl;

    return 0;
}

