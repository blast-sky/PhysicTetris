#pragma once

#include "RestartGameState.hpp"

namespace pt
{
	MenuState::MenuState(InputController* controller) :
		m_controller(controller),
		m_menu(controller->getMenu())
	{	}

	void MenuState::update(float dt)
	{
		m_menu.update(dt);
	}

	void MenuState::draw()
	{
		m_menu.draw();
	}

	void MenuState::eventCheck(sf::Event e)
	{
		if(e.type == sf::Event::KeyPressed)
			m_controller->setState(new RestartGameState(m_controller));
	}
}