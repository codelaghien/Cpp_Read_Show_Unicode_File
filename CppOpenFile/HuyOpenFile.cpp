#include "HuyOpenFile.h"

struct HuyObject {
    bool operator() (HuyFile f1, HuyFile f2) { return (f1.Size < f2.Size); }
} HuyObject;

HuyFile HuyOpenFile::getFile(HuyWindows mainWindow) {
    int w = mainWindow.getWidth() - 4;
    int h = mainWindow.getHeight() - 4;
    int x = (mainWindow.getWidth() - w) / 2;
    int y = (mainWindow.getHeight() - h) / 2;
    HuyWindows window(x, y, w, h, 1, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
    mainWindow.saveScreenRect(x, y, w, h);
    window.showConsoleCursor(false);
    window.clearConsole();
    window.drawFrame();
    wstring title = L" Chọn tập tin để đọc ";
    window.write(title, (w - title.length()) / 2, 0, HuyColors::GREEN, HuyColors::WHITE); 
    HuyOpenFile::printBottomCommands(window);
    
    vector<HuyFile> list = HuyOpenFile::getFileList();
    HuyOpenFile::printTableData(window, list);

    unsigned int c = _getch(); 
    while (c != 27) { // ESC
        if (c == 72) 
        {
            if (HuyOpenFile::CurrentRow > 0) {
                HuyOpenFile::CurrentRow--;
                HuyOpenFile::printTableData(window, list);
            }
        }
        else if (c == 80) {
            if (HuyOpenFile::CurrentRow < list.size() - 1) {
                HuyOpenFile::CurrentRow++;
                HuyOpenFile::printTableData(window, list);
            }
        }
        else if (c == 13) {
            mainWindow.restoreScreenRect();
            return HuyOpenFile::CurrentFile;
        }
        c = _getch();
    }
    mainWindow.restoreScreenRect();
	return HuyOpenFile::CurrentFile;
}
void HuyOpenFile::printTableData(HuyWindows window, vector<HuyFile> list) {  
    int row = 2;
    HuyOpenFile::printHeader(window, row);
    row += 3;
    for (HuyFile file : list) {
        if (HuyOpenFile::CurrentRow == -1 && file.Size > 0) {
            HuyOpenFile::CurrentRow = row - 5;
            HuyOpenFile::CurrentFile = file;
        }
        else if (HuyOpenFile::CurrentRow == row - 5) {
            HuyOpenFile::CurrentFile = file;
        }
        HuyOpenFile::printData(window, row++, file);
    }
    HuyOpenFile::printFooter(window, row);
}
void HuyOpenFile::printHeader(HuyWindows window, int row) {
    wstring top = L"┌";
    wstring line = L"";
    wstring bottom = L"├";
    int w = 0;  
    for (int i = 0; i < HuyOpenFile::HeaderCount; i++) {
        line += L"│";
        w += HuyOpenFile::HeaderWidth[i] + 1;
        wstring column;
        if (HuyOpenFile::HeaderWidth[i] > 0) {
            column = HuyCommon::headerPadding(HuyOpenFile::Header[i], HuyOpenFile::HeaderWidth[i], L" ");
        }
        else {
            column = HuyCommon::headerPadding(HuyOpenFile::Header[i], window.getWidth() - w - 3, L" ");
        }
        top += HuyCommon::headerPadding(L"", column.length(), L"─");
        if (i < HuyOpenFile::HeaderCount - 1) top += L"┬";
        line += column;
        bottom += HuyCommon::headerPadding(L"", column.length(), L"─");
        if (i < HuyOpenFile::HeaderCount - 1) bottom += L"┼";
    }
    top += L"┐";
    line += L"│";
    bottom += L"┤";
    window.write(top, 1, row++, HuyColors::LIGHTBLUE, HuyColors::WHITE);
    window.write(line, 1, row++, HuyColors::LIGHTBLUE, HuyColors::WHITE);
    window.write(bottom, 1, row++, HuyColors::LIGHTBLUE, HuyColors::WHITE);
}
void HuyOpenFile::printData(HuyWindows window, int row, HuyFile file) {
    wstring line = L"│"; 
    int w = 0;
    int background = HuyOpenFile::CurrentRow == -1 || HuyOpenFile::CurrentRow != row - 5 ? HuyColors::LIGHTBLUE : HuyColors::GREEN;
    int color = HuyOpenFile::CurrentRow == -1 || HuyOpenFile::CurrentRow != row - 5 ? HuyColors::WHITE : HuyColors::WHITE;

    line += HuyCommon::dataPadding(file.Type, HuyOpenFile::HeaderWidth[0], "left");
    w += HuyOpenFile::HeaderWidth[0];
    line += L"│";
    line += HuyCommon::dataPadding(file.Size == 0 ? L"" : to_wstring(file.Size) + L" bytes", HuyOpenFile::HeaderWidth[1], "right");
    w += HuyOpenFile::HeaderWidth[1];
    line += L"│";
    line += HuyCommon::dataPadding(file.Name, window.getWidth() - w - 6, "left");
    line += L"│";
    window.write(line, 1, row, background, color);
}
void HuyOpenFile::printFooter(HuyWindows window, int row) {
    wstring line = L"└";
    int w = 0;
    for (int i = 0; i < HuyOpenFile::HeaderCount; i++) {
        w += HuyOpenFile::HeaderWidth[i] + 1;
        wstring column;
        if (HuyOpenFile::HeaderWidth[i] > 0) {
            column = HuyCommon::headerPadding(L"", HuyOpenFile::HeaderWidth[i], L"─");
        }
        else {
            column = HuyCommon::headerPadding(L"", window.getWidth() - w - 3, L"─");
        }
        line += column;
        if (i < HuyOpenFile::HeaderCount - 1) line += L"┴";
    }
    line += L"┘";
    if (row > 0) window.write(line, 1, row, HuyColors::LIGHTBLUE, HuyColors::WHITE);
}
bool HuyOpenFile::filter(wstring fileName) {
    wstring compareName = fileName;
    transform(compareName.begin(), compareName.end(), compareName.begin(), ::tolower);

    if (compareName.rfind(L".h") == compareName.length() - 2) return true;
    if (compareName.rfind(L".cpp") == compareName.length() - 4) return true;
    if (compareName.rfind(L".csv") == compareName.length() - 4) return true;
    if (compareName.rfind(L".txt") == compareName.length() - 4) return true;

    return false;
}
vector<HuyFile> HuyOpenFile::getFileList() {  
	vector<HuyFile> list; 
    HANDLE hFind; 
    WIN32_FIND_DATA data; 
    hFind = FindFirstFileW(HuyOpenFile::CurrentPath.c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE)
    { 
        do
        {
            wstring fileName = data.cFileName;
            if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || 
                filter(fileName)) {
                HuyFile file;
                if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    //file.Name = L"<Thư mục> ";
                    //file.Name += filename;
                    file.Name = L"";
                    if (fileName == L".") file.Type += L"<Thư mục hiện tại>";
                    else if (fileName == L"..") file.Type += L"<Thư mục cha>";
                    else {
                        file.Type = L"<Thư mục>";
                        file.Name = fileName;
                    }
                }
                else { 
                    file.Type = L"";
                    file.Name += data.cFileName;
                }
                ULONGLONG FileSize = (static_cast<ULONGLONG>(data.nFileSizeHigh) << sizeof(data.nFileSizeLow) * 8) | data.nFileSizeLow;
                file.Size = FileSize;
                list.push_back(file);
            }
        } while (FindNextFileW(hFind, &data));   

        FindClose(hFind);   
    } 
    sort(list.begin(), list.end(), HuyObject);
	return list;
} 
void HuyOpenFile::printBottomCommands(HuyWindows window) {
    // http://xahlee.info/comp/unicode_arrows.html
    int col = 1;
    int row = window.getHeight() - 1; 
    window.write(L" ", col++, row);
    wstring temp = L" ↑ ";
    window.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
    col += temp.size();

    window.write(L" ", col++, row);
    temp = L" ↓ ";
    window.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
    col += temp.size(); 

    window.write(L" ", col++, row);
    temp = L" ESC ";
    window.write(temp, col, row, HuyColors::RED, HuyColors::WHITE);
    col += temp.size();
    temp = L" Thoát ";
    window.write(temp, col, row);
}

wstring HuyOpenFile::CurrentPath = L"*";
int HuyOpenFile::HeaderCount = 3;
wstring HuyOpenFile::Header[] = { L"", L"Kích thước", L"Tên" };
int HuyOpenFile::HeaderWidth[] = { 20, 20, 0 }; 
int HuyOpenFile::CurrentRow = -1;
HuyFile HuyOpenFile::CurrentFile;
