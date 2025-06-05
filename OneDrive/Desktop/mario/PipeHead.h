#pragma once
#include "GameObject.h"

#define ID_ANI_PIPE_HEAD 10001
#define PIPE_WIDTH 32
#define PIPE_HEIGHT 32

class CPipeHead : public CGameObject {
public:
    CPipeHead(float x, float y) : CGameObject(x, y) {}

    void Render() override;
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};
