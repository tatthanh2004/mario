#include "Goomba.h"
#include "Koopa.h"
#include "Brick.h"
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
    // 
    if (!e->obj->IsBlocking() && !dynamic_cast<CGoomba*>(e->obj)) return;

    // 
    if (dynamic_cast<CKoopa*>(e->obj)) return;


    if (dynamic_cast<CGoomba*>(e->obj))
    {
        OnCollisionWithGoomba(e);
        return;
    }

    if (e->ny != 0)
        vy = 0;
    else if (e->nx != 0)
    {
        vx = -vx;
        faceRight = (vx > 0);
    }
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
    if (state == KOOPA_STATE_SPIN && e->nx != 0)
    {
        CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
        if (!goomba->IsDeleted())
        {
            goomba->SetState(GOOMBA_STATE_DIE);
        }
    }
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    vx += ax * dt;

    if (state == KOOPA_STATE_SPIN && GetTickCount() - spin_start > KOOPA_SPIN_TIMEOUT)
    {
        if (vx == 0)
            SetState(KOOPA_STATE_WALKING);
    }

    if (state == KOOPA_STATE_SPIN)
        faceRight = (vx > 0);

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
    /////
    if (state == KOOPA_STATE_WALKING)
    {
        float kl, kt, kr, kb;
        GetBoundingBox(kl, kt, kr, kb);

        // Điểm cần kiểm tra dưới chân trái/phải
        float check_x = (vx > 0) ? kr - 1 : kl + 1;
        float check_y = kb + 1; // ngay dưới chân

        bool supported = false;

        for (LPGAMEOBJECT obj : *coObjects)
        {
            if (!dynamic_cast<CBrick*>(obj)) continue;

            float bl, bt, br, bb;
            obj->GetBoundingBox(bl, bt, br, bb);

            if (check_x >= bl && check_x <= br && check_y >= bt && check_y <= bb)
            {
                supported = true;
                break;
            }
        }

        if (!supported)
        {
            vx = -vx;
        }
    }
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
    if (this->state == state) return;

    CGameObject::SetState(state);

    float old_bottom = y + KOOPA_BBOX_HEIGHT / 2;

    switch (state)
    {
    case KOOPA_STATE_SPIN:
        spin_start = GetTickCount();
        vx = 0;
        ay = KOOPA_GRAVITY;
        y = old_bottom - KOOPA_BBOX_HEIGHT_DIE / 2;
        break;

    case KOOPA_STATE_WALKING:
        vx = -KOOPA_WALKING_SPEED;
        y = old_bottom - KOOPA_BBOX_HEIGHT;
        break;
    }
}