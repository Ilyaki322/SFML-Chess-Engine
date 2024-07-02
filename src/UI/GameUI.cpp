#include "UI/GameUI.h"
#include "ChessLogic/NBoard.h"
#include "Assets.h"

GameUI::GameUI(StateMachine& stateMachine, sf::Sprite& p1, sf::Sprite& p2, SFMLBoard& board)
	:PlayUI(stateMachine), m_player1(p1), m_player2(p2), m_whiteScore(0), m_blackScore(0),m_board(board)
{
	m_player1.setPosition(30, 650);
	m_player2.setPosition(30, 20);

	m_scoreMap[PawnVal] = 1;
	m_scoreMap[RookVal] = 5;
	m_scoreMap[BishopVal] = 3;
	m_scoreMap[KnightVal] = 3;
	m_scoreMap[QueenVal] = 9;
	m_scoreMap[KingVal] = 0;

	m_Bscore.setFont(Assets::instance().getFont());
	m_Wscore.setFont(Assets::instance().getFont());

	m_Bscore.setFillColor(sf::Color::Black);
	m_Wscore.setFillColor(sf::Color::White);

	m_Bscore.setCharacterSize(50);
	m_Wscore.setCharacterSize(50);
	
	m_Bscore.setPosition(50, 130);
	m_Wscore.setPosition(50, 550);
}

/*
* calculates the relative score, draws it. 
* draws all captured pieces.
* draws the Player icon and background.
*/
void GameUI::draw(sf::RenderWindow &window)
{
	PlayUI::draw(window);
	window.draw(m_player1);
	window.draw(m_player2);

	auto board = NBoard::instance().getBoard();

	m_whiteScore = m_blackScore = 39;
	for (int i = 0; i < SIZE; i++) {
		if (board[i] == 0)continue;
		Color color = (board[i] & White) > 0 ? White : Black;
		int piece = board[i] & 0b111;
		if (color == White)m_blackScore -= m_scoreMap[piece];
		else m_whiteScore -= m_scoreMap[piece];
	}
	m_Bscore.setString((""));
	m_Wscore.setString((""));
	if (m_whiteScore > m_blackScore) {
		m_whiteScore = m_whiteScore - m_blackScore;
		m_Wscore.setString("+" + std::to_string(m_whiteScore));
	}
	else if (m_whiteScore < m_blackScore) {
		m_blackScore = m_blackScore - m_whiteScore;
		m_Bscore.setString("+" + std::to_string(m_blackScore));
	}
	auto& white = m_board.getCaptured(White);
	for (const auto& i : white) {
		i->draw(window);
	}
	auto& black = m_board.getCaptured(Black);
	for (const auto& i : black) {
		i->draw(window);
	}
	window.draw(m_Bscore);
	window.draw(m_Wscore);
}

void GameUI::initButtons(GameManager& manager)
{
	m_newBackground = false;
	PlayUI::initButtons(manager);
	m_whiteScore = m_blackScore = 39; 
}

void GameUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
}
