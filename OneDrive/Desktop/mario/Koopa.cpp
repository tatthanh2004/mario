﻿#include "Koopa.h"

CKoopa::CKoopa(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = KOOPA_GRAVITY;
    spin_start = -1;
    SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    if (state == KOOPA_STATE_SPIN)
    {
        left = x - KOOPA_BBOX_WIDTH / 2;
        top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
        right = left + KOOPA_BBOX_WIDTH;
        bottom = top + KOOPA_BBOX_HEIGHT_DIE;
    }
    else
    {
        left = x - KOOPA_BBOX_WIDTH / 2;
        top = y - KOOPA_BBOX_HEIGHT / 2;
        right = left + KOOPA_BBOX_WIDTH;
        bottom = top + KOOPA_BBOX_HEIGHT;
    }
}

void CKoopa::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CKoopa*>(e->obj)) return;

    if (e->ny != 0)
        vy = 0;
    else if (e->nx != 0)
        vx = -vx;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    vx += ax * dt;

    if ((state == KOOPA_STATE_SPIN) && (GetTickCount64() - spin_start > KOOPA_SPIN_TIMEOUT))
    {
        SetState(KOOPA_STATE_WALKING);
        return;
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
    int aniId = ID_ANI_KOOPA_WALKING;
    if (state == KOOPA_STATE_SPIN)
        aniId = ID_ANI_KOOPA_SPIN;

    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case KOOPA_STATE_SPIN:
        spin_start = GetTickCount64();
        vx = 0;
        vy = 0;
        ay = 0;
        break;
    case KOOPA_STATE_WALKING:
        vx = -KOOPA_WALKING_SPEED;
        ay = KOOPA_GRAVITY;
        break;
    }
}
