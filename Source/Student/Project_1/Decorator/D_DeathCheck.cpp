#include <pch.h>
#include "D_DeathCheck.h"

D_DeathCheck::D_DeathCheck(float distance) : distance(distance)
{}

void D_DeathCheck::on_enter()
{
    findNearestHauntingAgent();
    BehaviorNode::on_enter();
}

void D_DeathCheck::on_update(float dt)
{
    // Find the nearest agent (excluding self)
    findNearestHauntingAgent();

    // Get the agent's position
    Vec3 agentPos = agent->get_position();

    // If the nearest Haunting agent is within the distance, succeed
    if (nearestHauntingAgent != nullptr && Vec3::Distance(agentPos, nearestHauntingAgent->get_position()) <= distance)
    {
        children.front()->tick(dt);  // Execute the child node
        set_status(children.front()->get_status());
        set_result(children.front()->get_result());
    }
	else 
	{
		on_failure();
	}

    display_leaf_text();
}

void D_DeathCheck::findNearestHauntingAgent()
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