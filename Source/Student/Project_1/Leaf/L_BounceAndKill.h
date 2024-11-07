#pragma once
#include "BehaviorNode.h"

class L_BounceAndKill : public BaseNode<L_BounceAndKill>
{
public:
    L_BounceAndKill();
protected:
    //std::vector<Agent*> agentsToDie;
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    void goOutOfBounds();
};