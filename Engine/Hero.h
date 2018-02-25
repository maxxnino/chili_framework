#pragma once
#include "Actor.h"

class Hero : public Actor
{
public:
	Hero()
		:
		Actor({200,100},10,Colors::Blue,200)
	{}
	void Draw(Graphics& gfx) const;
private:
};