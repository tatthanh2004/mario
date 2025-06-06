//#include "Koopa.h"
//#include "debug.h"
//#include "Goomba.h"
//
//CKoopa::CKoopa(float x, float y) : CGameObject(x, y)
//{
//    this->ax = 0;
//    this->ay = KOOPA_GRAVITY;
//    spin_start = -1;
//    SetState(KOOPA_STATE_WALKING);
//}
//
//void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//    if (state == KOOPA_STATE_SPIN)
//    {
//        left = x - KOOPA_BBOX_WIDTH / 2;
//        top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
//        right = left + KOOPA_BBOX_WIDTH;
//        bottom = top + KOOPA_BBOX_HEIGHT_DIE;
//    }
//    else
//    {
//        left = x - KOOPA_BBOX_WIDTH / 2;
//        top = y - KOOPA_BBOX_HEIGHT / 2;
//        right = left + KOOPA_BBOX_WIDTH;
//        bottom = top + KOOPA_BBOX_HEIGHT;
//    }
//}
//
//void CKoopa::OnNoCollision(DWORD dt)
//{
//    x += vx * dt;
//    y += vy * dt;
//}
//
//void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//    CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
//    if (!e->obj->IsBlocking()) return;
//    if (dynamic_cast<CKoopa*>(e->obj)) return;
//
//    if (e->ny != 0)
//    {
//        vy = 0;
//    }
//    else if (e->nx != 0 )
//    {
//        vx = -vx;
//        
//        faceRight = (vx > 0);
//    }
//    
//}
//
//void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//    vy += ay * dt;
//    vx += ax * dt;
//
//    if ((state == KOOPA_STATE_SPIN) && (GetTickCount() - spin_start > KOOPA_SPIN_TIMEOUT))
//    {
//        SetState(KOOPA_STATE_WALKING);
//        return;
//    }
//    if (vx != 0)
//        faceRight = (vx > 0);
//    CGameObject::Update(dt, coObjects);
//    CCollision::GetInstance()->Process(this, dt, coObjects);
//}
//
//void CKoopa::Render()
//{
//    int aniId = ID_ANI_KOOPA_WALKING;
//    if (state == KOOPA_STATE_SPIN)
//        aniId = ID_ANI_KOOPA_SPIN;
//    
//    //else if (vx > 0)
//    //    aniId = ID_ANI_KOOPA_WALKING_RIGHT;
//
//    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
//    RenderBoundingBox();
//}
//
//
//void CKoopa::SetState(int state)
//{
//    if (this->state == state) return;
//
//    float old_bottom = y + (this->state == KOOPA_STATE_SPIN ? KOOPA_BBOX_HEIGHT_DIE / 2 : KOOPA_BBOX_HEIGHT / 2);
//
//    CGameObject::SetState(state);
//    switch (state)
//    {
//    case KOOPA_STATE_SPIN:
//        spin_start = GetTickCount();
//        vx = 0;     
//        ay = KOOPA_GRAVITY;
//        y = old_bottom - KOOPA_BBOX_HEIGHT_DIE / 2;
//        break;
//    
//    case KOOPA_STATE_WALKING:
//        vx = -KOOPA_WALKING_SPEED;    
//
//        ay = KOOPA_GRAVITY;
//        y = old_bottom - KOOPA_BBOX_HEIGHT / 2;
//        break;
//    }    
//
//}
#include "Koopa.h"

#include "Goomba.h"

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
    // ✅ Bỏ qua object không blocking TRỪ Goomba
    if (!e->obj->IsBlocking() && !dynamic_cast<CGoomba*>(e->obj)) return;

    // ✅ Bỏ qua va chạm với chính Koopa khác
    if (dynamic_cast<CKoopa*>(e->obj)) return;

    // ✅ Nếu Goomba → gọi hàm riêng
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

    /*if (state == KOOPA_STATE_SPIN && GetTickCount() - spin_start > KOOPA_SPIN_TIMEOUT)
        SetState(KOOPA_STATE_WALKING);*/
    if (state == KOOPA_STATE_SPIN && GetTickCount() - spin_start > KOOPA_SPIN_TIMEOUT)
    {
        if (vx == 0) // chỉ hồi sinh nếu đang đứng yên
            SetState(KOOPA_STATE_WALKING);
    }

    if (state == KOOPA_STATE_SPIN)
        faceRight = (vx > 0);

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
