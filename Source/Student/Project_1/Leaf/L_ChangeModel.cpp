#include <pch.h>
#include "L_ChangeModel.h"


void L_ChangeModel::on_enter()
{
    // Get a reference to the BehaviorAgent
    BehaviorAgent* agent = static_cast<BehaviorAgent*>(this->agent);

    // Ensure the agent is a BehaviorAgent before attempting to change the model
    if (agent != nullptr)
    {
        agent->setAgentModel(Agent::AgentModel::Ball);
        agent->set_scaling(Vec3(0.3f, 0.3f, 0.3f));
    }

    display_leaf_text();
    on_success(); // This action is considered successful immediately
}