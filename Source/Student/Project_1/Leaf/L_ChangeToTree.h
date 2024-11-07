#pragma once
#include "BehaviorNode.h"

class L_ChangeToTree : public BaseNode<L_ChangeToTree>
{

protected:
    virtual void on_enter() override;
};