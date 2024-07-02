#pragma once
#include "PlayUI.h"
#include "PuzzleManager.h"

typedef std::unique_ptr<Button> buttonPtr;

/*
* Represents the UI and actions of the Puzzle gamemode.
*/
class PuzzleUI : public PlayUI {
public:
	PuzzleUI(StateMachine& stateMachine,PuzzleManager& manager);
	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
	virtual void buttonClicked(const sf::Vector2f& loc)override;
	void setName(std::string name);
	void needUndo();
	void needNext();
	bool isUndo()const;
	bool isNew()const;

private:
	bool m_undoButton;
	bool m_nextPuzzleButton;

	sf::Sprite m_undoPic;
	sf::Text m_puzzleName;
	buttonPtr m_undo;
	buttonPtr m_next;
	PuzzleManager& m_manager;
};

