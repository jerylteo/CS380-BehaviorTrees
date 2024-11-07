#include <pch.h>
#include "L_PlayGrowl.h"

void L_PlayGrowl::on_enter()
{
	audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}