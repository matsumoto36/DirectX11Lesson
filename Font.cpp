#include "Font.h"

ID3D11Device* Font::device;
list<wstring> Font::loadedFontDataList;


Font::Font() {}
Font::~Font() {}

void Font::LoadAllFont() {

	if (loadedFontDataList.size() > 0) UnLoadAllFont();

	//���[�h�����Font�����擾

	loadedFontDataList = list<wstring>();



}

void Font::UnLoadAllFont() {

	for (auto item : loadedFontDataList) {

	}

	loadedFontDataList = list<wstring>();

}

