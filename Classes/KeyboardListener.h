#pragma once
#include"Includes.h"

class KeyboardListener :public cocos2d::Node
{
public:
	KeyboardListener();
	EventListenerKeyboard* GetListener();
	
	bool GetAttackStatus();
	int GetMoveDirection();
	bool IsKeyPressed(EventKeyboard::KeyCode aKey);

private:
	EventListenerKeyboard* listener;
	map<EventKeyboard::KeyCode, bool> keyboard;
};


struct KeyControls
{
	EventKeyboard::KeyCode LeftKey;
	EventKeyboard::KeyCode RightKey;
	EventKeyboard::KeyCode UpKey;
	EventKeyboard::KeyCode DownKey;

	EventKeyboard::KeyCode AttackKey;
};

static class KeyControlProfile
{
public:
	static KeyControls WASD()
	{
		auto keyControls = KeyControls();
		keyControls.LeftKey = EventKeyboard::KeyCode::KEY_A;
		keyControls.RightKey = EventKeyboard::KeyCode::KEY_D;
		keyControls.UpKey = EventKeyboard::KeyCode::KEY_W;
		keyControls.DownKey = EventKeyboard::KeyCode::KEY_S;
		keyControls.AttackKey = EventKeyboard::KeyCode::KEY_LEFT_CTRL;

		return keyControls;
	}

	static KeyControls Arrows()
	{
		auto keyControls = KeyControls();
		keyControls.LeftKey = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		keyControls.RightKey = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		keyControls.UpKey = EventKeyboard::KeyCode::KEY_UP_ARROW;
		keyControls.DownKey = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
		keyControls.AttackKey = EventKeyboard::KeyCode::KEY_RIGHT_CTRL;

		return keyControls;
	}
};
