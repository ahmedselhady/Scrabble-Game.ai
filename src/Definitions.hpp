#pragma once

enum GameMode{
	TEACHER_MODE,
	AI_MODE
};

enum GamePhase{
	MID_GAME_MODE,
	PREEND_GAME_MODE,
	END_GAME_MODE
};

	
enum AgentResponse{
	/**
	 * BEST_MOVE: if the move is the best move Agent could think of
	 * SUGGEST_BETTER_MOVE: if the agent could think of a better move than played by human
     * CONGRATULATION: if it were better than the Agent's guess
	*/
	BEST_MOVE,
	SUGGEST_BETTER_MOVE,
	CONGRATULATION
}