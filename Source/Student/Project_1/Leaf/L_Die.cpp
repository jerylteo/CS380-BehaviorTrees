#include <pch.h>
#include "L_Die.h"


void L_Die::on_enter()
{
    agents->destroy_agent(agent);

    display_leaf_text();
    on_success(); // This action is considered successful immediately
}