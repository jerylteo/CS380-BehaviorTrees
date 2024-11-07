#include <pch.h>
#include "D_HumanCheck.h"


D_HumanCheck::D_HumanCheck(float distance) : distance(distance)
{}

void D_HumanCheck::on_enter()
{
    isHumanNearby();
    BehaviorNode::on_enter();
}

void D_HumanCheck::on_update(float dt)
{
    // Check if a Human agent is nearby
    if (isHumanNearby())
    {
        // Execute the child node if a Human is found within the specified distance
        children[0]->tick(dt);
        set_status(children[0]->get_status());
        set_result(children[0]->get_result());
    }
    else
    {
        // If no Human is nearby, fail the decorator
        on_failure();
    }
}

bool D_HumanCheck::isHumanNearby()
{
    const auto& allAgents = agents->get_all_agents();
    for (const auto& otherAgent : allAgents)
    {
        BehaviorAgent* behaviorAgent = dynamic_cast<BehaviorAgent*>(otherAgent);
        if (behaviorAgent &&
            behaviorAgent->get_behavior_tree().get_tree_name() == "Human" &&
            Vec3::Distance(agent->get_position(), otherAgent->get_position()) <= distance)
        {
            return true;
        }
    }
    return false;
}