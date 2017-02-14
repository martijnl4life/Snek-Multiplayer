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
		void SetLocation(Location& loc);
		const Location& GetLocation() const;
		void DrawG(Board& brd) const;
	private:
		static constexpr Color cg = Colors::Red;
		Location locG;
	};
//private:
//	class SlowDown
//	{
//	public:
//	private:
//		Location loc;
//	};
public:
	Goal() = default;
	Goal( std::mt19937& rng,const Board& brd,const Snake& snake );
	void Draw( Board& brd ) const;
	Location CompareLocGrowRespawn(std::mt19937 & rng, const Board & brd, const Snake & snake, const Location loc);
	Location CompareLocGrow(const Location loc) const;
private:
	static constexpr Color c = Colors::Red;
	static constexpr int growN = 10;
	Location loc;
	Grow grow[growN];
};