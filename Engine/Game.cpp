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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	hero({ 400.0f,300.0f }, 20.0f, Colors::Blue, 300.0f),
	rng(std::random_device()())
{
	std::uniform_int_distribution<int> xDist(100, 700);
	std::uniform_int_distribution<int> yDist(100, 500);
	for (size_t i = 0; i < 10; i++)
	{
		walls.emplace_back(RectI({ xDist(rng),yDist(rng) }, 50, 50));
	}
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
	VecF dir = { 0.0f,0.0f };
	if (wnd.kbd.KeyIsPressed('A'))
	{
		dir.x = -1.0f;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		dir.x = 1.0f;
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		dir.y = -1.0f;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		dir.y = 1.0f;
	}
	std::vector<Mouse::Event::Type> mouseEvent;
	while (!wnd.mouse.IsEmpty())
	{
		mouseEvent.push_back(wnd.mouse.Read().GetType());
	}
	hero.Update(dir,dt, mouseEvent,wnd.mouse, walls);
}

void Game::ComposeFrame()
{
	for (auto& w : walls)
	{
		gfx.DrawRect(w, Colors::Red);
	}
	
	hero.Draw(gfx);
}
