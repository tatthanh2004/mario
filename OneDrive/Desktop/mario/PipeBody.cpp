#include "PipeBody.h"
#include "Animations.h"
#include "debug.h"
void CPipeBody::Render() {
    CAnimations::GetInstance()->Get(ID_ANI_PIPE_BODY)->Render(x, y);
   
}

void CPipeBody::GetBoundingBox(float& l, float& t, float& r, float& b) {
    l = x - PIPE_BODY_WIDTH / 2;
    t = y - PIPE_BODY_HEIGHT / 2;
    r = l + PIPE_BODY_WIDTH;
    b = t + PIPE_BODY_HEIGHT;
}