#pragma once
#include "BoxPhysic.h"
#include <vector>
class PhysicEngine
{
public:
	void Update(float dt);
	void AddPhysicObject(const BoxPhysic& box)
	{
		physicObjects.emplace_back(box);
	}
	const std::vector<BoxPhysic>& GetPhysicObjects() const
	{
		return physicObjects;
	}
	std::vector<BoxPhysic>& GetPhysicObjects()
	{
		return physicObjects;
	}
private:
	std::vector<BoxPhysic> physicObjects;
};