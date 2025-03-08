#pragma once

#include "KeySettings.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace msclr::interop;

ref class MacroItem
{
public:
	uint8_t keyCode = 0;
	String^ name;

public:
	virtual String^ ToString() override
	{
		return name;
	}
};

ref class PlaybackItem
{
public:
	uint8_t keyCode = 0;
	String^ name;

public:
	virtual String^ ToString() override
	{
		return name;
	}
};

String^ ConvertToManagedString(std::string str)
{
	return gcnew String(msclr::interop::marshal_as<String^>(str.c_str()));
}

String^ ConvertToManagedString(const char* charPtr)
{
	return gcnew String(msclr::interop::marshal_as<String^>(charPtr));
}

std::string ConvertToUnmanagedString(String^ managed)
{
	return marshal_as<std::string>(managed);
}

