#pragma once

#include "../../extern/box2d/include/box2d/box2d.h"
#include "Event.hpp"
#include "Figure/Figures.hpp"

namespace pt
{
	class SelectedFigure
	{
	public:
		event<void(b2Vec2)> figureCollide;
		const float rotateSpeed = 12.f;

		SelectedFigure(b2World& world) :
			m_world(world),
			m_figure(nullptr),
			m_speed(0.f, 0.f),
			m_angle(0.f)
		{	}

		void update()
		{
			tryRotate();
			
			tryMove();

			m_figure->setVelocity(m_speed);

			if (isCollideWithOtherFigures())
			{
				m_figure->setGravityScale(1.f);
				figureCollide(m_figure->getPosition());
			}
		}

		void move(b2Vec2 offset)
		{
			m_position += offset;
		}

		void rotate(float angle)
		{
			m_angle += angle;
		}

		void setFigure(IFigureBody* figure)
		{
			if (m_figure)
			{
				m_figure->setAngularVelocity(0.f);
				m_figure->setGravityScale(1.f);
			}

			m_figure = figure;

			if (figure)
			{
				m_position = m_figure->getPosition();
				m_angle = 0.f;
				m_figure->setGravityScale(0.f);
			}
		}

		IFigureBody* getFigure()
		{
			return m_figure;
		}

		void setSpeed(b2Vec2 speed)
		{
			m_speed = speed;
		}

	private:
		b2World& m_world;
		IFigureBody* m_figure;
		b2Vec2 m_speed;
		b2Vec2 m_position;
		float m_angle;

		void tryMove()
		{
			m_position.y = m_figure->getPosition().y;
			m_figure->setPosition(m_position);
		}

		void tryRotate()
		{
			float eps = 0.001;
			if (m_figure->getAngle() > m_angle - eps && m_figure->getAngle() < m_angle + eps)
				m_figure->setAngularVelocity(0.f);
			else if (m_figure->getAngle() > m_angle - eps)
				m_figure->setAngularVelocity(-rotateSpeed * (m_figure->getAngle() - m_angle - eps));
			else if (m_figure->getAngle() < m_angle + eps)
				m_figure->setAngularVelocity(rotateSpeed * (m_angle - eps - m_figure->getAngle()));
		}

		bool isCollideWithOtherFigures()
		{
			return m_figure->isCollide();
		}
	};
}
