#pragma once
class Bullet;
class BulletState
{
public:
	virtual void excute(Bullet* bullet, float dt) = 0;
};
class StateStart : public BulletState
{
public:
	virtual void excute(Bullet* bullet, float dt) override;
private:
	float curTime = 0.0f;
	float EndTime = 0.25f;
};
class StateFlying : public BulletState
{
public:
	virtual void excute(Bullet* bullet, float dt) override;
};
class StateImpact : public BulletState
{
public:
	virtual void excute(Bullet* bullet, float dt) override;
};