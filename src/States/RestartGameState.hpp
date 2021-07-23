#pragma once

#include "InGameState.hpp"

namespace pt
{
	RestartGameState::RestartGameState(InputController* controller) :
		m_controller(controller)
	{
		controller->getView().restart();
		controller->getTetris().restart();
	}

	void RestartGameState::update(float)
	{
		m_controller->setState(new InGameState(m_controller));
	}

	void RestartGameState::draw()
	{
		m_controller->setState(new InGameState(m_controller));
	}
}