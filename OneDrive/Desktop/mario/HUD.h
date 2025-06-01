#pragma once
#include "GameObject.h"


class HUD {
public:
    void RenderNumber(float x, float y, int number, int maxDigits = 6);
    void Render(float x, float y, int score, int coins, int time, int power);
};
