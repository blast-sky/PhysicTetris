#pragma once

#include <iostream>
#include <list>

#include "../../extern/box2d/include/box2d/box2d.h"

#include "Event.hpp"

#include "Figure/Figures.hpp"
#include "Figure/FigureShapeBody.hpp"
#include "SelectedFigure.hpp"
#include "Floor.hpp"

#include "Rules/Rules.hpp"

namespace pt
{
	class Tetris
	{
	public:
		event<void(IFigureBody*)> newFigureCreate;
		event<void(IFigureBody*)> figureFall;
		event<void()> gameWon;
		event<void()> gameOver;

		const b2Vec2 normalFigureSpeed;
		const b2Vec2 fastFigureSpeed;
		const b2Vec2 normalMoveOffset;

		Tetris(float cubeSize) :
			m_world(b2Vec2(0.f, 10.f)),
			normalFigureSpeed(0.f, cubeSize * 1.f),
			fastFigureSpeed(0.f, cubeSize * 6.f),
			m_selectedFigure(m_world),
			m_floor(m_world, b2Vec2(0.f, 0.f), b2Vec2(cubeSize * 10.f, cubeSize)),
			normalMoveOffset(cubeSize / 2.f, 0.f),
			m_higherPosition(0.f, 0.f),
			m_spawn(0.f, -cubeSize * 23.f),
			m_lastSpawn(m_spawn),
			m_cubeSize(cubeSize),
			m_fallFigureCount(0),
			m_frameAfterFigureCreate(-1)
		{	
			m_selectedFigure.figureCollide.attach(&Tetris::onCurrentFigureCollide, this);
		}

		~Tetris()
		{
			m_selectedFigure.figureCollide.detach(&Tetris::onCurrentFigureCollide, this);
			for (auto& figure : m_figuresInWorld)
				delete figure;
		}

		void setRules(IRules* rules)
		{
			m_rules.reset(rules);
		}

		void restart()
		{
			m_selectedFigure.setFigure(nullptr);
			for (auto& figure : m_figuresInWorld)
				delete figure;
			m_figuresInWorld.clear();
			m_higherPosition = b2Vec2(0.f, 0.f);
			m_fallFigureCount = 0;
			createRandomFigure();
		}

		void update(float deltaTimeAsSecond)
		{
			m_world.Step(deltaTimeAsSecond, 8, 3);
			m_selectedFigure.update();
			//higherPositionCheck();
			figureFallsCheck();
			if (m_rules->isGameOver()) gameOver();
			else if (m_rules->isGameWon()) gameWon();
			++m_frameAfterFigureCreate;
		}

		void createRandomFigure(b2Vec2 pos)
		{
			m_frameAfterFigureCreate = -1;
			auto newFigure = new FigureShapeBody(m_world, m_cubeSize);
			newFigure->setPosition(pos);
			
			m_selectedFigure.setFigure(newFigure);
			m_figuresInWorld.push_back(newFigure);
			newFigureCreate(dynamic_cast<IFigureBody*>(newFigure));
		}

		void createRandomFigure()
		{
			auto pos = getHigherPosition();
			pos.x = m_spawn.x;
			pos.y -= m_cubeSize * 10.f;
			if (m_spawn.y > pos.y)
				m_lastSpawn = pos;
			else
				m_lastSpawn = m_spawn;
			createRandomFigure(m_lastSpawn);
		}

		void moveCurrentFigure(b2Vec2 offset)
		{
			m_selectedFigure.move(offset);
		}

		void rotateCurrentFigure(float angle)
		{
			m_selectedFigure.rotate(angle);
		}

		void setCurrentFigureSpeed(b2Vec2 speed)
		{
			m_selectedFigure.setSpeed(speed);
		}

		Floor& getFloor()
		{
			return m_floor;
		}

		b2Vec2 getHigherPosition()
		{
			return m_higherPosition;
		}

		b2Vec2 getSpawnPosition()
		{
			return m_lastSpawn;
		}

		int getFallFigureCount()
		{
			return m_fallFigureCount;
		}

		SelectedFigure& getSelectedFigure()
		{
			return m_selectedFigure;
		}

	private:
		b2World m_world;
		Floor m_floor;
		SelectedFigure m_selectedFigure;
		std::list<IFigureBody*> m_figuresInWorld;
		int m_fallFigureCount;

		b2Vec2 m_higherPosition;
		b2Vec2 m_spawn;
		b2Vec2 m_lastSpawn;
		float m_cubeSize;
		int m_frameAfterFigureCreate;
		
		std::shared_ptr<IRules> m_rules;

		void onCurrentFigureCollide(b2Vec2 figurePos)
		{
           	if (m_frameAfterFigureCreate <= 0)
				gameOver();
			else
				createRandomFigure();
			calculateHigherPos();
		}

		void higherPositionCheck()
		{
			/*b2Vec2 higherPos(0.f, FLT_MAX);
			for (auto& figure : m_figuresInWorld)
			{
				if (higherPos.y > figure->getPosition().y)
					higherPos = figure->getPosition();
			}
			m_higherPosition = higherPos;*/
		}

		void calculateHigherPos()
		{
			b2Vec2 higherPos(0.f, FLT_MAX);
			for (auto& figure : m_figuresInWorld)
			{
				if (figure == m_selectedFigure.getFigure())
					continue;
				if (higherPos.y > figure->getPosition().y)
					higherPos = figure->getPosition();
			}
			m_higherPosition = higherPos;
		}

		void figureFallsCheck()
		{
			std::list<IFigureBody*> removeList;
			for (auto& figure : m_figuresInWorld)
			{
				auto yPos = figure->getPosition().y;
				auto b = 0.f + m_cubeSize * 6.f; // point of figure deleting
				if (yPos > b)
				{
					figureFall(dynamic_cast<IFigureBody*>(figure));
					removeList.push_back(figure);
					if (m_selectedFigure.getFigure() == figure)
						createRandomFigure();
				}
			}

			m_fallFigureCount += removeList.size();

			for (auto& figure : removeList)
				m_figuresInWorld.remove(figure);

			if (removeList.size() > 0)
				calculateHigherPos();
		}

		friend class IRules;
	};
}