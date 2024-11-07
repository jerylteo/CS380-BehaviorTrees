#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
    // Create an agent (using the default "Agent::AgentModel::Man" model)
    //auto man = agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::Example);

    for (int i = 0; i < 10; i++)
    {
        for (int x = 0; x < 3; x++) {
            auto man = agents->create_behavior_agent("Human", BehaviorTreeTypes::Human, Agent::AgentModel::Man);
            man->set_color(Vec3(1.0f, 0.f, 1.f));
            man->set_position(Vec3(x*10.0f, 0.f, i * 10.0f));
            man->set_scaling(Vec3(1.0f, 1.0f, 1.0f));
            man->set_movement_speed(5.0f);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int x = 0; x < 3; x++) {
            auto ball = agents->create_behavior_agent("Devil", BehaviorTreeTypes::Haunting, Agent::AgentModel::Ball);
            ball->set_position(Vec3(100-(x*10.0f), 0.f, i * 10.0f));
            ball->set_scaling(Vec3(0.3f, 0.3f, 0.3f));
            ball->set_movement_speed(7.0f);
        }
    }

    //auto man = agents->create_behavior_agent("Human", BehaviorTreeTypes::Human, Agent::AgentModel::Man);
    //man->set_color(Vec3(1.0f, 0.f, 1.f));
    //man->set_position(Vec3(10.0f, 0.f, 10.0f));
    //man->set_scaling(Vec3(1.0f, 1.0f, 1.0f));
    //man->set_movement_speed(5.0f);

   /* auto ball = agents->create_behavior_agent("Devil", BehaviorTreeTypes::Haunting, Agent::AgentModel::Ball);
    ball->set_position(Vec3(100 - (1 * 10.0f), 0.f, 1 * 10.0f));
    ball->set_scaling(Vec3(0.3f, 0.3f, 0.3f));
    ball->set_movement_speed(7.0f);
    */

    for (int i = 0; i < 2; i++) {
        auto tree = agents->create_behavior_agent("Tree", BehaviorTreeTypes::Malfunction, Agent::AgentModel::Tree);
        tree->set_color(Vec3(0, 1, 0));
        tree->set_position(Vec3(40.0f + (i*20.0f), 0, 40.0f + (i * 20.0f)));
        tree->set_scaling(Vec3(1, 1, 1.5));
        // set pitch 90 degrees (facing up)
        tree->set_pitch(DirectX::XMConvertToRadians(90.0f));
    }

    auto rainingBall = agents->create_behavior_agent("RainingBalls", BehaviorTreeTypes::RainingBalls, Agent::AgentModel::Ball);
    Vec3 spawnPos = Vec3(RNG::range(0.0f, 100.0f), 50.0f, RNG::range(0.0f, 100.0f));
    rainingBall->set_position(spawnPos);
    rainingBall->set_scaling(Vec3(1.5f, 1.5f, 1.5f));
    rainingBall->set_color(Vec3(1.f, 0.f, 0.f));
    rainingBall->set_movement_speed(50.0f);
    Vec3 targetPos = Vec3(RNG::range(0.0f, 100.0f), 0.f, RNG::range(0.0f, 100.0f));

    Blackboard& bb = rainingBall->get_blackboard();

    // Store ball information in the blackboard
    bb.set_value<Agent*>("SpawnedBall", rainingBall);
    bb.set_value<Vec3>("BallTargetPos", targetPos);
    bb.set_value<int>("BouncesRemaining", 3);
    bb.set_value<float>("BallFallSpeed", rainingBall->get_movement_speed());

    // Create an agent with a different 3D model:
    // 1. (optional) Add a new 3D model to the framework other than the ones provided:
    //    A. Find a ".sdkmesh" model or use https://github.com/walbourn/contentexporter
    //       to convert fbx files (many end up corrupted in this process, so good luck!)
    //    B. Add a new AgentModel enum for your model in Agent.h (like the existing Man or Tree).
    // 2. Register the new model with the engine, so it associates the file path with the enum
    //    A. Here we are registering all of the extra models that already come in the package.
    Agent::add_model("Assets\\tree.sdkmesh", Agent::AgentModel::Tree);
    Agent::add_model("Assets\\car.sdkmesh", Agent::AgentModel::Car);
    Agent::add_model("Assets\\bird.sdkmesh", Agent::AgentModel::Bird);
    Agent::add_model("Assets\\ball.sdkmesh", Agent::AgentModel::Ball);
    //Agent::add_model("Assets\\hut.sdkmesh", Agent::AgentModel::Hut);




    // You can technically load any map you want, even create your own map file,
    // but behavior agents won't actually avoid walls or anything special, unless you code
    // that yourself (that's the realm of project 2)
    terrain->goto_map(0);

    // You can also enable the pathing layer and set grid square colors as you see fit.
    // Works best with map 0, the completely blank map
    terrain->pathLayer.set_enabled(true);
    terrain->pathLayer.set_value(0, 0, Colors::Red);

    // Camera position can be modified from this default
    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(terrain->mapSizeInWorld * 0.5f, 70.0f, -90));
    camera->set_yaw(0);

    camera->set_pitch(25* PI /180.0f); // 35 degrees

    // Sound control (these sound functions can be kicked off in a behavior tree node - see the example in L_PlaySound.cpp)
    audioManager->SetVolume(0.4f);
    //audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
    // Uncomment for example on playing music in the engine (must be .wav)
     audioManager->PlayMusic(L"Assets\\Audio\\motivate.wav");
    // audioManager->PauseMusic(...);
    // audioManager->ResumeMusic(...);
    // audioManager->StopMusic(...);
}