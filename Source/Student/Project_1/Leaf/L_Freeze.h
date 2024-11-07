#pragma once
#include "BehaviorNode.h"

class L_Freeze : public BaseNode<L_Freeze>
{

protected:
    virtual void on_enter() override;
};