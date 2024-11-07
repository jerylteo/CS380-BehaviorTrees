#include <pch.h>
#include "L_IdleAbout.h"


L_IdleAbout::L_IdleAbout()
{
}

void L_IdleAbout::on_enter()
{
    if (agent->get_movement_speed() == 0.0f)
	{
		agent->set_movement_speed(5.0f);
	}
    // Save the agent's initial position as the center
    centerPosition = agent->get_position();
    setNewTargetPosition(); // Set initial random target within the radius
    BehaviorNode::on_leaf_enter();
}

void L_IdleAbout::on_update(float dt)
{
    // Move towards the current target position
    const auto result = agent->move_toward_point(targetPosition, dt);

    // Get current position
    Vec3 pos = agent->get_position();

    // Check and adjust for boundary collisions (walls)
    if (pos.x < 0 || pos.x > 100)
    {
        pos.x = std::max(0.0f, std::min(100.0f, pos.x)); // Clamp to bounds
        agent->set_position(pos);

        // Reset target position if it's outside the boundaries
        setNewTargetPosition();
    }
    if (pos.z < 0 || pos.z > 100)
    {
        pos.z = std::max(0.0f, std::min(100.0f, pos.z)); // Clamp to bounds
        agent->set_position(pos);

        // Reset target position if it's outside the boundaries
        setNewTargetPosition();
    }

    if (result == true)
    {
        on_success();
    }
    display_leaf_text();
}

void L_IdleAbout::setNewTargetPosition()
{
    // Generate a random direction
    float randomAngle = RNG::range(0.0f, DirectX::XM_2PI);
    Vec3 randomDirection(cos(randomAngle), 0.0f, sin(randomAngle));

    // Calculate a random point within the radius
    float randomDistance = RNG::range(0.0f, radius);
    targetPosition = centerPosition + (randomDirection * randomDistance);
}