#pragma once
#include "BehaviorNode.h"

class D_Counter : public BaseNode<D_Counter>
{
public:
    D_Counter(int count = 2);

protected:
    unsigned count;
    unsigned currentCount;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};