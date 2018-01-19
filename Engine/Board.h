#pragma once
#include "Graphics.h"
#include <cassert>
#include "Rect.h"
#include <vector>


class Tile
{
public:
	enum TileType
	{
		Goal,
		Bot,
		Wall,
		Floor,
	};
public:
	Tile(TileType tileType = TileType::Floor)
	{
		SetTile(tileType);
	}
	void ToggleWall()
	{
		assert(tileType == TileType::Wall || tileType == TileType::Floor);
		if (tileType == TileType::Floor)
		{
			SetTile(TileType::Wall);
		}
		else
		{
			SetTile(TileType::Floor);
		}
	}
	void UnSetGoal()
	{
		assert(tileType == TileType::Goal);
		SetTile(TileType::Floor);
	}
	void Clear()
	{
		SetTile(TileType::Floor);
	}
	void ClearWall()
	{
		if (tileType == TileType::Wall)
		{
			SetTile(TileType::Floor);
		}
	}
	void UnSetBot()
	{
		assert(tileType == TileType::Bot);
		SetTile(TileType::Floor);
	}
	void SetGoal()
	{
		assert(tileType == TileType::Floor || tileType == TileType::Goal);
		SetTile(TileType::Goal);
	}
	void SetBot()
	{
		assert(tileType == TileType::Floor || tileType == TileType::Bot);
		SetTile(TileType::Bot);
	}
	void Draw(const VecI& pos, const int& size, Graphics& gfx) const
	{
		if (tileType == TileType::Floor)
		{
			if (isPath)
			{
				gfx.DrawRect(pos, size, Color((unsigned char)158, (unsigned char)111, (unsigned char)139));
			}
			else if (isCheck)
			{
				gfx.DrawRect(pos, size, Color((unsigned char) 0, (unsigned char)0, (unsigned char)100 ));
			}
			else
			{
				gfx.DrawRect(pos, size, color);
			}
		}
		else
		{
			gfx.DrawRect(pos, size, color);
		}
	}
	const TileType& GetTileType() const
	{
		return tileType;
	}
private:
	void SetTile(TileType newTile)
	{
		switch (newTile)
		{
		case Tile::Goal:
			color = Colors::Red;
			break;
		case Tile::Bot:
			color = Colors::Green;
			break;
		case Tile::Wall:
			color = Colors::LightGray;
			break;
		case Tile::Floor:
			color = Colors::Blue;
			break;
		default:
			break;
		}
		tileType = newTile;
	}
public:
	bool isCheck = false;
	bool isPath = false;
private:
	TileType tileType = TileType::Floor;
	Color color;
};

class Board
{
public:
	Board()
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				tiles.emplace_back(Tile());
			}
		}
	}
	void Draw(Graphics& gfx) const
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				TileAt(x, y).Draw({ x * tileSize + padding , y * tileSize + padding }, tileSize - padding, gfx);
			}
		}
	}
	void ClearBoard()
	{
		for (auto& t : tiles)
		{
			t.Clear();
		}
	}
	void ClearWall()
	{
		for (auto& t : tiles)
		{
			t.ClearWall();
		}
	}
	VecI posAtMouse(const VecI& mousePos)
	{
		return VecI(mousePos.x / tileSize, mousePos.y / tileSize);
	}
	const Tile& TileAt(int x, int y) const
	{
		return tiles[y * width + x];
	}

	Tile& TileAt(int x, int y)
	{
		return tiles[y * width + x];
	}
private:
private:
	std::vector<Tile> tiles;
	static constexpr int tileSize = 20;
	int width = Graphics::ScreenWidth / tileSize;
	int height = Graphics::ScreenHeight / tileSize;
	static constexpr int padding = 2;
};
