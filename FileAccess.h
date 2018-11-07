#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class FileAccess final {

private:
	FileAccess() {}
	~FileAccess() {}

public:
	
	static void SearchDirectoryPathInDirectory(const string& directoryName, vector<string>& findDirectories);
	static void SearchDirectoryPathInDirectory(const wstring& directoryName, vector<wstring>& findDirectories);
};

