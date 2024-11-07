#include <pch.h>
#include "D_DistanceCheck.h"


D_DistanceCheck::D_DistanceCheck(float distance)
    : distance(distance)
{}

void D_DistanceCheck::on_enter()
{
    findNearestHauntingAgent();
    BehaviorNode::on_enter();
}


void D_DistanceCheck::on_update(float dt)
{
    // Get the agent's position
    Vec3 agentPos = agent->get_position();

    // Re-evaluate nearest Haunting agent in each update
    findNearestHauntingAgent();

    // If the nearest Haunting agent is within the distance, succeed
    if (nearestHauntingAgent != nullptr &&
        Vec3::Distance(agentPos, nearestHauntingAgent->get_position()) <= distance)
    {
        BehaviorNode* child = children.front();

        if (child->get_status() == NodeStatus::READY)
        {
            // If not running, start the child by calling tick()
            child->tick(dt);
        }
        else if (child->get_status() == NodeStatus::RUNNING)
        {
            // If the child is running, keep ticking it until it finishes
            child->tick(dt);
        }

        // Update the status and result of the decorator based on the child's outcome
        set_status(child->get_status());
        set_result(child->get_result());
    }
    else
    {
        on_failure();
    }
}

void D_DistanceCheck::findNearestHauntingAgent()
{
    // Find the closest Haunting agent
    float shortestDistance = std::numeric_limits<float>::max();
    nearestHauntingAgent = nullptr; // Reset before searching

    const auto& allAgents = agents->get_all_agents();
    for (const auto& otherAgent : allAgents)
    {
        BehaviorAgent* behaviorAgent = dynamic_cast<BehaviorAgent*>(otherAgent);
        if (behaviorAgent && behaviorAgent->get_behavior_tree().get_tree_name() == "Haunting")
        {
            float distance = Vec3::Distance(agent->get_position(), otherAgent->get_position());
            if (distance < shortestDistance)
            {
                shortestDistance = distance;
                nearestHauntingAgent = otherAgent;
            }
        }
    }
}