#pragma once

#include "Board.h"
#include "Goal.h"
#include "AStart.h"

class Bot
{
public:
	void ChangePos(const VecI& mousePos, Board& board)
	{
		VecI newPos = board.posAtMouse(mousePos);
		if (board.TileAt(newPos.x, newPos.y).GetTileType() == Tile::TileType::Floor)
		{
			if (pos != VecI(-1,-1))
			{
				board.TileAt(pos.x, pos.y).UnSetBot();
			}
			board.TileAt(newPos.x, newPos.y).SetBot();
			pos = newPos;
		}
	}
	void Update(const Goal& goal, Board& board)
	{
		if (!isDone)
		{
			Plan(goal, board);
		}
		else
		{
			if (pos != goal.GetPos())
			{
				if (!astart.getpath().empty())
				{
					count++;
					if (count >= 3)
					{
						auto i = std::find(astart.getpath().begin(), astart.getpath().end(), pos);
						moveTo(*std::next(i), board);
						count = 0;
					}
				}
			}

		}
	}
private:
	void moveTo(const VecI& newPos, Board& board)
	{
		auto& tileAt = board.TileAt(newPos.x, newPos.y);
		if (tileAt.GetTileType() == Tile::TileType::Floor)
		{
			board.TileAt(pos.x, pos.y).UnSetBot();
			pos = newPos;
			tileAt.SetBot();
		}
	}
	void Plan(const Goal& goal, Board& board)
	{
		if (astart.ComputePath(pos, goal.GetPos(), board))
		{
			isDone = true;
		}
		else
		{
			isDone = true;
		}
	}
private:
	int count = 0;
	VecI pos = {-1,-1};
	bool isDone = false;
	AStart astart = {Graphics::ScreenWidth/20,Graphics::ScreenHeight/20};
};
