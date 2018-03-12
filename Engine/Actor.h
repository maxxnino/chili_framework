#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Bullet.h"
#include "PhysicEngine.h"

class Actor
{
public:
	Actor(VecF pos, float size, Color color, float speed, PhysicEngine& physicEngine)
		:
		size(size),
		color(color),
		speed(speed)
	{
		physicEngine.AddPhysicObject(BoxPhysic(pos, size, { 0.0f,0.0f }));
		indexPhysicEngine = (int)physicEngine.GetPhysicObjects().size() - 1;
	}

	float DotProduct(const VecF& A, const VecF& B) const
	{
		return A.x * B.x + A.y * B.y;
	}
	void Draw(Graphics& gfx,const VecF& pos) const
	{
		gfx.DrawActor((VecI)pos, (int)size, color);
		//draw bullets
		for (auto& b : bullets)
		{
			b->Draw(gfx);
		}
	}
	void Update(VecF dir,float dt, const std::vector<Mouse::Event::Type>& mouseEvent, Mouse& mouse,BoxPhysic& box)
	{
		float lenSq = (box.GetVel() + dir * speed * dt).GetLengthSq();
		if (lenSq < 400.0f * 400.0f)
		{
			box.UpdateVel(dir * speed * dt);
		}
		//shoot butllet
		Shoot(mouseEvent, mouse, box.GetPosition());
		for (int i = 0; i < bullets.size();)
		{
			bullets[i]->Update(dt);
			if (bullets[i]->GetIsRemove())
			{
				std::swap(bullets[i], bullets.back());
				bullets.pop_back();
			}
			else
			{
				i++;
			}
		}
	}
	int GetIndexPhysicObject()
	{
		return indexPhysicEngine;
	}
private:
	void Shoot(const std::vector<Mouse::Event::Type>& mouseEvent,Mouse& mouse,const VecF& pos)
	{
		for (const auto& e : mouseEvent)
		{
			if (e == Mouse::Event::Type::LPress)
			{
				const VecF dir = ((VecF)mouse.GetPos() - pos).GetNormalized();
				bullets.emplace_back(std::make_unique<CycloneBullet>(pos, 3.0f, dir, 400.0f, Colors::Green));
			}
		}
	}
protected:
	std::vector<std::unique_ptr<Bullet>> bullets;
	int indexPhysicEngine;
	float size;
	Color color;
	float speed;
};