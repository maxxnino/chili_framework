#pragma once

#include "Actor.h"

class Boss : public Actor
{
public:
	Boss()
		:
		Actor({800.0f,600.0f}, 20,Colors::Red,200,0.1,1.0f)
	{}
private:
};
