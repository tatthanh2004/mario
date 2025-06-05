#include "PipeHead.h"
#include "Animations.h"

void CPipeHead::Render() {
    CAnimations::GetInstance()->Get(ID_ANI_PIPE_HEAD)->Render(x, y);
}

void CPipeHead::GetBoundingBox(float& l, float& t, float& r, float& b) {
    l = x;
    t = y;
    r = x + PIPE_WIDTH;
    b = y + PIPE_HEIGHT;
}
