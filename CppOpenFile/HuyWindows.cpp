#include "HuyWindows.h"  

HuyWindows::HuyWindows() : HuyWindows(0, 0, 0, 0, 0, 0, 0) {
}
HuyWindows::HuyWindows(const int left, const int top, const int width, const int height, const int frameNo, const int backgroundColor, const int foregroundColor)
{
	_Left = left;
	_Top = top;
	_Width = width;
	_Height = height;
	_BackgroundColor = backgroundColor;
	_ForegroundColor = foregroundColor;
	_FrameNo = frameNo == 0 || frameNo == 1 ? frameNo : 0;  
}
HuyWindows::~HuyWindows()
{ 
	if (_ChiBuffer != NULL) delete _ChiBuffer; 
} 
void HuyWindows::drawFrame()
{ 
	write(_Frame[_FrameNo].substr(0, 1), 0, 0, _BackgroundColor, _ForegroundColor);
	for (int i = 0; i < _Width - 2; i++)
	{
		write(_Frame[_FrameNo].substr(1, 1), 1 + i, 0, _BackgroundColor, _ForegroundColor);
	}
	write(_Frame[_FrameNo].substr(2, 1), _Width - 1, 0, _BackgroundColor, _ForegroundColor);

	for (int i = 1; i < _Height - 1; i++)
	{
		write(_Frame[_FrameNo].substr(3, 1), 0, i, _BackgroundColor, _ForegroundColor);
		write(_Frame[_FrameNo].substr(3, 1), _Width - 1, i, _BackgroundColor, _ForegroundColor);
	}

	write(_Frame[_FrameNo].substr(4, 1), 0, _Height - 1, _BackgroundColor, _ForegroundColor);
	for (int i = 0; i < _Width - 2; i++)
	{
		write(_Frame[_FrameNo].substr(1, 1), 1 + i, _Height - 1, _BackgroundColor, _ForegroundColor);
	}
	write(_Frame[_FrameNo].substr(5, 1), _Width - 1, _Height - 1, _BackgroundColor, _ForegroundColor); 
}
wstring HuyWindows::toWString(const string st)
{
	using convert_t = std::codecvt_utf8<wchar_t>;
	wstring_convert<convert_t, wchar_t> strconverter;
	return strconverter.from_bytes(st);
}
void HuyWindows::write(const wstring st, const int x, const int y, const int backgroundColor, const int foregroundColor) {
	if (y > _Height - 1) return;

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int stringlen = st.length();
	int new_x = x < 0 ? 1 : x;
	if (new_x + stringlen > _Width) stringlen = _Width - new_x - 1;
	if (stringlen < 1) return;
	const wchar_t* text = st.c_str();
	CHAR_INFO* consoletext = new CHAR_INFO[stringlen];
	COORD a = { stringlen, 1 }, b = { 0, 0 };
	SMALL_RECT c = { _Left + new_x, _Top + y, _Left + new_x + stringlen, _Top + y + 1 };
	WORD wColor = (((backgroundColor == -1 ? _BackgroundColor : backgroundColor) & 0x0F) << 4) + ((foregroundColor == -1 ? _ForegroundColor : foregroundColor) & 0x0F);
	for (int i = 0; i < stringlen; i++)
	{ 
		consoletext[i].Char.UnicodeChar = text[i];
		consoletext[i].Attributes = wColor;
	}
	WriteConsoleOutput(hout, consoletext, a, b, &c);
}
void HuyWindows::write(const string st, const int x, const int y, const int backgroundColor, const int foregroundColor) {
	write(toWString(st), x, y, backgroundColor, foregroundColor);
}
void HuyWindows::gotoXY(const int x, const int y) {
	COORD coord = { _Left + x, _Top + y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void HuyWindows::clearConsole(const wchar_t wchar, const bool contentOnly) {
	wstring rowString = L"";
	int offset = contentOnly ? 1 : 0;
	for (int col = contentOnly; col < _Width - contentOnly; col++)
	{
		rowString += wchar;
	}
	for (int row = contentOnly; row < _Height - contentOnly; row++)
	{
		write(rowString, contentOnly, row, _BackgroundColor, _ForegroundColor);
	}
}
void HuyWindows::clearConsole(const char ch, const bool contentOnly) {
	clearConsole((wchar_t)ch, contentOnly);
}
void HuyWindows::saveScreenRect(const int x, const int y, const int w, const int h) {
	HANDLE hStdout;
	int new_w = w == 0 ? _Width : w;
	int new_h = h == 0 ? _Height : h;
	_ChiBuffer = new CHAR_INFO[new_w * new_h];
	COORD coordBufSize = { new_w , new_h };
	COORD coordBufCoord = { 0, 0 };
	BOOL fSuccess;
	_SrctReadRect.Top = _Top + y;     
	_SrctReadRect.Left = _Left + x;
	_SrctReadRect.Bottom = _Top + y + new_h;
	_SrctReadRect.Right = _Left + x + new_w;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	fSuccess = ReadConsoleOutput(
		hStdout,        
		_ChiBuffer,      
		coordBufSize,   
		coordBufCoord,  
		&_SrctReadRect); 
	_SavedRect = _SrctReadRect;
}
void HuyWindows::restoreScreenRect() {
	if (_SavedRect.Right == 0 && _SavedRect.Left == 0 && _SavedRect.Top == 0 && _SavedRect.Bottom == 0) return;

	HANDLE hStdout;  
	SMALL_RECT srctWriteRect = _SavedRect;
	COORD coordBufSize = { _SavedRect.Right - _SavedRect.Left + 1, _SavedRect.Bottom - _SavedRect.Top + 1 };
	COORD coordBufCoord = { 0, 0 };
	BOOL fSuccess; 
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	fSuccess = WriteConsoleOutput( 
		hStdout,        
		_ChiBuffer,       
		coordBufSize,     
		coordBufCoord,    
		&srctWriteRect); 
}
void HuyWindows::showConsoleCursor(const bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(out, &cursorInfo);
}
void HuyWindows::animateFrame(const int x, const int y, const int w, const int h, const int backgroundColor, const int foregroundColor) {
	int x2 = _Left + x;
	int y2 = _Top + y;
	int w2 = w == 0 ? _Width : 1;
	int h2 = h == 0 ? _Height : 1;
	int backgroundColor2 = backgroundColor == -1 ? _BackgroundColor : backgroundColor;
	int foregroundColor2 = foregroundColor == -1 ? _ForegroundColor : foregroundColor;
	int stepX = w2 < 10 ? 1 : w2 / 10;
	int stepY = h2 < 10 ? 1 : h2 / 10;

	int x1 = x2 + w2 / 2;
	int y1 = y2 + h2 / 2;
	int w1 = 1;
	int h1 = 1;
	while (x1 > x2 || y1 > y2 || w1 < w2 || h1 < h2) {
		if (x1 > x2) x1 -= stepX;
		else x1 = x2;
		if (x1 < x2) x1 = x2;

		if (y1 > y2) y1 -= stepY;
		else y1 = y2;
		if (y1 < y2) y1 = y2;

		if (w1 < w2) w1 += stepX * 2;
		else w1 = w2;
		if (w1 > w2) w1 = w2;

		if (h1 < h2) h1 += stepY * 2;
		else h1 = h2;
		if (h1 > h2) h1 = h2;

		HuyWindows temp(x1, y1, w1, h1, _FrameNo, backgroundColor2, foregroundColor2);
		temp.clearConsole();
		temp.drawFrame();
		 
		//Sleep(10);
	}
}
 