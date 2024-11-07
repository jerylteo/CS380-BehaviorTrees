#pragma once
#include "BehaviorNode.h"

class L_IdleAbout : public BaseNode<L_IdleAbout>
{
public: 
    L_IdleAbout();
protected:
    Vec3 centerPosition;
    float radius = 10.0f;
    Vec3 targetPosition;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    void setNewTargetPosition();
};