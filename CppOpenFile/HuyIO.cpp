#include "HuyIO.h" 

HuyIO::HuyIO() {

}

HuyIO::~HuyIO() {

} 

void HuyIO::writeToFile(string fileName, wstring data[], int size) {
	std::wofstream wof;
	wof.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wstring fileNameUTF = HuyUnicode::StringToWString(fileName);
	wof.open(fileNameUTF);
	for (int i = 0; i < size; i++) {
		wof << data[i] << L"\n";
	}
	wof.close();
}
void HuyIO::writeToCSVFile(string fileName, wstring data[], int size) {
	// Write file in UTF-8  
	std::wofstream wof;
	wof.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wstring fileNameUTF = HuyUnicode::StringToWString(fileName);
	wof.open(fileNameUTF);
	wstring temp;
	wstring line;
	for (int i = 0; i < size; i++) {
		//line = L"";
		temp = data[i];
		if (temp != L"") {
			wof << temp << L"\n";
		}
	}
	wof.close();
}

vector<wstring> HuyIO::loadConfig(string fileName) {
	std::ifstream f(fileName);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(f.rdbuf());
	std::wistream wf(&conv);
	wchar_t BOM = 0xFEFF; 
	unicode str[0x1000];
	unicode u;
	vector<wstring> result;
	wf.get(u); 
	while (!wf.eof()) {
		wf.getline(str, 1000);
		result.push_back(str); 
	}
	return result;
}
vector<wstring> HuyIO::readDataFromFile(wstring fileName) {
	std::ifstream f(fileName);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(f.rdbuf());
	std::wistream wf(&conv);
	wchar_t BOM = 0xFEFF;
	unicode str[0x1000];
	unicode u;
	vector<wstring> result;
	//wf.get(u); 
	while (!wf.eof()) {
		wf.getline(str, 1000);
		wstring line = str;
		if (line.length() > 0 && line[0] == BOM) {
			line = line.substr(1);
		}
		result.push_back(line);
	}
	return result;
}