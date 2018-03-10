#include "BulletState.h"
#include "Bullet.h"

void StateStart::excute(Bullet * bullet, float dt)
{
	curTime += dt;
	if (curTime < EndTime)
	{
		bullet->OnStart(dt);
	}
	else
	{
		bullet->ChangeState(std::make_unique<StateFlying>());
	}
}

void StateFlying::excute(Bullet* bullet, float dt)
{
	bullet->OnFlying(dt);
}

void StateImpact::excute(Bullet * bullet, float dt)
{
	bullet->OnImpact(dt);
}
