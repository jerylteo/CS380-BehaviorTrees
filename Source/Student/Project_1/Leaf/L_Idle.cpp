#include <pch.h>
#include "L_Idle.h"

L_Idle::L_Idle() : timer(0.0f)
{}

void L_Idle::on_enter()
{
    timer = RNG::range(1.0f, 2.0f);

	BehaviorNode::on_leaf_enter();
}

void L_Idle::on_update(float dt)
{
    timer -= dt;

    if (agent->getAgentModel() == Agent::AgentModel::Ball) {
        agent->set_position(Vec3(agent->get_position().x, 2.0f, agent->get_position().z));
    }

    if (timer < 0.0f)
    {
        on_success();
    }

    display_leaf_text();
}
