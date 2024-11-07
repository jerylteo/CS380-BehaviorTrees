#include <pch.h>
#include "Projects/ProjectOne.h"
#include "L_FallOutOfBounds.h"


L_FallOutOfBounds::L_FallOutOfBounds()
{}

void L_FallOutOfBounds::on_enter() {
    Blackboard& bb = agent->get_blackboard();
    if (bb.get_value<int>("BouncesRemaining") > 0) {
		on_failure();
		return;
	}
    Vec3 targetPos = bb.get_value<Vec3>("BallTargetPos");
    if ((targetPos.x >= 0.0f && targetPos.x <= 100.0f) && (targetPos.z >= 0.0f && targetPos.z <= 100.0f)) {
        on_failure();
        return;
    }
    BehaviorNode::on_leaf_enter();
}

void L_FallOutOfBounds::on_update(float dt)
{
    if (agent == nullptr)
    {
        on_failure(); // Agent no longer exists
        return;
    }

    Blackboard& bb = agent->get_blackboard();

    Vec3 targetPos = bb.get_value<Vec3>("BallTargetPos");
    targetPos.y = -150.f;
    float fallSpeed = bb.get_value<float>("BallFallSpeed");

    const auto result = agent->move_toward_point(targetPos, dt);
    if (result) {

        Vec3 pos = agent->get_position();
        if (pos.y <= -130.0f)
        {
            //agents->destroy_agent(agent);
            bb.set_value<Agent*>("SpawnedBall", nullptr);
            on_success();
        }

    }
    display_leaf_text();
}