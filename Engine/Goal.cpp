#include "Goal.h"

Goal::Goal( std::mt19937 & rng,const Board & brd,const Snake & snake )
{
	for (int i = 0; i < growN; i++)
	{
		std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
		std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

		Location newLoc;
		do
		{
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while (snake.IsInTile(newLoc));
		grow[i].SetLocation(newLoc);
	}
}

void Goal::Draw( Board & brd ) const
{
	for (int i = 0; i < growN; i++)
	{
		grow[i].DrawG(brd);
	}
}

Location Goal::CompareLocGrowRespawn(std::mt19937 & rng, const Board & brd, const Snake & snake, const Location loc)
{
	for (int i = 0; i < growN; i++)
	{
		if (loc == grow[i].GetLocation())
		{
			Location oldLoc = grow[i].GetLocation();;
			std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
			std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

			Location newLoc;
			do
			{
				newLoc.x = xDist(rng);
				newLoc.y = yDist(rng);
			} while (snake.IsInTile(newLoc));
			grow[i].SetLocation(newLoc);
			return oldLoc;
			break;
		}
	}
	return Location{ -1,-1 };
}

Location Goal::CompareLocGrow(const Location loc) const
{
	for (int i = 0; i < growN; i++)
	{
		if (loc == grow[i].GetLocation())
		{
			Location oldLoc = grow[i].GetLocation();;
			return oldLoc;
			break;
		}
	}
	return Location{ -1,-1 };
}

// ------------------------------ Grow block ------------------------------ \\

void Goal::Grow::SetLocation(Location & loc)
{
	locG = loc;
}

const Location & Goal::Grow::GetLocation() const
{
	return locG;
}

void Goal::Grow::DrawG(Board & brd) const
{
	brd.DrawCell(locG,cg);
}
