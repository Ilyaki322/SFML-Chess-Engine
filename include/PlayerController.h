#pragma once
#include "Controller.h"
#include "IObserver.h"

#include <SFML/Graphics.hpp>

class GameManager;
class SFMLBoard;

typedef std::vector<Move> Moves;

class PlayerController : public Controller, public IObserver
{
public:
	PlayerController(GameManager& manager, sf::RenderWindow& window, Color color, SFMLBoard& board);

	bool turnReady() override;
	Move playTurn() override;

	void eventUpdate(sf::Event& event, Color color) override;

private:

	void rotateScreen();

	sf::RenderWindow& m_window;
	SFMLBoard& m_sfmlBoard;

	bool m_firstClick;
	bool m_turnReady;
	Moves m_moves;
	Move m_chosenMove;
};