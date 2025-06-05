#pragma once
#include "GameObject.h"
#include "debug.h"

class CPipe : public CGameObject
{
protected:
    int ani_id;
public:
    CPipe(float x, float y, int ani_id) : CGameObject(x, y) {
        this->ani_id = ani_id;
    }

    void Render() override;
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};
