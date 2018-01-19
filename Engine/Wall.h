#pragma once
#include "Board.h"

class Wall
{
public:
	void ToggleWall(const VecI& mousePos, Board& board)
	{
		VecI newPos = board.posAtMouse(mousePos);
		auto& tileAt = board.TileAt(newPos.x, newPos.y);
		if (tileAt.GetTileType() == Tile::TileType::Floor || tileAt.GetTileType() == Tile::TileType::Wall)
		{
			tileAt.ToggleWall();
		}
	}
	void BuildWall(const VecI& mousePos, Board& board)
	{
		VecI newPos = board.posAtMouse(mousePos);
		auto& tileAt = board.TileAt(newPos.x, newPos.y);
		if (tileAt.GetTileType() == Tile::TileType::Floor)
		{
			tileAt.ToggleWall();
		}
	}
};
