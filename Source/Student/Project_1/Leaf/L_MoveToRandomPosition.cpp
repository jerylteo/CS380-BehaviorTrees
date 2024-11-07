#include <pch.h>
#include "L_MoveToRandomPosition.h"
#include "Agent/BehaviorAgent.h"

void L_MoveToRandomPosition::on_enter()
{
    // set animation, speed, etc

    targetPoint = RNG::world_position();
    //agent->look_at_point(targetPoint);

	BehaviorNode::on_leaf_enter();
}

void L_MoveToRandomPosition::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    Vec3 forward = agent->get_forward_vector();
    forward.y = 0.0f; // Project to XZ plane
    forward.Normalize();

    float targetYaw = atan2f(forward.x, forward.z);
    if (agent->getAgentModel() == Agent::AgentModel::Bird) {
        targetYaw -= HALF_PI;
    }

    agent->set_yaw(targetYaw);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
