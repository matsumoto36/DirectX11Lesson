#include "Font.h"

ID3D11DeviceContext* Font::deviceContext;
unordered_map<string, DESIGNVECTOR> Font::loadedFontDataList;

void Font::LoadAllFont() {

	if (loadedFontDataList.size() > 0) UnLoadAllFont();

	//フォントをロード
	loadedFontDataList = unordered_map<string, DESIGNVECTOR>();

	string loadingFontList[] = {
		TEXT("RictyDiminishedDiscord-Regular"),
	};

	for (auto item : loadingFontList) {

		loadedFontDataList.emplace(item, nullptr);
		
		auto filename = item + TEXT(".ttf");

		//フォントデータを追加
		AddFontResourceEx(
			filename.c_str(), //ttfファイルへのパス
			FR_PRIVATE,
			&loadedFontDataList[item]
		);

	}

}

void Font::UnLoadAllFont() {

	for (auto item : loadedFontDataList) {

		auto filename = item.first + TEXT(".ttf");

		//フォントデータを削除
		AddFontResourceEx(
			filename.c_str(), //ttfファイルへのパス
			FR_PRIVATE,
			&item.second
		);

	}

	loadedFontDataList = unordered_map<string, DESIGNVECTOR>();

}

