#include <pch.h>
#include "Projects/ProjectOne.h"
#include "L_GiveBirth.h"

void L_GiveBirth::on_enter()
{
    //audioManager->PlaySoundEffect(L"Assets\\Audio\\growl.wav");

    Vec3 spawnPos = agent->get_position() + Vec3(RNG::range(-5.0f, 5.0f), 0.0f, RNG::range(-5.0f, 5.0f));
    auto cloneAgent = agents->create_behavior_agent("Ghost", BehaviorTreeTypes::Haunting, Agent::AgentModel::Ball);
    cloneAgent->set_position(spawnPos);
    cloneAgent->set_scaling(Vec3(0.3f, 0.3f, 0.3f));
    cloneAgent->set_movement_speed(7.0f);

    display_leaf_text();
    on_success(); 
}