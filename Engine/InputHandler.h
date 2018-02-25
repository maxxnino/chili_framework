#pragma once
#include "Command.h"
#include "Keyboard.h"
#include <memory>

class InputHandler
{
public:
	void handleInput(Keyboard& kbd,Actor& actor,float dt)
	{
		if (kbd.KeyIsPressed('A')) ButtonA->execute(actor, dt);
		if (kbd.KeyIsPressed('D')) ButtonD->execute(actor, dt);
		if (kbd.KeyIsPressed('W')) ButtonW->execute(actor, dt);
		if (kbd.KeyIsPressed('S')) ButtonS->execute(actor, dt);
	}
private:
	std::unique_ptr<Command> ButtonA = std::make_unique<MoveLeft>();
	std::unique_ptr<Command> ButtonD = std::make_unique<MoveRight>();
	std::unique_ptr<Command> ButtonW = std::make_unique<MoveUp>();
	std::unique_ptr<Command> ButtonS = std::make_unique<MoveDown>();
};