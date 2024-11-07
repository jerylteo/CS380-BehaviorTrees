#pragma once
#include "BehaviorNode.h"

class C_RandomSequencer : public BaseNode<C_RandomSequencer>
{
public:
    C_RandomSequencer();
protected:
    size_t randomIndex;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    
    void choose_random_node();
    
};