#pragma once

#include "IState.hpp"
#include "Scene.hpp"

namespace pt
{
	class MenuState : public IState
	{
	public:
		MenuState(Scene* controller);

		void update(float dt) override;
		void draw() override;
		void eventCheck(sf::Event) override;

	private:
		Scene* m_controller;
		MenuView& m_menu;
	};


	class InGameState : public IState
	{
	public:
		InGameState(Scene* controller);
		~InGameState() override;

		void draw() override;
		void update(float dt) override;
		void eventCheck(sf::Event) override;

	private:
		Scene* m_controller;
		Tetris& m_tetris;
		TetrisView& m_view;
		bool m_isRightRotate = false;
		bool m_isLeftRotate = false;

		void onGameOver();

		void onKeyPressed(sf::Event);
		void onKeyReleased(sf::Event);
	};

	class RestartGameState : public IState
	{
	public:
		RestartGameState(Scene* controller);

		void update(float) override;
		void draw() override;

	private:
		Scene* m_controller;
	};
}