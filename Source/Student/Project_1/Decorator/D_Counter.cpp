#include <pch.h>
#include "D_Counter.h"

D_Counter::D_Counter(int count) : count(count), currentCount(0)
{}

void D_Counter::on_enter()
{
    if (agent->get_behavior_tree().get_tree_name() == "Testing")
	{
        count = 10;
	}
    currentCount = 0;
    BehaviorNode::on_enter();
}

void D_Counter::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        currentCount++;
        std::cout << "Current Count: " << currentCount << std::endl;
        if (currentCount >= count)
        {
            on_success();
        }
        else
        {
            child->set_status(NodeStatus::READY);
        }
    }
    else if (child->failed() == true)
    {
        on_failure();
    }
}
