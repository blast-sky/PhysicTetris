#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

		static sf::Sound FigureSpawnSound;
		static sf::Sound FigureCollishionSound;

		static sf::Music BackMusic;

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

			find = FindResource(NULL, MAKEINTRESOURCE(IDR_MY_OGG2), L"MY_OGG");
			res = LoadResource(NULL, find);
			size = SizeofResource(NULL, find);
			m_figureSpawnSoundBuffer.loadFromMemory(res, size);
			FigureSpawnSound.setBuffer(m_figureSpawnSoundBuffer);

			find = FindResource(NULL, MAKEINTRESOURCE(IDR_MY_OGG1), L"MY_OGG");
			res = LoadResource(NULL, find);
			size = SizeofResource(NULL, find);
			m_FigureCollishionSoundBuffer.loadFromMemory(res, size);
			FigureCollishionSound.setBuffer(m_FigureCollishionSoundBuffer);

			find = FindResource(NULL, MAKEINTRESOURCE(IDR_MY_OGG3), L"MY_OGG");
			res = LoadResource(NULL, find);
			size = SizeofResource(NULL, find);
			BackMusic.openFromMemory(res, size);
		}

	private:
		static sf::SoundBuffer m_figureSpawnSoundBuffer;
		static sf::SoundBuffer m_FigureCollishionSoundBuffer;
	};

	sf::Texture Resources::BackgroundTex;
	sf::Texture Resources::FloorTex;
	sf::Texture Resources::FigureTex;

	sf::Font Resources::Font;

	sf::Sound Resources::FigureSpawnSound;
	sf::SoundBuffer Resources::m_figureSpawnSoundBuffer;
	sf::Sound Resources::FigureCollishionSound;
	sf::SoundBuffer Resources::m_FigureCollishionSoundBuffer;

	sf::Music Resources::BackMusic;
}