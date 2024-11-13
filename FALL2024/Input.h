#pragma once
#include "GameWindow.h"

using KEY = int;

//Key definations
constexpr KEY K_SPACE = 32;

constexpr KEY K_A = 65;
constexpr KEY K_Z = 90;

constexpr KEY K_0 = 48;
constexpr KEY K_9 = 57;

constexpr KEY K_F1 = 290;
constexpr KEY K_F12 = 301;

constexpr KEY KP_0 = 320;
constexpr KEY KP_9 = 329;

constexpr KEY A_RIGHT = 262;
constexpr KEY A_LEFT = 263;
constexpr KEY A_DOWN = 264;
constexpr KEY A_UP = 265;
constexpr KEY L_SHIFT = 340;
constexpr KEY L_CTRL = 341;
constexpr KEY L_ALT = 342;
constexpr KEY R_SHIFT = 344;
constexpr KEY R_CTRL = 345;
constexpr KEY R_ALT = 346;

struct KeyState {
	bool pressed = false;
	bool released = false;
	bool held = false;
};

class Input {
public:
	Input(GameWindow& window);
	
	bool isKeyPressed(int key);
	bool isKeyReleased(int key);
	bool isKeyHeld(int key);

	void update();

private:
	GameWindow& pWindow;
	std::unordered_map<int, KeyState> keyStates;

	void registerKey(int key);
};
