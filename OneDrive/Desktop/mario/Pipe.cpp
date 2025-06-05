#include "Pipe.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "debug.h"
void CPipe::Render()
{
    DebugOut(L"[RENDER] Pipe ani_id: %d at (%.2f, %.2f)\n", ani_id, x, y);
    CAnimations::GetInstance()->Get(ani_id)->Render(x, y);

}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x;
    t = y;
    if (ani_id == ID_ANI_PIPE_HEAD) {
        r = x + 33;
        b = y + 33;
    }
    else {
        r = x + 31;
        b = y + 17;
    }
}
