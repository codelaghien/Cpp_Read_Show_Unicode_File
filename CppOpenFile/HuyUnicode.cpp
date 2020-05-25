#include "HuyUnicode.h"
#include <iostream> 
 
wstring HuyUnicode::ReadString() {
	unicode buffer[MAX_LENGTH];
	size_t numRead = 0;
	_cgetws_s(buffer, &numRead);
	return buffer;
}
void HuyUnicode::ReadString(unicode* var) {
	unicode buffer[MAX_LENGTH];
	size_t numRead = 0;
	_cgetws_s(buffer, &numRead);
	for (size_t i = 0; i <= numRead; i++) {
		var[i] = buffer[i];
	}
}
void HuyUnicode::ReadString(const unicode* subject, unicode* var) {
	WriteString(subject);
	ReadString(var);
}
void HuyUnicode::ReadString(const char* subject, unicode* var) {
	WriteString(subject);
	ReadString(var);
}

int HuyUnicode::ReadInt() {
	int so; 
	scanf_s("%d", &so);
	getchar(); 
	return so;
}

void HuyUnicode::WriteString(const unicode* string) {
	_cputws(string);
}
void HuyUnicode::WriteString(const wstring string) {
	_cputws(string.c_str());
}
void HuyUnicode::WriteString(const char* string) {
	cout << string;
}

int HuyUnicode::Size(const unicode* string) {
	return wcslen(string);
}
int HuyUnicode::Size(const char* string) {
	for (int i = 0; i < MAX_LENGTH; i++) {
		if (string[i] == EOL) {
			return i;
		}
	}
	return 0;
}

void HuyUnicode::AppendString(unicode* left_string, const unicode* right_string) {
	int left_size = Size(left_string);
	int right_size = Size(right_string);
	int rigth_index = 0;
	for (int i = left_size; i < left_size + right_size; i++) {
		left_string[i] = right_string[rigth_index++];
	}
	left_string[left_size + right_size] = EOL;
}
void HuyUnicode::AppendString(unicode* left_string, const char* right_string) {
	int left_size = Size(left_string);
	int right_size = Size(right_string);
	int rigth_index = 0;
	for (int i = left_size; i < left_size + right_size; i++) {
		left_string[i] = right_string[rigth_index++];
	}
	left_string[left_size + right_size] = EOL;
}

void HuyUnicode::StringToUnicode(const char* string, unicode* var) {
	int string_size = Size(string);
	int i = 0;
	for (i = 0; i < string_size; i++) {
		var[i] = string[i];
	}
	var[i] = EOL;
} 

wstring HuyUnicode::StringToWString(const string& s) {
	wstring temp(s.length(), L' ');
	copy(s.begin(), s.end(), temp.begin());
	return temp;
}