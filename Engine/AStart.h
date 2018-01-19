#pragma once
#include "Board.h"
#include <algorithm>

class AStart
{
private:
	class Node
	{
	public:
		Node(VecI pos)
			:
			pos(pos)
		{}
		bool UpdateCost(VecI goalPos, VecI newprevPos = {-1,-1}, int newgcost = 0)
		{
			if (newgcost < gcost)
			{
				prevPos = newprevPos;
				gcost = newgcost;
				fcost = (goalPos - pos).GetLengthSq() + (float)gcost;
				return true;
			}
			return false;
		}
	public:
		int gcost = std::numeric_limits<int>::max();
		float fcost = std::numeric_limits<float>::max();
		VecI prevPos = {-1,-1};
		VecI pos;
		bool isVisited = false;
	};
public:
	AStart(int width, int height)
		:
		width(width),
		height(height)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				nodes.push_back(Node(VecI(x,y )));
			}
		}
		
	}
	bool ComputePath(const VecI& botPos, const VecI& goalPos,Board& board)
	{
		std::vector<VecI> queue;
		queue.emplace_back(botPos);
		NoteAt(botPos).UpdateCost(goalPos);
		NoteAt(botPos).isVisited = true;
		auto pred = [this](const VecI& rhs, const VecI& lhs)
		{
			return this->NoteAt(rhs).fcost > this->NoteAt(lhs).fcost;
		};
		while (!queue.empty())
		{
			const auto base = queue.back();
			queue.pop_back();
			for (int i = 0; i < 4; i++)
			{
				auto checkPos = base + dirs[i];
				if (checkPos.x >= 0 && checkPos.x < width && checkPos.y >= 0 && checkPos.y < height)
				{
					auto TileAt = board.TileAt(checkPos.x, checkPos.y).GetTileType();
					if (TileAt == Tile::TileType::Floor || TileAt == Tile::TileType::Goal)
					{
						if (NoteAt(checkPos).UpdateCost(goalPos, base, NoteAt(base).gcost + 1))
						{
							if (!NoteAt(checkPos).isVisited)
							{
								queue.push_back(checkPos);
								board.TileAt(checkPos.x, checkPos.y).isCheck = true;
								NoteAt(checkPos).isVisited = true;
								if (TileAt == Tile::TileType::Goal)
								{
									break;
								}
							}
						}
					}
				}
			}
			std::sort(queue.begin(), queue.end(), pred);
		}

		while (!queue.empty())
		{
			const auto base = queue.back();
			queue.pop_back();
			for (int i = 0; i < 4; i++)
			{
				auto checkPos = base + dirs[i];
				if (checkPos.x >= 0 && checkPos.x < width && checkPos.y >= 0 && checkPos.y < height)
				{
					auto TileAt = board.TileAt(checkPos.x, checkPos.y).GetTileType();
					if (NoteAt(checkPos).isVisited)
					{
						if (TileAt == Tile::TileType::Floor || TileAt == Tile::TileType::Goal)
						{
							NoteAt(checkPos).UpdateCost(goalPos, base, NoteAt(base).gcost + 1);
						}
					}
				}
			}
			std::sort(queue.begin(), queue.end(), pred);
		}
		if (NoteAt(goalPos).prevPos != VecI(-1,-1))
		{
			auto trace = goalPos;
			while (NoteAt(trace).prevPos != VecI(-1, -1))
			{
				path.emplace_back(trace);
				board.TileAt(trace.x, trace.y).isPath = true;
				trace = NoteAt(trace).prevPos;
			}
			path.emplace_back(botPos);
			std::reverse(path.begin(), path.end());
			return true;
		}
		else
		{
			return false;
		}
	}
	Node& NoteAt(const VecI& pos)
	{
		return nodes[pos.y * width + pos.x];
	}
	const auto& getpath() const
	{
		return path;
	}
private:
	int width;
	int height;
	std::vector<Node> nodes;
	std::vector<VecI> path;
	std::vector<VecI> dirs = { {1,0},{0,1},{-1,0},{0,-1} };
};