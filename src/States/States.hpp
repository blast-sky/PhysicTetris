#pragma once

#include "IState.hpp"
#include "InputController.hpp"

namespace pt
{
	class MenuState : public IState
	{
	public:
		MenuState(InputController* controller);

		void update(float dt) override;
		void draw() override;
		void eventCheck(sf::Event) override;

	private:
		InputController* m_controller;
		MenuView& m_menu;
	};


	class InGameState : public IState
	{
	public:
		InGameState(InputController* controller);
		~InGameState() override;

		void draw() override;
		void update(float dt) override;
		void eventCheck(sf::Event) override;

	private:
		InputController* m_controller;
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
		RestartGameState(InputController* controller);

		void update(float) override;
		void draw() override;

	private:
		InputController* m_controller;
	};
}