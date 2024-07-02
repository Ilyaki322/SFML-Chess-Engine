#include "UI/PuzzleUI.h"
#include "ButtonCommand/UndoPuzzleCommand.h"
#include "ButtonCommand/NextPuzzleCommand.h"
#include "Assets.h"

PuzzleUI::PuzzleUI(StateMachine& stateMachine, PuzzleManager& manager)
	:PlayUI(stateMachine),m_undoButton(false),m_nextPuzzleButton(false),m_manager(manager)
{
	m_undoPic.setTexture(Assets::instance().getUITexture("undo"));
	m_undoPic.setPosition(1100, 80);
	m_undoPic.setColor(sf::Color(0, 0,0,100));
	m_puzzleName.setFont(Assets::instance().getFont());
	m_puzzleName.setPosition({ 950, 370 });
	m_puzzleName.setCharacterSize(15);
	m_puzzleName.setString("Puzzle Time");
}
void PuzzleUI::draw(sf::RenderWindow& window)
{

	PlayUI::draw(window);
	window.draw(m_undoPic);
	window.draw(m_puzzleName);
	if (m_undoButton)
		m_undo->draw(window);

	if (m_nextPuzzleButton)
		m_next->draw(window);
}

void PuzzleUI::initButtons(GameManager& manager)
{
	newBackground = false;
	sf::Sprite pic;
	pic.setTexture(Assets::instance().getUITexture("undo"));
	PlayUI::initButtons(manager);
	m_undo=(std::make_unique<Button>(pic,
		std::make_unique<UndoPuzzleCommand>(m_stateMachine, *this, manager),
		sf::Vector2f(1100, 80)));
	pic.setTexture(Assets::instance().getUITexture("next"));
	m_next = (std::make_unique<Button>(pic,
		std::make_unique<NextPuzzleCommand>(m_stateMachine, m_manager),
		sf::Vector2f(1100, 160)));
}

void PuzzleUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
	if (m_undoButton) 
		if (m_undo->getGlobalBounds().contains(loc)) {
			m_undo->click();
			m_undoButton = false;
		}

	if (m_nextPuzzleButton)
		if (m_next->getGlobalBounds().contains(loc)) {
			m_next->click();
			m_puzzleName.setString(m_manager.getName());
			m_nextPuzzleButton = false;
		}
}

void PuzzleUI::setName(std::string name)
{
	m_puzzleName.setString(name);
}

void PuzzleUI::needUndo()
{
	m_undoButton = true;
}

void PuzzleUI::needNext()
{
	m_nextPuzzleButton = true;
}

bool PuzzleUI::isUndo() const
{
	return !m_undoButton;
}

bool PuzzleUI::isNew() const
{
	return !m_nextPuzzleButton;
}
