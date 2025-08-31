# SFML Chess Engine

[![Watch on YouTube](https://img.shields.io/badge/Watch%20on-YouTube-red?logo=youtube&style=for-the-badge)](https://www.youtube.com/watch?v=P3rxAs5GV68)

## Authors: 

Ilya Kirshtein

Guy Danin

## Overview:

This project is a Chess Engine. 

The game provides the following features:

An option to play against another player or against the computer (AI).

An option for solving chess puzzles.

An option to review past games.

The AI leverages the Minimax algorithm with alpha-beta pruning to make decisions. 

The game architecture incorporates various design patterns to ensure clean code, scalability, and maintainability.

White AI runs on a single thread

Black AI runs multiple threads


## Data Structures:

### BoardStack

Role: Saves each move played, provides the last move, and saves the game to a file.

StateMachine::std::stack<statePtr> m_stateStack 
Choosing this data structure with shared ptr for the reason to access each 
time only the end of the data structure for insertion and deletion. 
The choice of shared ptr is because each state holds the next state, 
so there will be several objects that will point to the same state.
Also when we pop a state, we dont want to waste and rebuild it.

### NBoard
Role: With this data structure we guarantee efficient operations for running the chess engine 
This class holds an array of size 64
Each element in the array is an int whose first 3 bits hold the type of piece, 
the 3rd and 4th bits hold the color and the 5th bit holds whether the piece has moved yet

## Algorithms:

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

## DESIGN:

The project design incorporates several design patterns to promote clean code architecture, scalability, and maintainability. Key design patterns include:

Command Pattern: Used for implementing commands such as menu actions, game state changes, and player moves.

State Pattern: Used for managing the different states of the game, such as playing, paused, game over, and various UI states.

Factory Pattern: Used for creating instances of various game components such as AI, menus, and game states.

Observer Pattern: Used to create a subscription mechanism to allow multiple objects to listen to and react to events or changes in state.


This project demonstrates the use of object-oriented programming principles and design patterns in a complex application. 

It also highlights the integration of AI algorithms in game development.


