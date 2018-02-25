#pragma once
#include "Actor.h"

class Command
{
public:
	virtual void execute(Actor& actor,float dt) const = 0;
};

class MoveLeft : public Command
{
public:
	virtual void execute(Actor& actor, float dt) const
	{
		actor.MoveLeft(dt);
	}
};
class MoveRight : public Command
{
public:
	virtual void execute(Actor& actor, float dt) const
	{
		actor.MoveRight(dt);
	}
};
class MoveUp : public Command
{
public:
	virtual void execute(Actor& actor, float dt) const
	{
		actor.MoveUp(dt);
	}
};
class MoveDown : public Command
{
public:
	virtual void execute(Actor& actor, float dt) const
	{
		actor.MoveDown(dt);
	}
};