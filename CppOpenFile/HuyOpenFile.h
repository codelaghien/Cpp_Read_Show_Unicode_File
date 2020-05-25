#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>   
#include <vector>
#include <fstream> 
#include <algorithm>    // std::sort
#include <cwctype>

#include "HuyUnicode.h"; 
#include "HuyFile.h"; 
#include "HuyWindows.h";
#include "HuyCurrentConsole.h";
#include "HuySize.h";
#include "HuyCommon.h";

class HuyOpenFile
{
    public:
        static wstring CurrentPath;
        static int HeaderCount;
        static wstring Header[];
        static int HeaderWidth[];
        static int CurrentRow;
        static HuyFile CurrentFile;

        HuyOpenFile() {
        }

        static HuyFile getFile(HuyWindows mainWindow);

    private:
        static vector<HuyFile> getFileList();
        static bool filter(wstring fileName);
        static void printTableData(HuyWindows window, vector<HuyFile> list);
        static void printHeader(HuyWindows window, int row);
        static void printData(HuyWindows window, int row, HuyFile file);
        static void printFooter(HuyWindows window, int row);
        static void printBottomCommands(HuyWindows window);
};

