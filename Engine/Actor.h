#pragma once
#include "Rect.h"
#include "Graphics.h"

class Actor
{
public:
	Actor(VecF pos, int size, Color color, float moveSpeed = 1)
		:
		pos(pos),
		size(size),
		color(color),
		moveSpeed(moveSpeed)
	{}
	void Draw(Graphics& gfx) const
	{
		gfx.DrawActor(static_cast<VecI>(pos + VecF(0.5f,0.5f)), size, color);
	}
	void MoveLeft(float dt)
	{
		pos.x -= moveSpeed * dt;
	}
	void MoveRight(float dt)
	{
		pos.x += moveSpeed * dt;
	}
	void MoveUp(float dt)
	{
		pos.y -= moveSpeed * dt;
	}
	void MoveDown(float dt)
	{
		pos.y += moveSpeed * dt;
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
	float moveSpeed;
};