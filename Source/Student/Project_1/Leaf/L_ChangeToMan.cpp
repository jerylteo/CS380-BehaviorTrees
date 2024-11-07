#include <pch.h>
#include "L_ChangeToMan.h"


void L_ChangeToMan::on_enter()
{
    // Get a reference to the BehaviorAgent
    BehaviorAgent* agent = static_cast<BehaviorAgent*>(this->agent);

    // Ensure the agent is a BehaviorAgent before attempting to change the model
    if (agent != nullptr)
    {
        agent->setAgentModel(Agent::AgentModel::Man); // Set the model to Car
        agent->set_scaling(Vec3(1, 1, 1)); // Set the scaling to 2
    }

    display_leaf_text();
    on_success(); // This action is considered successful immediately
}