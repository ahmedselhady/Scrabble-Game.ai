#pragma once

enum GameMode
{
	/**
	 * TEACHER-MODE: if a human player is playing against the AI
	 * AI_MODE: if an AI plays against another AI
	*/
	TEACHER_MODE,
	COMPUTER_MODE
};

enum GamePhase
{
	/**
	 * MID_GAME_MODE: the state of the game from the begining or from a mid game state
	 * PREEND_GAME_MODE: if the bag of tiles has 9 tiles or less
	 * END_GAME_MODE: if the bag of tiles is empty
	*/
	MID_GAME_MODE,
	PREEND_GAME_MODE,
	END_GAME_MODE
};

enum AgentResponse
{
	/**
	 * BEST_MOVE: if the move is the best move Agent could think of
	 * SUGGEST_BETTER_MOVE: if the agent could think of a better move than played by human
     * CONGRATULATION: if it were better than the Agent's guess
	*/
	BEST_MOVE,
	SUGGEST_BETTER_MOVE,
	CONGRATULATION
};
