#include <pch.h>
#include "D_BounceCheck.h"



D_BounceCheck::D_BounceCheck()
{}

void D_BounceCheck::on_enter()
{
    Blackboard& bb = agent->get_blackboard();
    if (!bb.has_key("SpawnedBall")) {
        on_failure();
        return;
    }

    if (bb.get_value<int>("BouncesRemaining") < 0) {
        BehaviorNode::on_enter();
	}
    else {
        on_failure();
    }
}

void D_BounceCheck::on_update(float dt)
{
    children.front()->tick(dt);
    set_status(children.front()->get_status());
    set_result(children.front()->get_result());

}