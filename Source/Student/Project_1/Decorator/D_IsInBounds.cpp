#include <pch.h>
#include "D_IsInBounds.h"



D_IsInBounds::D_IsInBounds(const Vec3& minBounds, const Vec3& maxBounds)
    : minBounds(minBounds), maxBounds(maxBounds)
{}

void D_IsInBounds::on_enter()
{
    Blackboard& bb = agent->get_blackboard();
    if (!bb.has_key("SpawnedBall")) {
        on_failure();
        return;
    }
    if (bb.get_value<int>("BouncesRemaining") < 0) {
		on_failure();
		return;
	}
    BehaviorNode::on_enter();
}

void D_IsInBounds::on_update(float dt)
{
    if (isInBounds())
    {
        // Execute child node and propagate status/result
        BehaviorNode* child = children.front();
        child->tick(dt);
        set_status(child->get_status());
        set_result(child->get_result());
    }
    else
    {
        // If out of bounds, fail
        on_failure();
    }
    
    display_leaf_text();
}

bool D_IsInBounds::isInBounds() const
{
    const Vec3& pos = agent->get_position();
    return (pos.x >= minBounds.x && pos.x <= maxBounds.x &&
        pos.z >= minBounds.z && pos.z <= maxBounds.z); // Check only x and z bounds
}