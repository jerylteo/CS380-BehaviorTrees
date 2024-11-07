#pragma once
#include "BehaviorNode.h"

class D_AnimationFinished : public BaseNode<D_AnimationFinished>
{

protected:
    virtual void on_update(float dt) override;

};
