#include "Bullet.h"
#include "Actor.h"
void CycloneBullet::OnFlying(float dt)
{
	cycloneDir = { cycloneDir.x * cosAlpha - cycloneDir.y * sinAlpha, cycloneDir.x * sinAlpha + cycloneDir.y * cosAlpha };
	pos += dir * speed * 0.5f * dt + cycloneDir * speed * dt;
	curTimeImpact += dt;
	if (curTimeImpact >= EndTimeImpact)
	{
		isImpact = true;
		curTimeImpact = 0.0f;
	}
}

void CycloneBullet::OnStart(float dt)
{
	cycloneDir = dir;
	pos += dir * speed * dt;
}

void CycloneBullet::OnImpact(float dt)
{
	curTimeImpact += dt;
	if (curTimeImpact >= EndTimeImpact)
	{
		isDead = true;
	}
	else
	{
		cycloneDir = { cycloneDir.x * cosAlpha - cycloneDir.y * sinAlpha, cycloneDir.x * sinAlpha + cycloneDir.y * cosAlpha };
		pos += cycloneDir * speed * dt * ((EndTimeImpact - curTimeImpact) / EndTimeImpact);
	}
}

bool Bullet::CheckCollision(std::vector<Actor>& enemies) const
{
	return true;
}
