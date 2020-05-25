// CppHuyOpenFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <iostream>
#include <string>  
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */ 

#include "HuyUnicode.h";
#include "HuyOpenFile.h"
#include "HuyFile.h";
#include "HuyCommon.h";
#include "HuyWindows.h";
#include "HuyCurrentConsole.h";
#include "HuySize.h";
#include "HuyIO.h";

using namespace std;
 
void writeContent(HuyWindows mainWindow, vector<wstring> fileContent, int currentRow, int maxHeight) {
    int y = 1;
    for (int row = currentRow; row < fileContent.size(); row++) {
        if (y < maxHeight) {
            mainWindow.write(fileContent[row], 1, y++, HuyColors::BLUE, HuyColors::WHITE);
        } 
        else {
            break;
        }
    }
}
int main()
{
    /* initialize random seed: */
    srand(time(NULL));
     
    HuySize consoleSize = HuyCurrentConsole::getSize();
    HuyWindows mainWindow(0, 0, consoleSize.width, consoleSize.height, 1, HuyColors::BLUE, HuyColors::WHITE);
    mainWindow.showConsoleCursor(false);
    mainWindow.clearConsole();
    mainWindow.drawFrame();

    wstring title = L" Đọc tập tin ";
    mainWindow.write(title, (mainWindow.getWidth() - title.length()) / 2, 0, HuyColors::RED, HuyColors::WHITE);

    int col = 1;
    int row = mainWindow.getHeight() - 1;
    mainWindow.write(L" ", col++, row);
    wstring temp = L" Ctrl + o ";
    mainWindow.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
    col += temp.size();
    temp = L" Chọn tập tin ";
    mainWindow.write(temp, col, row);
    col += temp.size();

    mainWindow.write(L" ", col++, row);
    temp = L" ↑ ";
    mainWindow.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
    col += temp.size();

    mainWindow.write(L" ", col++, row);
    temp = L" ↓ ";
    mainWindow.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
    col += temp.size();

    mainWindow.write(L" ", col++, row);
    temp = L" Ctrl + x ";
    mainWindow.write(temp, col, row, HuyColors::RED, HuyColors::WHITE);
    col += temp.size();
    temp = L" Thoát ";
    mainWindow.write(temp, col, row);

    unsigned int c = _getch(); 
    int maxHeight = mainWindow.getHeight() - 2;
    int currentRow = 0;
    wstring path = L"";
    vector<wstring> fileContent;
    while (c != 24) { // Ctrl + x
        if (c == 15) // Ctrl + o
        {  
            HuyOpenFile::CurrentPath = path + L"*";

            HuyOpenFile openFile; 
            HuyFile file = openFile.getFile(mainWindow);
            mainWindow.clearConsole(); 
            while (file.Size == 0 && file.Name != L"") {
                path += file.Name + L"\\";
                HuyOpenFile::CurrentPath = path + L"*";
                file = openFile.getFile(mainWindow);
                mainWindow.clearConsole();
            }
            if (file.Size > 0) {
                currentRow = 0;
                fileContent = HuyIO::readDataFromFile(path + file.Name);
                wstring title = L" " + file.Name + L" ";
                mainWindow.write(title, (mainWindow.getWidth() - title.length()) / 2, 0, HuyColors::RED, HuyColors::WHITE);
                writeContent(mainWindow, fileContent, currentRow, maxHeight);
            } 
            /*else {
                title = L"Bạn đã chọn " + wstring((file.Size == 0) ? L"thư mục" : L"tập tin");
                mainWindow.write(title, (mainWindow.getWidth() - title.length()) / 2, (mainWindow.getHeight()) / 2 - 1, HuyColors::BLUE, HuyColors::WHITE);
                title = (file.Name == L"") ? file.Type : file.Name;
                mainWindow.write(title, (mainWindow.getWidth() - title.length()) / 2, (mainWindow.getHeight()) / 2 + 1, HuyColors::RED, HuyColors::WHITE);
            }*/
        } 
        else if (c == 72 && fileContent.size() > 0)
        {
            if (currentRow > 0) {
                currentRow--; 
                writeContent(mainWindow, fileContent, currentRow, maxHeight);
            }
        }
        else if (c == 80 && currentRow + maxHeight < fileContent.size()) {
            currentRow++;
            writeContent(mainWindow, fileContent, currentRow, maxHeight);
        }
        c = _getch();
    } 
    //system("PAUSE");
    //int c = _getch();
    return 0;
}
 