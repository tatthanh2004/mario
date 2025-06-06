#pragma once
#include "GameObject.h"

#define PIPE_BODY_WIDTH 32
#define PIPE_BODY_HEIGHT 16
#define ID_ANI_PIPE_BODY 10002 

class CPipeBody : public CGameObject
{
public:
    CPipeBody(float x, float y) : CGameObject(x, y) {}

    void Render()override;
    void GetBoundingBox(float& l, float& t, float& r, float& b)override;
};
