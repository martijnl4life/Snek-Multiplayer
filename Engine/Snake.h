#pragma once

#include "Board.h"


class Snake
{
private:	
	class Segment
	{
	public:
		void InitHead( const Location& loc, const Color& c);
		void InitBody( Color c );
		void Follow( const Segment& next );
		void MoveBy( const Location& delta_loc );
		void Draw( Board& brd ) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake( const Location& loc, const Color& c);
	void Respawn(const Location& loc);
	void MoveBy( const Location& delta_loc );
	Location GetNextHeadLocation( const Location& delta_loc ) const;
	void GrowAndMoveBy( const Location& delta_loc );
	void Draw( Board& brd ) const;
	void Shrink();
	bool IsInTileExceptEnd( const Location& target ) const;
	bool IsInTile( const Location& target ) const;
	void SetHeadColor(const Color& c);

private:
	Color headColor;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};