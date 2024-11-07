#include <pch.h>
#include "Projects/ProjectOne.h"
#include "L_Rain.h"


L_Rain::L_Rain()
    : totalDuration(5.0f),  
    numTrees(50),  
    spawnRadius(8.0f),    
    fallSpeed(5.0f)   
{
}

void L_Rain::on_enter()
{
    // Spawn the small trees
    elapsedTime = 0.0f;
    spawnTrees();
    BehaviorNode::on_leaf_enter();
}

void L_Rain::on_update(float dt)
{
    elapsedTime += dt;

    // Spawn trees at intervals
    if (elapsedTime >= nextSpawnTime && spawnedTrees.size() < numTrees)
    {
        // Calculate a random spawn position around the parent tree 
        float angle = RNG::range(0.0f, 2.0f * DirectX::XM_PI);
        float distance = RNG::range(0.0f, spawnRadius);
        Vec3 offset(cos(angle) * distance, 0.0f, sin(angle) * distance); // XZ plane
        Vec3 spawnPos = agent->get_position() + offset;
        spawnPos.y += 10.0f; // Spawn a bit above the parent tree

        // Create a new small tree agent 
        Agent* smallTree = agents->create_behavior_agent("SmallTree", BehaviorTreeTypes::Idle, Agent::AgentModel::Tree);
        smallTree->set_position(spawnPos);
        smallTree->set_scaling(Vec3(0.2f));
        spawnedTrees.push_back(smallTree);

        // Update the next spawn time
        float spawnInterval = totalDuration / numTrees;
        nextSpawnTime += spawnInterval;
    }

    // Update positions of the small trees 
    updateTrees(dt);

    // Check if the rain effect is finished
    if (elapsedTime >= totalDuration) {
        // Delete spawned trees and finish the node
        for (auto* tree : spawnedTrees) {
            agents->destroy_agent(tree);
        }
        spawnedTrees.clear();
        on_success();
    }

    display_leaf_text();
}

void L_Rain::spawnTrees()
{
    BehaviorAgent* parentTree = static_cast<BehaviorAgent*>(agent);
    if (!parentTree || parentTree->getAgentModel() != Agent::AgentModel::Tree)
    {
        on_failure();
        return;
    }

    // Clear existing spawned trees (if any)
    for (auto* tree : spawnedTrees) {
        agents->destroy_agent(tree);
    }
    spawnedTrees.clear();

    // Set initial spawn time
    float spawnInterval = totalDuration / numTrees;
    nextSpawnTime = spawnInterval;
}

void L_Rain::updateTrees(float dt)
{
    for (auto* tree : spawnedTrees)
    {
        Vec3 pos = tree->get_position();
        pos.y -= fallSpeed * dt; // Move the tree downwards
        tree->set_position(pos);
    }
}