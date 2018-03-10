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
	void Update(VecF dir,float dt, const std::vector<Mouse::Event::Type>& mouseEvent, Mouse& mouse, const std::vector<RectI>& wall)
	{
		pos += vel * dt;
		rect = { int(pos.x - size),int(pos.y - size),int(pos.x + size),int(pos.y + size) };
		for (const auto& w : wall)
		{
			if (rect.isOverLap(w))
			{
				CorrectCollision(w);
			}
		}
		//screen collision
		if (rect.left < 0.0f)
		{
			vel.x = -vel.x;
			pos.x = size;
		}
		if (rect.top < 0.0f)
		{
			vel.y = -vel.y;
			pos.y = size;
		}
		if (rect.right >=  Graphics::ScreenWidth)
		{
			vel.x = -vel.x;
			pos.x += Graphics::ScreenWidth - rect.right;
		}
		if (rect.bottom >= Graphics::ScreenHeight)
		{
			vel.y = -vel.y;
			pos.y += Graphics::ScreenHeight - rect.bottom;
		}
		//shoot butllet
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
	void CorrectCollision(const RectI& wall)
	{
		if (vel.x > 0 )
		{
			int px = rect.right - wall.left;
			if (vel.y > 0)
			{
				int py = rect.bottom - wall.top;
				//px/vel.x > py/vel.y
				//top collision
				if (abs(vel.y) * px > abs(vel.x) * py)
				{
					pos.y -= py;
					vel.y = -vel.y;
				}
				//left collision
				else
				{
					pos.x -= px;
					vel.x = -vel.x;
				}
			}
			else
			{
				int py = wall.bottom - rect.top;
				//px/vel.x > py/vel.y
				//bottom collision
				if (abs(vel.y) * px > abs(vel.x) * py)
				{
					pos.y += py;
					vel.y = -vel.y;
				}
				//left collision
				else
				{
					pos.x -= px;
					vel.x = -vel.x;
				}
			}
		}
		else
		{
			int px = wall.right - rect.left;
			if (vel.y > 0)
			{
				int py = rect.bottom - wall.top;
				//px/vel.x > py/vel.y
				//top collision
				if (abs(vel.y) * px > abs(vel.x) * py)
				{
					pos.y -= py;
					vel.y = -vel.y;
				}
				//right collision
				else
				{
					pos.x += px;
					vel.x = -vel.x;
				}
			}
			else
			{
				int py = wall.bottom - rect.top;
				//px/vel.x > py/vel.y
				//bottom collision
				if (abs(vel.y) * px > abs(vel.x) * py)
				{
					pos.y += py;
					vel.y = -vel.y;
				}
				//right collision
				else
				{
					pos.x += px;
					vel.x = -vel.x;
				}
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
	RectI rect;
	VecF vel = {400.0f,400.0f};
	float size;
	Color color;
	float speed;
};