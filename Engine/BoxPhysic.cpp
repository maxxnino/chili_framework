#include "BoxPhysic.h"

void BoxPhysic::UpdatePosition(float dt)
{
	pos += vel * dt;
	UpdateRect();
}

void BoxPhysic::UpdateRect()
{
	rect.left = pos.x - size;
	rect.top = pos.y - size;
	rect.right = pos.x + size;
	rect.bottom = pos.y + size;
}

bool BoxPhysic::CheckCollision(BoxPhysic & otherBox)
{
	return rect.isOverLap(otherBox.rect);
}

void BoxPhysic::CorrectCollision(BoxPhysic & otherBox)
{
	VecF velNormal = vel - otherBox.vel;
	if (velNormal.x > 0.0f)
	{
		float px = rect.right - otherBox.rect.left;
		if (velNormal.y > 0.0f)
		{
			float py = rect.bottom - otherBox.rect.top;
			//px/vel.x > py/vel.y
			//top collision
			if (abs(velNormal.y) * px > velNormal.x * py)
			{
				pos.y -= py;
				//otherBox.pos.y -= py * (otherBox.vel.y - velNormal.y) / velNormal.y;
				vel.y -= velNormal.y;
				otherBox.vel.y += velNormal.y;

				vel.y *= 0.8f;
				otherBox.vel.y *= 0.8f;
			}
			//left collision
			else
			{
				pos.x -= px;
				//otherBox.pos.x -= px * (otherBox.vel.x - velNormal.x) / velNormal.x;
				vel.x -= velNormal.x;
				otherBox.vel.x += velNormal.x;
				vel.x *= 0.8f;
				otherBox.vel.x *= 0.8f;
			}
		}
		else
		{
			float py = otherBox.rect.bottom - rect.top;
			//px/vel.x > py/vel.y
			//bottom collision
			if (abs(velNormal.y) * px > abs(velNormal.x) * py)
			{
				pos.y += py;
				//otherBox.pos.y += py * (otherBox.vel.y - velNormal.y) / velNormal.y;
				vel.y -= velNormal.y;
				otherBox.vel.y += velNormal.y;
				vel.y *= 0.8f;
				otherBox.vel.y *= 0.8f;
			}
			//left collision
			else
			{
				pos.x -= px;
				//otherBox.pos.x -= px * (otherBox.vel.x - velNormal.x) / velNormal.x;
				vel.x -= velNormal.x;
				otherBox.vel.x += velNormal.x;
				vel.x *= 0.8f;
				otherBox.vel.x *= 0.8f;
			}
		}
	}
	else
	{
		float px = otherBox.rect.right - rect.left;
		if (velNormal.y > 0.0f)
		{
			float py = rect.bottom - otherBox.rect.top;
			//px/vel.x > py/vel.y
			//top collision
			if (abs(velNormal.y) * px > abs(velNormal.x) * py)
			{
				pos.y -= py;
				//otherBox.pos.y -= py * (otherBox.vel.y - velNormal.y) / velNormal.y;
				vel.y -= velNormal.y;
				otherBox.vel.y += velNormal.y;
				vel.y *= 0.8f;
				otherBox.vel.y *= 0.8f;
			}
			//right collision
			else
			{
				pos.x += px;
				//otherBox.pos.x += px * (otherBox.vel.x - velNormal.x) / velNormal.x;
				vel.x -= velNormal.x;
				otherBox.vel.x += velNormal.x;
				vel.x *= 0.8f;
				otherBox.vel.x *= 0.8f;
			}
		}
		else
		{
			float py = otherBox.rect.bottom - rect.top;
			//px/vel.x > py/vel.y
			//bottom collision
			if (abs(velNormal.y) * px > abs(velNormal.x) * py)
			{
				pos.y += py;
				//otherBox.pos.y += py * (otherBox.vel.y - velNormal.y) / velNormal.y;
				vel.y -= velNormal.y;
				otherBox.vel.y += velNormal.y;
				vel.y *= 0.8f;
				otherBox.vel.y *= 0.8f;
			}
			//right collision
			else
			{
				pos.x += px;
				//otherBox.pos.x += px * (otherBox.vel.x - velNormal.x) / velNormal.x;
				vel.x -= velNormal.x;
				otherBox.vel.x += velNormal.x;
				vel.x *= 0.8f;
				otherBox.vel.x *= 0.8f;
			}
		}
	}
	UpdateRect();
	otherBox.UpdateRect();
}

void BoxPhysic::ClamScreen()
{
	if (rect.left < 0.0f)
	{
		vel.x = -vel.x * 0.8f;
		pos.x = size;
	}
	if (rect.top < 0.0f)
	{
		vel.y = -vel.y* 0.8f;
		pos.y = size;
	}
	if (rect.right >= Graphics::ScreenWidth)
	{
		vel.x = -vel.x* 0.8f;
		pos.x += Graphics::ScreenWidth - rect.right;
	}
	if (rect.bottom >= Graphics::ScreenHeight)
	{
		vel.y = -vel.y* 0.8f;
		pos.y += Graphics::ScreenHeight - rect.bottom;
	}
	UpdateRect();
}
