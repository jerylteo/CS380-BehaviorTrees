#include <pch.h>
#include "C_RandomSequencer.h"

C_RandomSequencer::C_RandomSequencer() : randomIndex(-1)
{}

void C_RandomSequencer::on_enter()
{
    BehaviorNode::on_enter();

    choose_random_node();
}

void C_RandomSequencer::on_update(float dt)
{
    // If any child fails, the node fails
    // If all children succeed, the node succeeds
    BehaviorNode* child = children[randomIndex];
    child->tick(dt);

    if (child->failed())
    {
        on_failure();
    }
    else if (child->succeeded())
    {
        // Move to the next child node
        randomIndex++;

        // If we've reached the end, the node succeeds
        if (randomIndex >= children.size())
        {
            on_success();
        }
        else
        {
            // Otherwise, choose the next random node
            choose_random_node();
        }
    }
}

void C_RandomSequencer::choose_random_node()
{
    // Choose a random node that hasn't been executed yet
    randomIndex = RNG::range(static_cast<size_t>(0), children.size() - 1);
}
