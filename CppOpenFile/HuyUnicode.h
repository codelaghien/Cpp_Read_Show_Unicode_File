#pragma once
#include <windows.h>
#include <locale> 
 
using namespace std;
using unicode = typename wchar_t;

#define MAX_LENGTH	200 
#define EOL			'\0'  

class HuyUnicode
{ 
	public:
		static wstring ReadString();
		static void ReadString(unicode* var);
		static void ReadString(const unicode* subject, unicode* var);
		static void ReadString(const char* subject, unicode* var);
		static void WriteString(const unicode* string);
		static void WriteString(const char* string);
		static void WriteString(const wstring string);
		static int ReadInt();

		static int Size(const unicode* string);
		static int Size(const char* string);

		static void AppendString(unicode* left_string, const unicode* right_string);
		static void AppendString(unicode* left_string, const char* right_string);
		static void StringToUnicode(const char* string, unicode* var); 
		static wstring StringToWString(const string& s);
};

