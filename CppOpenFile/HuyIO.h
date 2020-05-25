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
#include "HuyUnicode.h"  

class HuyIO
{ 
	public:
		HuyIO();
		~HuyIO();

		static void writeToFile(string fileName, wstring data[], int size);
		static void writeToCSVFile(string fileName, wstring data[], int size);
		static vector<wstring> readDataFromFile(wstring fileName);
		static vector<wstring> loadConfig(string fileName);
};

