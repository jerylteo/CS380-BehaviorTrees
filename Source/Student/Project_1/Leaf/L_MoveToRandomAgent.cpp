#include <pch.h>
#include "L_MoveToRandomAgent.h"
#include "Agent/BehaviorAgent.h"


void L_MoveToRandomAgent::on_enter()
{
    elapsedTime = 0.0f;
    targetAgent = nullptr;

    // Get a list of all agents
    const auto& allAgents = agents->get_all_agents();

    // Filter out the agent itself
    std::vector<Agent*> validTargets;
    for (const auto& otherAgent : allAgents)
    {
        if (otherAgent != agent)
        {
            BehaviorAgent* otherBehaviorAgent = dynamic_cast<BehaviorAgent*>(otherAgent);
            if (agent->get_behavior_tree().get_tree_name() == "Haunting")
                if (otherBehaviorAgent->get_behavior_tree().get_tree_name() == "Human") {
                    validTargets.push_back(otherAgent);
                }
            }
        else {
            validTargets.push_back(otherAgent);
        }
    }

    // Choose a random target agent, if any are available
    if (!validTargets.empty())
    {
        size_t randomIndex = RNG::range(static_cast<size_t>(0), validTargets.size() - 1);
        targetAgent = validTargets[randomIndex];

        BehaviorNode::on_leaf_enter();
    }
    else
    {
        on_failure(); // No valid target found
    }
}

void L_MoveToRandomAgent::on_update(float dt)
{
    elapsedTime += dt;
    if (targetAgent == nullptr || elapsedTime >= timeoutDuration)
    {
        on_failure(); // Target no longer exists
        return;
    }


    // Calculate offset direction
    Vec3 direction = targetAgent->get_position() - agent->get_position();
    direction.Normalize();
    Vec3 offsetDirection = direction * -1.0f; // Inverted direction

    // Calculate target position with offset
    Vec3 targetPosWithOffset = targetAgent->get_position() + (offsetDirection * offsetDistance);
    targetPosWithOffset.y = 0.0f; // Project to XZ plane


    const auto result = agent->move_toward_point(targetPosWithOffset, dt);

    Vec3 forward = agent->get_forward_vector();
    forward.y = 0.0f; // Project to XZ plane
    forward.Normalize();

    float targetYaw = atan2f(forward.x, forward.z);
    if (agent->getAgentModel() == Agent::AgentModel::Bird) {
        targetYaw -= HALF_PI;
    }
    agent->set_yaw(targetYaw);

    if (result == true)
    {
        if (agent->getAgentModel() == Agent::AgentModel::Bird) {
        }
        on_success(); // Reached target
    }

    display_leaf_text();
}