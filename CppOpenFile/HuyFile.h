#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string> 

class HuyFile
{
    public:
        wstring Name;
        wstring Type;
        ULONGLONG Size;

        HuyFile(): HuyFile(L"", L"", 0) {
        }
        HuyFile(wstring name, wstring type, ULONGLONG size) {
            this->Name = name;
            this->Type = type;
            this->Size = size;
        } 
};

