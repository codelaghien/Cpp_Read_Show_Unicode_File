#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h> 

#include "HuyColors.h"  

using namespace std;
#define NULL	0     

class HuyWindows
{
	private:
		int _Left = 0;
		int _Top = 0;
		int _Width = 0;
		int _Height = 0;
		int _BackgroundColor = 0;
		int _ForegroundColor = 7;
		int _FrameNo = 0;
		wstring _Frame[2] = { L"┌─┐│└┘┬┴", L"╔═╗║╚╝╦╩" }; 
		SMALL_RECT _SrctReadRect = { 0, 0, 0, 0 };
		SMALL_RECT _SavedRect = { 0, 0, 0, 0 }; 
		CHAR_INFO* _ChiBuffer = NULL;  

	public:
		HuyWindows();
		HuyWindows(const int left, const int top, const int width, const int height, const int frameNo, const int backgroundColor = 0, const int foregroundColor = 7);
		~HuyWindows();

		void gotoXY(const int x, const int y);
		void clearConsole(const wchar_t wchar, const bool contentOnly = true);
		void clearConsole(const char ch = ' ', const bool contentOnly = true);
		void write(const string st, const int x, const int y, const int backgroundColor = -1, const int foregroundColor = -1);
		void write(const wstring st, const int x, const int y, const int backgroundColor = -1, const int foregroundColor = -1);
		void drawFrame();
		void saveScreenRect(const int x = 0, const int y = 0, const int w = 0, const int h = 0);
		void restoreScreenRect();
		void showConsoleCursor(const bool showFlag);
		void animateFrame(const int x = 0, const int y = 0, const int w = 0, const int h = 0, const int backgroundColor = -1, const int foregroundColor = -1);

		int getWidth() { return _Width; }
		int getHeight() { return _Height; } 

		static wstring toWString(const string st);
		static wstring toWString(const int i) { return to_wstring(i); }
		static wstring toWString(const double d) { return to_wstring(d); }
		static wstring toWString(const float f) { return to_wstring(f); }
};
 
