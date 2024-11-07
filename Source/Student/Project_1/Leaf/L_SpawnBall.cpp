#include <pch.h>
#include "Projects/ProjectOne.h"
#include "L_SpawnBall.h"


L_SpawnBall::L_SpawnBall()
    : spawnHeight(50.0f),
    bouncesRemaining(3),
    fallSpeed(50.f)
{}

void L_SpawnBall::on_enter()
{
    // World bounds
    float worldMinX = 0.0f;
    float worldMaxX = 100.0f;
    float worldMinZ = 0.0f;
    float worldMaxZ = 100.0f;

    // Calculate a random spawn position within the bounds
    Vec3 spawnPos(RNG::range(worldMinX, worldMaxX), spawnHeight, RNG::range(worldMinZ, worldMaxZ));
    Vec3 targetPos(RNG::range(worldMinX, worldMaxX), 0.0f, RNG::range(worldMinZ, worldMaxZ)); // Target on the ground

    //std::cout << "Destroying raining ball..." << std::endl;
    agents->destroy_agent(agent); // Destroy the parent raining ball
    // Create a new ball agent (adjust the creation process as needed)
    auto ball = agents->create_behavior_agent("RainingBalls", BehaviorTreeTypes::RainingBalls, Agent::AgentModel::Ball);
    ball->set_position(spawnPos);
    ball->set_scaling(Vec3(1.5f, 1.5f, 1.5f));
    ball->set_color(Vec3(1.f, 0.f, 0.f));

    ball->set_movement_speed(fallSpeed);

 /*   std::cout << "Ball spawned at: (" << spawnPos.x << "," << spawnPos.y << "," << spawnPos.z << ")" << std::endl;
    std::cout << "Ball target position: (" << targetPos.x << "," << targetPos.y << "," << targetPos.z << ") | " << bouncesRemaining << std::endl;
    */
    // Get the blackboard
    Blackboard& bb = ball->get_blackboard();

    // Store ball information in the blackboard
    bb.set_value<Agent*>("SpawnedBall", ball);
    bb.set_value<Vec3>("BallTargetPos", targetPos);
    bb.set_value<int>("BouncesRemaining", bouncesRemaining);
    bb.set_value<float>("BallFallSpeed", ball->get_movement_speed());


    display_leaf_text();
    on_success(); // Spawning is considered successful immediately
}