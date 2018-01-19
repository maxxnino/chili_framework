#pragma once

#include "Board.h"

class Bot
{
public:
	void ChangePos(const VecI& mousePos, Board& board)
	{
		VecI newPos = board.posAtMouse(mousePos);
		auto& tileAt = board.TileAt(newPos.x, newPos.y);
		if (tileAt.GetTileType() == Tile::TileType::Floor)
		{
			board.TileAt(pos.x, pos.y).UnSetGoal();
			pos = newPos;
			tileAt.SetBot();
		}
	}
private:
	VecI pos = {-1,-1};
};
