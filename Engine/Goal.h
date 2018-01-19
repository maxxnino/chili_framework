#pragma once
#include "Board.h"

class Goal
{
public:
	void ChangePos(const VecI& mousePos,Board& board)
	{
		VecI newPos = board.posAtMouse(mousePos);
		auto& tileAt = board.TileAt(newPos.x, newPos.y);
		if (tileAt.GetTileType() == Tile::TileType::Floor)
		{
			board.TileAt(pos.x, pos.y).UnSetGoal();
			pos = newPos;
			tileAt.SetGoal();
		}
	}
private:
	VecI pos = {-1,-1};
};