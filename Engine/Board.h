#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	Board( Graphics& gfx );
	void DrawCell( const Location& loc,Color c );
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard( const Location& loc ) const;
	bool CheckForObstacle( const Location& loc ) const;
	void SpawnObstacle( std::mt19937& rng,const class Snake& snake,const class Goal& goal );
	bool CheckForPosion(const Location& loc) const;
	void SpawnPosion(std::mt19937& rng, const class Snake& snake, const class Goal& goal);
	void ReSpawnPosion(std::mt19937& rng, const class Snake& snake, const class Goal& goal, const Location& loc);
	void DrawBorder();
	void DrawObstacles();
	void DrawPosion();
private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color posionColor = Colors::Magenta;
	static constexpr int dimension = 15;
	static constexpr int cellPadding = 1;
	static constexpr int width = 48;
	static constexpr int height = 35;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int x = 30;
	static constexpr int y = 30;
	bool hasObstacle[width * height] = { false };
	bool hasPosion[width * height] = { false };
	Graphics& gfx;
};