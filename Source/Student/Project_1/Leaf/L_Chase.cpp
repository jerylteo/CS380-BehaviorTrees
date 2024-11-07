#include <pch.h>
#include "L_Chase.h"

L_Chase::L_Chase(float chaseDistance) : chaseDistance(0.0f)
{}

void L_Chase::on_enter()
{
    // Find the closest agent (excluding self)
    float shortestDistance = std::numeric_limits<float>::max();

    const auto& allAgents = agents->get_all_agents();

    for (const auto& otherAgent : allAgents)
    {
        if (otherAgent != agent) // Exclude self
        {
            float distance = Vec3::Distance(agent->get_position(), otherAgent->get_position());
            if (distance < shortestDistance)
            {
                shortestDistance = distance;
                targetAgent = otherAgent;
            }
        }
    }

    // Chase only if a target is found
    if (targetAgent != nullptr)
    {
        BehaviorNode::on_leaf_enter();
    }
    else
    {
        on_failure(); // No target found, fail the node
    }
}

void L_Chase::on_update(float dt)
{
    if (targetAgent == nullptr)
    {
        on_failure(); // Target no longer exists
        return;
    }

    const auto result = agent->move_toward_point(targetAgent->get_position(), dt);

    if (chaseDistance > 0.0f &&
        Vec3::Distance(agent->get_position(), targetAgent->get_position()) < chaseDistance)
    {
        on_success(); // Reached chase distance
        return;
    }

     //Otherwise, continue chasing if not reached or distance check disabled
    if (result == true)
    {
        on_success(); // Reached target
    }

    display_leaf_text();
}