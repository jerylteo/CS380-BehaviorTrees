#pragma once
#include "BehaviorNode.h"

class L_Die : public BaseNode<L_Die>
{

protected:
    virtual void on_enter() override;
};