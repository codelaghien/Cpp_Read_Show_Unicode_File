#include "HuyCommon.h"

wstring HuyCommon::trim(wstring str) {
	wstring result = str;
	while (result.at(0) == L' ') result = result.substr(1);
	while (result.at(result.size() - 1) == L' ') result = result.substr(0, result.size() - 1);

	return result;
}
string HuyCommon::trim(string str) {
	string result = str;
	while (result.at(0) == L' ') result = result.substr(1);
	while (result.at(result.size() - 1) == L' ') result = result.substr(0, result.size() - 1);

	return result;
}  
wstring HuyCommon::headerPadding(wstring header, int width, wstring fillChar) {
	wstring line = header;
	while (line.length() < width) {
		line = fillChar + line;
		if (line.length() < width) {
			line += fillChar;
		}
	}
	return line;
}
wstring HuyCommon::dataPadding(wstring data, int width, string align, bool display) {
	wstring line = data;
	if (align == "left") {
		while (line.length() < width) {
			line += L" ";
		}
	}
	else if (align == "right") {
		while (line.length() < width) {
			line = L" " + line;
		}
	}
	else {
		while (line.length() < width) {
			line = L" " + line;
			if (line.length() < width) {
				line += L" ";
			}
		}
	}
	if (display && line.length() > width) {
		if (width > 3) {
			line = line.substr(0, width - 4) + L" ...";
		}
		else {
			line = L".";
			while (line.length() < width) {
				line += L".";
			}
		}
	}
	return line;
}