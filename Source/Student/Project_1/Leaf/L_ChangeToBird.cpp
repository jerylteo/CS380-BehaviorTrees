#include <pch.h>
#include "L_ChangeToBird.h"


void L_ChangeToBird::on_enter()
{
    // Get a reference to the BehaviorAgent
    BehaviorAgent* agent = static_cast<BehaviorAgent*>(this->agent);

    if (agent != nullptr)
    {
        agent->setAgentModel(Agent::AgentModel::Bird); // Set the model to Car

        if (agent->get_behavior_tree().get_tree_name() == "Malfunction") {
            //agent->set_color(Vec3(0.f));
            agent->set_scaling(Vec3(0.01f, 0.01f, 0.01f));
        }
        else {
            agent->set_scaling(Vec3(0.005, 0.005, 0.005));
        }
    }

    display_leaf_text();
    on_success(); 
}