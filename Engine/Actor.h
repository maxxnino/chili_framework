#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Bullet.h"

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
		//draw bullets
		for (auto& b : bullets)
		{
			b->Draw(gfx);
		}
	}
	void Update(VecF dir,float dt, const std::vector<Mouse::Event::Type>& mouseEvent, Mouse& mouse)
	{
		pos += dir * speed * dt;
		Shoot(mouseEvent, mouse);
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
	const VecF& GetPos() const
	{
		return pos;
	}
private:
	void Shoot(const std::vector<Mouse::Event::Type>& mouseEvent,Mouse& mouse)
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
	VecF pos;
	float size;
	Color color;
	float speed;
};