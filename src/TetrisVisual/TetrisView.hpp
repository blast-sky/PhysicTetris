#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "../TetrisLogic/Tetris.hpp"
#include "Event.hpp"

#include "FigureView.hpp"
#include "FloorView.hpp"
#include "FigureHighLight.hpp"

namespace pt
{
	class TetrisView
	{
	public:
		TetrisView(sf::RenderWindow& window, Tetris& m_tetris, float scale) :
			m_window(window),
			m_tetris(m_tetris),
			m_highLight(scale),
			m_scale(scale),
			m_floor(nullptr)
		{ 
			m_tetris.newFigureCreate.attach(&TetrisView::onNewFigureCreate, this);
			m_tetris.figureFall.attach(&TetrisView::onFigureFall, this);

			m_backroundTexture.loadFromFile("res/back.jpg");
			m_backroundTexture.setRepeated(true);

			m_figuresTexture.loadFromFile("res/tiles.png");

			m_floorTexture.loadFromFile("res/ground.png");
			m_floorTexture.setRepeated(true);

			m_floor.reset(new FloorView(m_tetris.getFloor(), m_floorTexture, scale));

			sf::FloatRect rect(
				-static_cast<float>(m_window.getSize().x) / 2.f,
				-static_cast<float>(m_window.getSize().y),
				m_window.getSize().x,
				m_window.getSize().y);
			m_lastView.reset(rect);
		}

		~TetrisView()
		{
			m_tetris.newFigureCreate.detach(&TetrisView::onNewFigureCreate, this);
		}

		void restart()
		{
			m_figures.clear();
			sf::FloatRect rect(
				-static_cast<float>(m_window.getSize().x) / 2.f,
				-static_cast<float>(m_window.getSize().y),
				m_window.getSize().x,
				m_window.getSize().y);
			m_lastView.reset(rect);
		}

		void draw()
		{
			// View setting
			m_lastView = getNextView();
			m_window.setView(m_lastView);

			// Backround draw
			backgroundDraw();

			// Hightight draw
			m_window.draw(m_highLight);

			// Figure draw
			for (auto& figure : m_figures)
				m_window.draw(*figure);

			// Floor draw
			m_window.draw(*m_floor);

			// Highest point draw (debug)
			sf::CircleShape higherPoint(2.f, 120u);
			higherPoint.setOrigin(sf::Vector2f(1.f, 1.f));
			higherPoint.setPosition(sf::Vector2f(Vector2f(m_tetris.getHigherPosition())) * m_scale);
			higherPoint.setFillColor(sf::Color::Green);
			m_window.draw(higherPoint);

			// Default wiew set
			m_window.setView(m_window.getDefaultView());
		}

	private:
		sf::RenderWindow& m_window;
		Tetris& m_tetris;
		std::shared_ptr<FloorView> m_floor;
		FigureHighLight m_highLight;
		std::list<std::shared_ptr<IFigureView>> m_figures;
		sf::View m_lastView;

		sf::Texture m_backroundTexture;
		sf::Texture m_floorTexture;
		sf::Texture m_figuresTexture;
		float m_scale;

		void onNewFigureCreate(IFigureBody* figure)
		{
			std::shared_ptr<IFigureView> ptr;
			auto castedFigure = dynamic_cast<FigureShapeBody*>(figure);
			ptr.reset(new FigureShapeView(*castedFigure, m_figuresTexture, m_scale));
			m_figures.push_back(ptr);
			m_highLight.setFigure(figure);
		}

		void onFigureFall(IFigureBody* figure)
		{
			m_figures.remove_if([figure](std::shared_ptr<IFigureView>& checkFigure) -> bool
				{
					return figure->getId() == checkFigure->getId();
				});
		}

		sf::View getNextView()
		{
			auto view = m_lastView;
			auto size = view.getSize();
			auto centr = view.getCenter();

			auto upper = sf::Vector2i(0, m_window.getSize().y * 0.10f);
			auto lower = sf::Vector2i(0, m_window.getSize().y * 0.20f);
			auto figureLower = sf::Vector2i(0, m_window.getSize().y * 0.80f);

			auto upperLine = m_window.mapPixelToCoords(upper, m_lastView).y; // spawn point beetwen 25-30% window height
			auto lowerLine = m_window.mapPixelToCoords(lower, m_lastView).y;
			auto spawn = m_tetris.getSpawnPosition().y * m_scale;

			auto lowerFigureLine = m_window.mapPixelToCoords(figureLower, m_lastView).y;

			auto curFigureLine= m_tetris.getSelectedFigure().getFigure()->getPosition().y;

			float zoomDelta = 0.005f; // Zoom dencity
			float moveDelta = 0.5f;

			if (spawn < upperLine)
			{
				centr.y -= moveDelta * (1);
			}
			else if (spawn > lowerLine)
			{
				centr.y += moveDelta;
			}

			/*if (curFigureLine > lowerFigureLine)
			{
				size *= 1.f + zoomDelta;
				centr.y -= (size * zoomDelta).y / 2.f;
			}*/

			view.setCenter(centr);
			view.setSize(size);

			return view;
		}

		void backgroundDraw()
		{
			sf::Sprite sprite(m_backroundTexture);

			sf::Vector2i size(m_window.getSize().x, m_window.getSize().y);
			sf::Vector2i leftUpCoord(0, 0);

			sf::Vector2i s(m_window.mapPixelToCoords(leftUpCoord).x, m_window.mapPixelToCoords(leftUpCoord).y);
			sf::Vector2i e(m_window.mapPixelToCoords(size).x, m_window.mapPixelToCoords(size).y);

			sprite.setTextureRect(sf::IntRect(s, e - s));
			sprite.setPosition(s.x, s.y);
			m_window.draw(sprite);
		}
	};
}