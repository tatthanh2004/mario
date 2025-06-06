#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.03f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_DIE 14

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SPIN 200

#define ID_ANI_KOOPA_WALKING 6000
#define ID_ANI_KOOPA_SPIN 6001
#define ID_ANI_KOOPA_WALKING_RIGHT   6002

#define KOOPA_SPIN_TIMEOUT 5000

#define OBJECT_TYPE_KOOPA 3

#define KOOPA_SPIN_SPEED 0.2f

class CKoopa : public CGameObject
{
protected:
    float ax;
    float ay;
    bool isBeingHeld = false;

    ULONGLONG spin_start;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    //
    void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
    //

public:
    CKoopa(float x, float y);
    virtual void SetState(int state);

    float GetVX() { return vx; }
    void SetVX(float _vx) { vx = _vx; }
    int GetState() { return state; }
    //
    bool faceRight;

};
