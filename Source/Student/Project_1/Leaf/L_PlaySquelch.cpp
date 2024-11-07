#include <pch.h>
#include "L_PlaySquelch.h"

void L_PlaySquelch::on_enter()
{
	audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}