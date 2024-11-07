#pragma once
#include "BehaviorNode.h"

class L_GiveBirth : public BaseNode<L_GiveBirth>
{
protected:
    virtual void on_enter() override;
};