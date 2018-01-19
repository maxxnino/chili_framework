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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
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
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		isstatr = true;
	}
	if (wnd.kbd.KeyIsPressed('Q'))
	{
		board.ClearBoard();
	}

	if (wnd.kbd.KeyIsPressed('E'))
	{
		board.ClearWall();
	}
	
	if (wnd.kbd.KeyIsPressed(VK_CONTROL))
	{
		while (!wnd.mouse.IsEmpty())
		{
			const Mouse::Event e = wnd.mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				goal.ChangePos(wnd.mouse.GetPos(), board);
			}
			if (e.GetType() == Mouse::Event::Type::RPress)
			{
				bot.ChangePos(wnd.mouse.GetPos(), board);
			}
		}
	}
	else if (wnd.mouse.RightIsPressed())
	{
		wall.BuildWall(wnd.mouse.GetPos(), board);
	}
	else
	{
		while (!wnd.mouse.IsEmpty())
		{
			const Mouse::Event e = wnd.mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				wall.ToggleWall(wnd.mouse.GetPos(), board);
			}
		}
	}

	if (isstatr)
	{
		bot.Update(goal,board);
	}
}

void Game::ComposeFrame()
{
	board.Draw(gfx);
}
