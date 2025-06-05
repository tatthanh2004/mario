#include "PipeHead.h"
#include "Animations.h"

void CPipeHead::Render() {
    CAnimations::GetInstance()->Get(ID_ANI_PIPE_HEAD)->Render(x, y);
   
}

void CPipeHead::GetBoundingBox(float& l, float& t, float& r, float& b) {
    l = x - PIPE_WIDTH / 2;
    t = y - PIPE_HEIGHT / 2;
    r = l + PIPE_WIDTH;
    b = t + PIPE_HEIGHT;
}
