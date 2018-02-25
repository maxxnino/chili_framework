#pragma once

#include "Actor.h"

class Boss : public Actor
{
public:
	Boss()
		:
		Actor({ 200,100 }, 20,Colors::Red,150)
	{}
private:
};
