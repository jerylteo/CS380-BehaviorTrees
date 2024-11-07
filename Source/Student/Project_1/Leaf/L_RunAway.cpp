#include <pch.h>
#include "Projects/ProjectOne.h"
#include "L_RunAway.h"

L_RunAway::L_RunAway()
{}

void L_RunAway::on_enter()
{
    agent->set_movement_speed(5.0f);
    // Calculate a random flee direction
    float randomAngle = RNG::range(0.0f, 2.0f * DirectX::XM_PI);
    Vec3 fleeDirection(cos(randomAngle), 0.0f, sin(randomAngle));

    // Set the target flee position based on distance and random direction
    fleeTarget = agent->get_position() + (fleeDirection * fleeDistance);


    BehaviorNode::on_leaf_enter();
}

void L_RunAway::on_update(float dt)
{
    const auto result = agent->move_toward_point(fleeTarget, dt);

    Vec3 pos = agent->get_position();

    // Check and adjust for boundary collisions (walls)
    if (pos.x < 0 || pos.x > 100)
    {
        pos.x = std::max(0.0f, std::min(100.0f, pos.x)); // Clamp to bounds
        agent->set_position(pos);

        // Adjust flee target to be along the wall
        fleeTarget.x = pos.x;
    }
    if (pos.z < 0 || pos.z > 100)
    {
        pos.z = std::max(0.0f, std::min(100.0f, pos.z)); 
        agent->set_position(pos);

        // Adjust flee target to be along the wall
        fleeTarget.z = pos.z; 
    }

    if (result)
    {
        on_success();
    }

    display_leaf_text();
}
