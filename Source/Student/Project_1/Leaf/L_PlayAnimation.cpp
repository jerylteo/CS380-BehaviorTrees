#include <pch.h>
#include "L_PlayAnimation.h"

L_PlayAnimation::L_PlayAnimation()
    : totalDuration(RNG::range(5.0f, 10.0f)), 
    elapsedTime(0.0f)
{}

void L_PlayAnimation::on_enter()
{
    elapsedTime = 0.0f;
    totalDuration = RNG::range(5.0f, 10.0f);
    scaleSpeed = RNG::range(-7.0f, 7.0f); 
    rotationSpeed = RNG::range(-1440.0f, 1440.0f);
    BehaviorNode::on_leaf_enter();
}

void L_PlayAnimation::on_update(float dt)
{
    BehaviorAgent* agent = static_cast<BehaviorAgent*>(this->agent);

    if (agent != nullptr)
    {
        elapsedTime += dt;

        // Adjust scale and rotation based on speed
        scaleFactor += scaleSpeed * dt + RNG::range(-0.1f, 0.1f); // Add some jitter to scaling
        scaleFactor = std::max(scaleFactor, 1.0f); // Apply minimum scale

        agent->set_scaling(scaleFactor);
        if (scaleFactor <= 1.0f || scaleFactor >= 2.0f) {
            scaleSpeed = -scaleSpeed; // Reverse scaling direction
        }
        if (agent->getAgentModel() == Agent::AgentModel::Tree) {
            agent->set_roll(agent->get_roll() + DirectX::XMConvertToRadians(rotationSpeed * dt));
        }
        else {
            agent->set_yaw(agent->get_yaw() + DirectX::XMConvertToRadians(rotationSpeed * dt));
        }
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