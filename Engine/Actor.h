#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Keyboard.h"

class Actor
{
public:
	Actor(VecF pos, int size, Color color, unsigned int moveSpeed = 1, float accelerate = 0.05f, float decelerate = 0.03f, 
		unsigned int maxHp = 1, unsigned int maxMp = 1, unsigned int armor = 1)
		:
		pos(pos),
		size(size),
		color(color)
	{}
	void Draw(Graphics& gfx) const
	{
		gfx.DrawActor(static_cast<VecI>(pos + VecF(0.5f,0.5f)), size, color);
	}
	const VecF& GetPos() const
	{
		return pos;
	}
protected:
	VecF pos;
	int size;
	Color color;

	//Attribute Stat
	int moveSpeed;
};