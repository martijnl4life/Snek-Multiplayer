#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Goal
{
private:
	class Grow 
	{
	public:
		void SetLocation(Location& loc);											// if you add a new goal, remember to update the functions in board too
		const Location& GetLocation() const;
		void DrawG(Board& brd) const;
	private:
		static constexpr Color cg = Colors::Green;
		Location locG;
	};
private:
	class SlowDown
	{
	public:
		void SetLocation(Location& loc);
		const Location& GetLocation() const;
		void DrawS(Board& brd) const;
	private:
		static constexpr Color cs = Colors::Blue;
		Location locS;
	};
public:
	Goal() = default;
	Goal( std::mt19937& rng,const Board& brd,const Snake& snake );
	void DrawGrow( Board& brd ) const;
	void DrawSlow(Board& brd) const;
	Location CompareLocGrowRespawn(std::mt19937 & rng, const Board & brd, const Snake & snake, const Location loc);
	Location CompareLocGrow(const Location loc) const;
	Location CompareLocSlowRespawn(std::mt19937 & rng, const Board & brd, const Snake & snake, const Location loc);
	Location CompareLocSlow(const Location loc) const;
private:
	static constexpr Color c = Colors::Red;
	static constexpr int growN = 20;
	static constexpr int slowN = 8;
	Grow grow[growN];
	SlowDown slow[slowN];
};