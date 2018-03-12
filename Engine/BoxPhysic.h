#pragma once
#include "Rect.h"
#include "Graphics.h"
class BoxPhysic
{
public:
	BoxPhysic(VecF pos, float size, VecF vel)
		:pos(pos),size(size),vel(vel)
	{}
	void UpdatePosition(float dt);
	void UpdateRect();
	bool CheckCollision(BoxPhysic& otherBox);
	void CorrectCollision(BoxPhysic& otherBox);
	void UpdateVel(const VecF& newVel)
	{
		vel += newVel;
	}
	const RectF& GetRect() const
	{
		return rect;
	}
	const VecF& GetVel() const
	{
		return vel;
	}
	const VecF& GetPosition() const
	{
		return pos;
	}
	void ClamScreen();
private:
	VecF pos;
	float size;
	VecF vel;
	RectF rect;
};