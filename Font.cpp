#include "Font.h"

ID3D11DeviceContext* Font::deviceContext;
unordered_map<string, DESIGNVECTOR> Font::loadedFontDataList;

void Font::LoadAllFont() {

	if (loadedFontDataList.size() > 0) UnLoadAllFont();

	//�t�H���g�����[�h
	loadedFontDataList = unordered_map<string, DESIGNVECTOR>();

	string loadingFontList[] = {
		TEXT("RictyDiminishedDiscord-Regular"),
	};

	for (auto item : loadingFontList) {

		loadedFontDataList.emplace(item, nullptr);
		
		auto filename = item + TEXT(".ttf");

		//�t�H���g�f�[�^��ǉ�
		AddFontResourceEx(
			filename.c_str(), //ttf�t�@�C���ւ̃p�X
			FR_PRIVATE,
			&loadedFontDataList[item]
		);

	}

}

void Font::UnLoadAllFont() {

	for (auto item : loadedFontDataList) {

		auto filename = item.first + TEXT(".ttf");

		//�t�H���g�f�[�^���폜
		AddFontResourceEx(
			filename.c_str(), //ttf�t�@�C���ւ̃p�X
			FR_PRIVATE,
			&item.second
		);

	}

	loadedFontDataList = unordered_map<string, DESIGNVECTOR>();

}

