#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "Portal.h"
void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		/*mario->SetState(MARIO_STATE_SIT);
		break;*/
	{
		mario->SetState(MARIO_STATE_SIT);
		CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (!scene) break;

		CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());

		if (mario)
		{
			float ml, mt, mr, mb;
			mario->GetBoundingBox(ml, mt, mr, mb);

			// Lấy danh sách object trong scene hiện tại
			CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			if (!scene) break;

			for (LPGAMEOBJECT obj : scene->GetObjects())
			{
				if (dynamic_cast<CPortal*>(obj))
				{
					float pl, pt, pr, pb;
					obj->GetBoundingBox(pl, pt, pr, pb);

					// Kiểm tra chạm AABB
					if (!(mr < pl || ml > pr || mb < pt || mt > pb))
					{
						CPortal* portal = dynamic_cast<CPortal*>(obj);
						CGame::GetInstance()->InitiateSwitchScene(portal->GetSceneId());
						return;
					}
				}
			}
		}
		break;
	}

	
	
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
		////////////////
	case DIK_A:
		if (mario->holdingKoopa)
		{
			CKoopa* k = mario->holdingKoopa;
			k->SetVX(mario->GetNx() > 0 ? KOOPA_SPIN_SPEED : -KOOPA_SPIN_SPEED);
			mario->holdingKoopa = NULL;
		}
		break;
		//////////////
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}