#include "Coin.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Animations.h"
#include <vector>

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects); // Gọi cập nhật vị trí nếu cần (dù coin thường đứng yên)

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());

	if (!mario) return; // Phòng lỗi null

	float ml, mt, mr, mb;
	mario->GetBoundingBox(ml, mt, mr, mb);
	float cl, ct, cr, cb;
	GetBoundingBox(cl, ct, cr, cb);

	if (CGame::IsColliding(ml, mt, mr, mb, cl, ct, cr, cb))
	{
		scene->coins++;
		scene->score += 100;
		this->Delete();
	}
}
