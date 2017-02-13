/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	rng( std::random_device()() ),
	snek({2,2}),
	snek2({12,12}),
	goal( rng,brd,snek )
{
	sndTitle.Play( 1.0f,1.0f );
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	if( gameIsStarted )
	{
		if( !gameIsOver )
		{
			if (!gameIsInitialized)
			{
				for (int i = 0; i < brd.GetGridWidth() * brd.GetGridHeight() * posionPercentage; i++)
				{
					brd.SpawnPoison(rng, snek, snek2, goal);
				}
				gameIsInitialized = true;
			}
			// player 1
			if (wnd.kbd.KeyIsPressed(VK_UP))             delta_loc = { 0,-1 };
			else if( wnd.kbd.KeyIsPressed( VK_DOWN ) )   delta_loc = { 0,1 };
			else if( wnd.kbd.KeyIsPressed( VK_LEFT ) )   delta_loc = { -1,0 };
			else if( wnd.kbd.KeyIsPressed( VK_RIGHT ) )  delta_loc = { 1,0 };
			//player 2
			if (wnd.kbd.KeyIsPressed('W'))        delta_loc2 = { 0,-1 };
			else if (wnd.kbd.KeyIsPressed('S'))   delta_loc2 = { 0,1 };
			else if (wnd.kbd.KeyIsPressed('A'))   delta_loc2 = { -1,0 };
			else if (wnd.kbd.KeyIsPressed('D'))   delta_loc2 = { 1,0 };

			//player 1
			snekMoveCounter += dt * poisonHit;
			if( snekMoveCounter >= snekMovePeriod )
			{
				snekMoveCounter -= snekMovePeriod;
				const Location next = snek.GetNextHeadLocation( delta_loc );
				if( !brd.IsInsideBoard( next ) ||
					snek.IsInTileExceptEnd( next ) ||
					snek2.IsInTile(next) ||
					brd.CheckForObstacle( next ) )
				{
					gameIsOver = true;
					sndFart.Play();
					sndMusic.StopAll();
				}
				else
				{
					if( next == goal.GetLocation() )
					{
						snek.GrowAndMoveBy( delta_loc );
						goal.Respawn( rng,brd,snek );
						for (int i = 0; i < 4; i++)
						{
							brd.SpawnObstacle(rng, snek, snek2, goal);
						}
						sfxEat.Play( rng,0.8f );
					}
					else if ( brd.CheckForPoison(next) )
					{
						poisonHit += 0.03;
						brd.ReSpawnPoison(rng, snek, snek2, goal, next);
						snek.MoveBy(delta_loc);
					}
					else
					{
						snek.MoveBy( delta_loc );
					}
					sfxSlither.Play( rng,0.08f );
				}
			}
			//player 2
			snekMoveCounter2 += dt * poisonHit2;
			if (snekMoveCounter2 >= snekMovePeriod2)
			{
				snekMoveCounter2 -= snekMovePeriod2;
				const Location next2 = snek2.GetNextHeadLocation(delta_loc2);
				if (!brd.IsInsideBoard(next2) ||
					snek2.IsInTileExceptEnd(next2) ||
					snek.IsInTile(next2) ||
					brd.CheckForObstacle(next2))
				{
					gameIsOver = true;
					sndFart.Play();
					sndMusic.StopAll();
				}
				else
				{
					if (next2 == goal.GetLocation())
					{
						snek2.GrowAndMoveBy(delta_loc2);
						goal.Respawn(rng, brd, snek2);
						for (int i = 0; i < 4; i++)
						{
							brd.SpawnObstacle(rng, snek2, snek, goal);
						}
						sfxEat.Play(rng, 0.8f);
					}
					else if (brd.CheckForPoison(next2))
					{
						poisonHit2 += 0.03;
						brd.ReSpawnPoison(rng, snek2, snek, goal, next2);
						snek2.MoveBy(delta_loc2);
					}
					else
					{
						snek2.MoveBy(delta_loc2);
					}
					sfxSlither.Play(rng, 0.08f);
				}
			}
			snekMovePeriod = std::max( snekMovePeriod - dt * snekSpeedupFactor,snekMovePeriodMin );
			snekMovePeriod2 = std::max(snekMovePeriod2 - dt * snekSpeedupFactor2, snekMovePeriodMin2);
		}
	}
	else
	{
		if( wnd.kbd.KeyIsPressed( VK_RETURN ) )
		{
			sndMusic.Play( 1.0f,0.6f );
			gameIsStarted = true;
		}
	}
}

void Game::ComposeFrame()
{
	if( gameIsStarted )
	{
		brd.DrawPosion();
		brd.DrawObstacles();
		snek.Draw( brd );
		snek2.Draw(brd);
		goal.Draw( brd );
		if( gameIsOver )
		{
			SpriteCodex::DrawGameOver( 350,265,gfx );
		}
		brd.DrawBorder();
	}
	else
	{
		SpriteCodex::DrawTitle( 290,225,gfx );
	}
}
