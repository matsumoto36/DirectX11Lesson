#include "FileAccess.h"

void FileAccess::SearchDirectoryPathInDirectory(const string& directoryName, vector<string>& findDirectories) {

	findDirectories = vector<string>();

	WIN32_FIND_DATA win32FindData;
	HANDLE find = FindFirstFile(directoryName.c_str(), &win32FindData);

	do {
		if (find != INVALID_HANDLE_VALUE) {
			if (strcmp(win32FindData.cFileName, ".") &&
				strcmp(win32FindData.cFileName, "..")
				) {
				if (win32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					// フォルダ
					findDirectories.push_back(win32FindData.cFileName);
				}
				else {
					// ファイル
				}
			}
		}
	} while (FindNextFile(find, &win32FindData));
}

void FileAccess::SearchDirectoryPathInDirectory(const wstring& directoryName, vector<wstring>& findDirectories) {

	findDirectories = vector<wstring>();

	WIN32_FIND_DATAW win32FindData;
	HANDLE find = FindFirstFileW(directoryName.c_str(), &win32FindData);

	do {
		if (find != INVALID_HANDLE_VALUE) {

			if (lstrcmpW(win32FindData.cFileName, L".") &&
				lstrcmpW(win32FindData.cFileName, L"..")
				) {
				if (win32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					// フォルダ
					findDirectories.push_back(win32FindData.cFileName);
				}
				else {
					// ファイル
				}
			}
		}
	} while (FindNextFileW(find, &win32FindData));
}