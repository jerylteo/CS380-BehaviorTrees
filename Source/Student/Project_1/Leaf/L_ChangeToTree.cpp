#include <pch.h>
#include "L_ChangeToTree.h"


void L_ChangeToTree::on_enter()
{
    // Get a reference to the BehaviorAgent
    BehaviorAgent* agent = static_cast<BehaviorAgent*>(this->agent);

    // Ensure the agent is a BehaviorAgent before attempting to change the model
    if (agent != nullptr)
    {
        agent->setAgentModel(Agent::AgentModel::Tree); // Set the model to Tree
        agent->set_scaling(Vec3(1, 1, 1.5));
    }

    display_leaf_text();
    on_success(); // This action is considered successful immediately
}