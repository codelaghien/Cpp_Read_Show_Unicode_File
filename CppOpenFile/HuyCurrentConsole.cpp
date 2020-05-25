#include "HuyCurrentConsole.h"

HuySize HuyCurrentConsole::getSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows; 
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return HuySize(columns, rows);
} 
