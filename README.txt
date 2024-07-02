//***********************************************
OOP2_
//***********************************************

//***********************************************
Authors: 
	Ilya Kirshtein	ID: 323299362
	Guy Danin  ID:205372105
//***********************************************

//***********************************************
Overview:
//***********************************************
This project is a Chess Engine. 
The game provides the following features:

An option to play against another player or against the computer (AI).
An option for solving chess puzzles.
An option to review past games.
The AI leverages the Minimax algorithm with alpha-beta pruning to make decisions. 
The game architecture incorporates various design patterns to ensure clean code, scalability, and maintainability.

//***********************************************
Created Files:
//***********************************************
Command Classes
	BackToMenuCommand.h: Command to navigate back to the main menu.
	ButtonCommand.h: Base class for all button commands.
	ChangeGameStateCommand.h: Command to change the current game state.
	ExitCommand.h: Command to exit the game.
	NextPuzzleCommand.h: Command to load the next puzzle.
	NextStateCommand.h: Command to move to the next state.
	PuzzleCommand.h: Command related to puzzle management.
	PVPCommand.h: Command for Player vs Player mode.
	RematchCommand.h: Command to initiate a rematch.
	UndoPuzzleCommand.h: Command to undo the last puzzle move.
	VBlackAICommand.h: Command for setting up the AI as black.
	VWhiteAICommand.h: Command for setting up the AI as white.
State Classes
	GameOverState.h: Represents the game over state.
	GameState.h: Base class for all game states.
	PlayerXPromotionState.h: State for player promotion.
	PlayerXTurnState.h: State for player's turn.
	PuzzleGameState.h: State for puzzle gameplay.
	ReviewState.h: State for reviewing the game.
	WaitGameState.h: State for waiting during the game.
	HistoryState.h: Manages the history state of the game.
UI Classes
	EndGameUI.h: Handles the UI for the end game screen.
	GameUI.h: Base class for all game UI elements.
	PlayUI.h: Handles the UI for the main gameplay screen.
	PuzzleUI.h: Handles the UI for puzzle mode.
	ReviewUI.h: Handles the UI for the review mode.
Factory Classes
	BlackAICreator.h: Creates an AI for black pieces.
	GameHistoryCreator.h: Creates a game history object.
	MainMenuCreator.h: Creates the main menu.
	MenuCreator.h: Base class for menu creation.
	MenuFactory.h: Factory class for creating menus.
	PlayMenuCreator.h: Creates the play menu.
	PuzzleMenuCreator.h: Creates the puzzle menu.
	WhiteAICreator.h: Creates an AI for white pieces.
	FenAlgorithm.h: Translates FEN strings to board positions.
Manager Classes
	GameManager.h: Manages the overall game, including state transitions and player management.
	PuzzleManager.h: Manages puzzles, including loading, deleting, and selecting puzzles.
SFML Classes
	SFMLBoard.h: Handles rendering of the chessboard using SFML.
	SFMLPiece.h: Represents a chess piece in SFML.
	SFMLPieceFactory.h: Factory class for creating SFML chess pieces.
	Tile.h: Represents a tile on the chessboard.
Controller Classes
	AIController.h: Manages the AI controller.
	Controller.h: Base class for controllers.
	PlayerController.h: Manages the player controller.
Test Classes
	TestAI.h: Class for testing AI functionality.
Menu Classes
	Menu.h: Handles the game menu.
	MenuState.h: Manages the menu state.
	StateMachine.h: Manages different states in the game.
Observer Classes 
	IObservable.h: Manages a list of observers and notifies them of events.
	IObserver.h: Represents an observer that receives updates from observables.
Logic Classes
	IGenerate.h: Interface for generating moves.
	NBoard.h: Manages the board state and moves.
	OpeningBook.h: Manages the opening book for chess moves.
	PieceLogic.h: Contains logic for piece movements and checks.
	PromotionBox.h: Handles pawn promotion in chess.
Utility Classes
	Assets.h: Singleton class that manages game assets like textures, fonts, and sounds.
	BoardStack.h: Saves each move played and can restore the last move.
	Button.h: Represents a button in the game.
	Utilities.h: Contains utility functions and constants used throughout the project


//***********************************************
Data Structures:
//***********************************************

BoardStack
Role: Saves each move played, provides the last move, and saves the game to a file.

StateMachine::std::stack<statePtr> m_stateStack 
Choosing this data structure with shared ptr for the reason to access each 
time only the end of the data structure for insertion and deletion. 
The choice of shared ptr is because each state holds the next state, 
so there will be several objects that will point to the same state

NBoard
Role: With this data structure we guarantee efficient operations for running the chess engine 
This class holds an array of size 64
Each element in the array is an int whose first 3 bits hold the type of piece, 
the 3rd and 4th bits hold the color and the 5th bit holds whether the piece has moved yet


//***********************************************
Algorithms:
//***********************************************
Minimax Algorithm with Alpha-Beta Pruning
Role:
The minimax algorithm will get a board position, and recusivly play all possible moves, 
and on those moves will apply minimax, up to depth.
for each move it will evaluate the board and return a value,
overall this will return a move that has the highest value.
The algorithm also uses alpha beta pruning:
minmax plays both black and white moves, so
it will 'cut' and stop the recursion if it finds moves that are better for the opponent,
it assumes the opponent will make the best move for them, and so we reduce the number 
of positions we need to check.

Fen Algorithm
Role: Translates FEN strings to board positions, used to set up initial positions and for testing.

PieceLogic
Role:This class holds all the moves and rules that exist in chess in relation to a single piece
The main goal in creating this class is to calculate all the moves in the most efficient way. 
While calculating the king's risk in relation to the opponent, 
we can know that a piece calculates its moves only if it is possible without exposing the king to chess

//***********************************************
DESIGN:
//***********************************************
The project design incorporates several design patterns to promote clean code architecture, scalability, and maintainability. Key design patterns include:

Command Pattern: Used for implementing commands such as menu actions, game state changes, and player moves.
State Pattern: Used for managing the different states of the game, such as playing, paused, game over, and various UI states.
Factory Pattern: Used for creating instances of various game components such as AI, menus, and game states.
Observer Pattern: Used to create a subscription mechanism to allow multiple objects to listen to and react to events or changes in state.


//***********************************************
Remarks:
//***********************************************
This project demonstrates the use of object-oriented programming principles and design patterns in a complex application. 
It also highlights the integration of AI algorithms in game development.


//***********************************************
Known bugs:
//***********************************************

