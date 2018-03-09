#pragma once
#include "Rect.h"
#include "Graphics.h"

class Actor
{
public:
	Actor(VecF pos, float size, Color color, float speed)
		:
		pos(pos),
		size(size),
		color(color),
		speed(speed)
	{}

	float DotProduct(const VecF& A, const VecF& B) const
	{
		return A.x * B.x + A.y * B.y;
	}
	void Draw(Graphics& gfx) const
	{
		gfx.DrawActor((VecI)pos, (int)size ,color);
	}
	void Update(VecF dir,float dt)
	{
		pos += dir * speed * dt;
	}
	const VecF& GetPos() const
	{
		return pos;
	}

protected:
	VecF pos;
	float size;
	Color color;
	float speed;
};