#include <pch.h>
#include "L_Rotate.h"

L_Rotate::L_Rotate()
    : totalDuration(2.0f),
    elapsedTime(0.0f),
    rotationSpeed(RNG::range(-1440.f, 1440.0f)) // Random initial rotation speed
{}

void L_Rotate::on_enter()
{
    elapsedTime = 0.0f;
    BehaviorNode::on_leaf_enter();
}

void L_Rotate::on_update(float dt)
{
    BehaviorAgent* agent = static_cast<BehaviorAgent*>(this->agent);

    if (agent != nullptr)
    {
        elapsedTime += dt;

        // Adjust rotation
        if (agent->getAgentModel() == Agent::AgentModel::Tree) {
			agent->set_roll(agent->get_roll() + DirectX::XMConvertToRadians(rotationSpeed * dt));
		}
        else {
            agent->set_yaw(agent->get_yaw() + DirectX::XMConvertToRadians(rotationSpeed * dt));
        }

        // Introduce random changes in rotation direction
        if (RNG::range(0.0f, 1.0f) < 0.1f) {
            rotationSpeed = -rotationSpeed;
        }
    }

    display_leaf_text();

    // Check if total duration is reached
    if (elapsedTime >= totalDuration) {
        on_success();
    }
}