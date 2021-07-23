#pragma once

#include "TetrisLogic/Tetris.hpp"
#include "TetrisVisual/TetrisView.hpp"
#include "TetrisVisual/MenuView.hpp"
#include "States/IState.hpp"

namespace pt
{
	class InputController
	{
	public:
		InputController(Tetris& tetris, TetrisView& view, MenuView& menu);

		void setState(IState* state);

		void checkEvent(sf::Event event);
		void draw();
		void update(float dt);

		Tetris& getTetris();
		TetrisView& getView();
		MenuView& getMenu();

	private:
		Tetris& m_tetris;
		TetrisView& m_view;
		MenuView& m_menu;
		IState* m_currentState;
	};

	InputController::InputController(Tetris& tetris, TetrisView& view, MenuView& menu) :
		m_tetris(tetris),
		m_view(view),
		m_menu(menu),
		m_currentState(nullptr)
	{	}

	void InputController::setState(IState* state)
	{
		if (m_currentState) delete m_currentState;
		m_currentState = state;
	}

	void InputController::checkEvent(sf::Event event)
	{
		m_currentState->eventCheck(event);
	}

	void InputController::draw()
	{
		m_currentState->draw();
	}

	void InputController::update(float dt)
	{
		m_currentState->update(dt);
	}

	Tetris& InputController::getTetris()
	{
		return m_tetris;
	}
	TetrisView& InputController::getView()
	{
		return m_view;
	}
	MenuView& InputController::getMenu()
	{
		return m_menu;
	}
}