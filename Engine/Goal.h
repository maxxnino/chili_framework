#pragma once
#include "Board.h"

class Goal
{
public:
	void ChangePos(const VecI& mousePos,Board& board)
	{
		VecI newPos = board.posAtMouse(mousePos);
		Tile& tileat = board.TileAt(newPos.x, newPos.y);
		if (tileat.GetTileType() == Tile::TileType::Floor)
		{
			if (pos != VecI(-1, -1))
			{
				board.TileAt(pos.x, pos.y).UnSetGoal();
			}
			tileat.SetGoal();
			pos = newPos;
		}
	}
	const VecI& GetPos() const
	{
		return pos;
	}
private:
	VecI pos = {-1,-1};
};