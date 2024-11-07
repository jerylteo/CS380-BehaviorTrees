#pragma once
#include "BehaviorNode.h"

class D_IsInBounds : public BaseNode<D_IsInBounds>
{
public:
    D_IsInBounds(const Vec3& minBounds = Vec3(0, 0, 0), const Vec3& maxBounds = Vec3(100, 100, 100));

protected:
    Vec3 minBounds;
    Vec3 maxBounds;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    bool isInBounds() const;
};