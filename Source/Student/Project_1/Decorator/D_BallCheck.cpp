#include <pch.h>
#include "D_BallCheck.h"


D_BallCheck::D_BallCheck()
{}

void D_BallCheck::on_enter() {
    Blackboard& bb = agent->get_blackboard();
    if (bb.has_key("SpawnedBall")) {
        if (bb.get_value<Agent*>("SpawnedBall") != nullptr) {
            on_failure(); // Ball exists, so don't spawn another
            return;
        }
        else {
            //agents->destroy_agent(agent);
            BehaviorNode::on_enter();
        }
    }
}

void D_BallCheck::on_update(float dt)
{


    // If no active ball is found, execute the child node
    BehaviorNode* child = children.front();
    child->tick(dt);
    set_status(child->get_status());
    set_result(child->get_result());

    display_leaf_text();
}
