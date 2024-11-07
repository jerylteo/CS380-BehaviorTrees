#include <pch.h>
#include "D_DelayRandom.h"

D_DelayRandom::D_DelayRandom() : delayDuration(0.0f), elapsedTime(0.0f)
{}

void D_DelayRandom::on_enter()
{
    elapsedTime = 0.0f;
    delayDuration = RNG::range(MIN_DELAY, MAX_DELAY);
    BehaviorNode::on_enter();
}

void D_DelayRandom::on_update(float dt)
{
    elapsedTime += dt;

    if (elapsedTime >= delayDuration)
    {
        // Execute the child node after the delay
        BehaviorNode* child = children.front();
        child->tick(dt);

        // Propagate the child's status and result to this node
        set_status(child->get_status());
        set_result(child->get_result());
    }
}
