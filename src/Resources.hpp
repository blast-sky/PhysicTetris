#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "../resource.h"

namespace pt
{
	class Resources
	{
	public:
		static sf::Texture BackgroundTex;
		static sf::Texture FloorTex;
		static sf::Texture FigureTex;

		static sf::Font Font;

		static void load()
		{
			HRSRC find;
			HGLOBAL res;
			DWORD size;

			find = FindResource(NULL, MAKEINTRESOURCE(IDB_PNG1), L"PNG");
			size = SizeofResource(NULL, find);
			res = LoadResource(NULL, find);
			BackgroundTex.loadFromMemory(res, size);

			find = FindResource(NULL, MAKEINTRESOURCE(IDB_PNG2), L"PNG");
			size = SizeofResource(NULL, find);
			res = LoadResource(NULL, find);
			FloorTex.loadFromMemory(res, size);

			find = FindResource(NULL, MAKEINTRESOURCE(IDB_PNG3), L"PNG");
			size = SizeofResource(NULL, find);
			res = LoadResource(NULL, find);
			FigureTex.loadFromMemory(res, size);

			find = FindResource(NULL, MAKEINTRESOURCE(IDR_MY_FONT2), L"MY_FONT");
			res = LoadResource(NULL, find);
			size = SizeofResource(NULL, find);
			Font.loadFromMemory(res, size);
		}
	};

	sf::Texture Resources::BackgroundTex = sf::Texture();
	sf::Texture Resources::FloorTex = sf::Texture();
	sf::Texture Resources::FigureTex = sf::Texture();
	sf::Font Resources::Font = sf::Font();
}