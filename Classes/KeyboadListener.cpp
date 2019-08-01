#include "KeyboardListener.h"

KeyboardListener::KeyboardListener()
{
	listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keycode, Event * event) {
		keyboard[keycode] = true;
	};

	listener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keycode, Event * event) {
		keyboard.erase(keycode);
	};

}

EventListenerKeyboard* KeyboardListener::GetListener()
{
	return listener;
}

int KeyboardListener::GetMoveDirection()
{
	for (auto keyPressed : keyboard)
	{
		auto keyCode = keyPressed.first;

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
			return LEFT;
		case EventKeyboard::KeyCode::KEY_D:
			return RIGHT;
		case EventKeyboard::KeyCode::KEY_W:
			return UP;
		case EventKeyboard::KeyCode::KEY_S:
			return DOWN;
		}
	}
	return NODIRECTION;
}

bool KeyboardListener::GetAttackStatus()
{
	if (keyboard.find(EventKeyboard::KeyCode::KEY_SPACE) != keyboard.end())
	{
		return true;
	}

	return false;
}

bool KeyboardListener::IsKeyPressed(EventKeyboard::KeyCode aKey)
{
	if (keyboard.find(aKey) != keyboard.end())
	{
		return true;
	}

	return false;
}