#pragma once

#include "States.hpp"

namespace pt
{
	InGameState::InGameState(InputController* controller) :
		m_controller(controller),
		m_tetris(controller->getTetris()),
		m_view(controller->getView())
	{
		m_tetris.gameOver.attach(&InGameState::onGameOver, this);
		m_tetris.setCurrentFigureSpeed(m_tetris.normalFigureSpeed);
	}

	InGameState::~InGameState()
	{
 		m_tetris.gameOver.detachLater(&InGameState::onGameOver, *this);
	}

	void InGameState::draw()
	{
		m_view.draw();
	}

	void InGameState::update(float dt)
	{
		m_tetris.update(dt);
	}

	void InGameState::eventCheck(sf::Event event)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed: onKeyPressed(event); break;
		case sf::Event::KeyReleased: onKeyReleased(event); break;
		default: break;
		}
	}

	void InGameState::onKeyPressed(sf::Event event)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Q:
			if (!m_isRightRotate)
			{
				m_tetris.rotateCurrentFigure(-PI / 2.f);
				m_isRightRotate = 1;
			}
			break;
		case sf::Keyboard::E:
			if (!m_isLeftRotate)
			{
				m_tetris.rotateCurrentFigure(PI / 2.f);
				m_isLeftRotate = 1;
			}
			break;
		case sf::Keyboard::D: m_tetris.moveCurrentFigure(m_tetris.normalMoveOffset); break;
		case sf::Keyboard::A: m_tetris.moveCurrentFigure(-m_tetris.normalMoveOffset); break;
		case sf::Keyboard::S: m_tetris.setCurrentFigureSpeed(m_tetris.fastFigureSpeed); break;
		default: break;
		}
	}

	void InGameState::onKeyReleased(sf::Event event)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Q: m_isRightRotate = 0; break;
		case sf::Keyboard::E: m_isLeftRotate = 0; break;
		case sf::Keyboard::D: break;
		case sf::Keyboard::A: break;
		case sf::Keyboard::S: m_tetris.setCurrentFigureSpeed(m_tetris.normalFigureSpeed); break;
		default: break;
		}
	}

	void InGameState::onGameOver()
	{
		m_controller->setState(new MenuState(m_controller));
	}
}