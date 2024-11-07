#include <pch.h>
#include "L_Freeze.h"


void L_Freeze::on_enter()
{
    //audioManager->PlaySoundEffect(L"Assets\\Audio\\scream.wav");

    agent->set_movement_speed(0.0f);

    display_leaf_text();
    on_success(); // This action is considered successful immediately
}