#include "PhysicEngine.h"

void PhysicEngine::Update(float dt)
{
	for (auto& o : physicObjects)
	{
		o.UpdatePosition(dt);
	}
	for (int i = 0; i < physicObjects.size(); i++)
	{
		for (int j = i + 1; j < physicObjects.size(); j++)
		{
			if (physicObjects[i].CheckCollision(physicObjects[j]))
			{
				physicObjects[i].CorrectCollision(physicObjects[j]);
			}
		}
	}
	for (auto& o : physicObjects)
	{
		o.ClamScreen();
	}
}
