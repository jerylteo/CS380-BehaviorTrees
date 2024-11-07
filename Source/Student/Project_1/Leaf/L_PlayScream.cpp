#include <pch.h>
#include "L_PlayScream.h"

void L_PlayScream::on_enter()
{
	audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}