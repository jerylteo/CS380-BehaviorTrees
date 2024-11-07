#include <pch.h>
#include "L_Scale.h"

L_Scale::L_Scale()
    : totalDuration(RNG::range(2.0f, 5.0f)),
    elapsedTime(0.0f),
    scaleSpeed(RNG::range(-7.0f, 7.0f)) // Random initial scale speed
{}

void L_Scale::on_enter()
{
    originalScaleFactor = static_cast<BehaviorAgent*>(agent)->get_scaling();
    elapsedTime = 0.0f;
    BehaviorNode::on_leaf_enter();
}

void L_Scale::on_update(float dt)
{
    BehaviorAgent* agent = static_cast<BehaviorAgent*>(this->agent);

    if (agent != nullptr)
    {
        elapsedTime += dt;

        // Adjust scale, ensuring it doesn't go below the minimum
        scaleFactor = std::max(0.5f, scaleFactor + scaleSpeed * dt); // Minimum scale of 0.5
        agent->set_scaling(scaleFactor);

        // Reverse scaling direction if exceeding limits (0.5 to 3.0)
        if (scaleFactor <= 0.5f || scaleFactor >= 3.0f)
        {
            scaleSpeed = -scaleSpeed;
        }
    }

    display_leaf_text();

    // Check if total duration is reached
    if (elapsedTime >= totalDuration) {
        agent->set_scaling(originalScaleFactor);
        on_success();
    }
}