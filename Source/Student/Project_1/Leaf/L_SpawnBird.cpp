#include <pch.h>
#include "Projects/ProjectOne.h"
#include "L_SpawnBird.h"

L_SpawnBird::L_SpawnBird()
    : elapsedTime(0.0f),
    totalDuration(5.0f), 
    circleRadius(10.0f),  
    circleSpeed(DirectX::XM_PI) // 180 degrees per second 
{}

void L_SpawnBird::on_enter()
{
    elapsedTime = 0.0f;
    spawnBird();
    BehaviorNode::on_leaf_enter();
}

void L_SpawnBird::on_update(float dt)
{
    elapsedTime += dt;

    if (spawnedBird == nullptr)
    {
        on_failure();
        return;
    }

    // Only works on Tree agents
    BehaviorAgent* parentTree = static_cast<BehaviorAgent*>(agent);
    if (!parentTree || parentTree->getAgentModel() != Agent::AgentModel::Tree)
    {
        on_failure();
        return;
    }

    // Calculate bird's new position
    Vec3 parentPos = parentTree->get_position();
    float angle = circleSpeed * elapsedTime;
    Vec3 offset(cos(angle) * circleRadius, 0, sin(angle) * circleRadius);
    Vec3 newPos = parentPos + offset;

    // Apply offset to bird's height for visual effect 
    newPos.y += sin(angle * 4.0f);

    // Update bird's position
    spawnedBird->set_position(newPos);

    // Face the bird towards the direction of movement
    Vec3 direction = parentPos - newPos;
    direction.Normalize();
    float targetYaw = atan2f(direction.x, direction.z);
    spawnedBird->set_yaw(targetYaw);

    // Check if the total duration is reached
    if (elapsedTime >= totalDuration)
    {
        // Destroy the spawned bird and finish the node
        agents->destroy_agent(spawnedBird);
        on_success();
    }

    display_leaf_text();
}

void L_SpawnBird::spawnBird()
{
    BehaviorAgent* parentTree = static_cast<BehaviorAgent*>(agent);
    if (!parentTree || parentTree->getAgentModel() != Agent::AgentModel::Tree)
    {
        on_failure(); // Node can only be executed by Tree agents
        return;
    }

    // Calculate initial spawn position of the bird
    Vec3 parentPos = parentTree->get_position();
    Vec3 spawnPos = parentPos + Vec3(circleRadius, 10.0f, 0.0f); // 1.0f for a bit of height

    // Create a new bird agent (you'll need to adjust the creation process)
    spawnedBird = agents->create_behavior_agent("Bird", BehaviorTreeTypes::Idle, Agent::AgentModel::Bird);
    spawnedBird->set_position(spawnPos);
    spawnedBird->set_scaling(Vec3(0.008f));
    spawnedBird->set_color(Vec3(0.0f, 0.0f, 0.0f)); // Black color for the bird
}
