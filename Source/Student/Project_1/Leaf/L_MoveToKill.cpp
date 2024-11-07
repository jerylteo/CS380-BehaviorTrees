#include <pch.h>
#include "L_MoveToKill.h"


L_MoveToKill::L_MoveToKill() : killRadius(15.0f)
{}

void L_MoveToKill::on_enter()
{
    // Find the nearest agent (excluding self)
    float shortestDistance = std::numeric_limits<float>::max();

    const auto& allAgents = agents->get_all_agents();

    for (const auto& otherAgent : allAgents)
    {
        BehaviorAgent* behaviorAgent = dynamic_cast<BehaviorAgent*>(otherAgent);
        if (otherAgent != agent && behaviorAgent->get_behavior_tree().get_tree_name() != "Malfunction") // Exclude self
        {
            float distance = Vec3::Distance(agent->get_position(), otherAgent->get_position());
            if (distance < shortestDistance)
            {
                shortestDistance = distance;
                targetAgent = otherAgent;
            }
        }
    }

    if (targetAgent != nullptr)
    {
        BehaviorNode::on_leaf_enter();
    }
    else
    {
        on_success();
        return;
    }
}

void L_MoveToKill::on_update(float dt)
{
    if (targetAgent == nullptr)
    {
        on_failure(); 
        return;
    }

    const auto result = agent->move_toward_point(targetAgent->get_position(), dt);

    if (result == true)
    {
        killNearbyAgents();  
        on_success();
    }

    display_leaf_text();
}

void L_MoveToKill::killNearbyAgents()
{
    const auto& allAgents = agents->get_all_agents();

    for (const auto& otherAgent : allAgents)
    {
        if (otherAgent != agent &&  // Don't kill self
            Vec3::Distance(agent->get_position(), otherAgent->get_position()) <= killRadius)
        {
            //audioManager->PlaySoundEffect(L"Assets\\Audio\\squelch.wav");

            otherAgent->set_pitch(PI / 2);

            //agents->destroy_agent(otherAgent);
        }
    }
}