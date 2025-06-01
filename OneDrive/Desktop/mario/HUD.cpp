#include "HUD.h"
#include "Sprites.h"
#include "Game.h"
#include <string>
#include "AssetIDs.h"


void HUD::RenderNumber(float x, float y, int number, int maxDigits)
{
    CSprites* s = CSprites::GetInstance();
    std::string numStr = std::to_string(number);
    while (numStr.length() < maxDigits)
        numStr = "0" + numStr;

    for (int i = 0; i < maxDigits; i++)
    {
        int digit = numStr[i] - '0';
        s->Get(70000 + digit)->Draw(x + i * 9, y); // 9px spacing for clarity
    }
}

void HUD::Render(float x, float y, int score, int coins, int time, int power)
{
    CSprites* s = CSprites::GetInstance();

    // Line 1: MARIO x01 WORLD 1-1
    s->Get(70100)->Draw(x, y);     // M
    s->Get(70101)->Draw(x + 8, y); // A
    s->Get(70102)->Draw(x + 16, y);// R
    s->Get(70103)->Draw(x + 24, y);// I
    s->Get(70104)->Draw(x + 32, y);// O

    s->Get(70105)->Draw(x + 72, y); // x
    RenderNumber(x + 80, y, power, 2); // x01

    s->Get(ID_SPRITE_TEXT_WORLD)->Draw(x + 140, y); // Draw full "WORLD"

    RenderNumber(x + 200, y, 1, 1);  // World 1
    s->Get(70111)->Draw(x + 208, y + 2);
    RenderNumber(x + 216, y, 1, 1);  // Stage 1

    // Line 2: Score + TIME
    RenderNumber(x, y + 16, score, 6);

    s->Get(70109)->Draw(x + 150, y + 16); // T
    s->Get(70103)->Draw(x + 158, y + 16); // I
    s->Get(70100)->Draw(x + 166, y + 16); // M
    s->Get(70110)->Draw(x + 174, y + 16); // E

    RenderNumber(x + 200, y + 16, time, 3);
}
