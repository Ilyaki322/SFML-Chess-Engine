#pragma once
#include "GameState/GameState.h"
#include "Utilities.h"
#include "IObserver.h"
#include "Button.h"

#include <memory>
#include <vector>

typedef std::unique_ptr<Button> buttonPtr;

class ReviewState : public GameState, public IObserver 
{
public:
	ReviewState(GameManager& manager, const int game);

	void eventUpdate(sf::Event& event, Color color = White);

	void execute();
	void draw(float dt);

private:
	void loadGame(const int num);

	std::vector<Move> m_moveList;
	buttonPtr m_next;
	buttonPtr m_prev;
	buttonPtr m_exit;
	sf::Sprite m_background;
	int m_currMove;

	bool m_once;

};