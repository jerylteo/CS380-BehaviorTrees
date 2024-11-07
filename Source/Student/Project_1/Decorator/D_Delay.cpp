#include <pch.h>
#include "D_Delay.h"

D_Delay::D_Delay() : delay(0.0f)
{}

void D_Delay::on_enter()
{
    if (agent->get_behavior_tree().get_tree_name() == "RainingBalls") {
        delay = RNG::range(8.f, 12.f);
    }
    else {
        delay = RNG::range(1.0f, 2.0f);
    }

    BehaviorNode::on_enter();
}

void D_Delay::on_update(float dt)
{
    delay -= dt;

    if (delay < 0.0f)
    {
        BehaviorNode *child = children.front();

        child->tick(dt);

        // assume same status as child
        set_status(child->get_status());
        set_result(child->get_result());
    }
}
