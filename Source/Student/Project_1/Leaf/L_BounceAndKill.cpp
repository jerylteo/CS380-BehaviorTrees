#include <pch.h>
#include "Projects/ProjectOne.h"
#include "L_BounceAndKill.h"


L_BounceAndKill::L_BounceAndKill()
{}

void L_BounceAndKill::on_enter() {
    BehaviorNode::on_leaf_enter();
}

void L_BounceAndKill::on_update(float dt)
{
    if (agent == nullptr)
    {
        on_failure(); // Agent no longer exists
        return;
    }

    Blackboard& bb = agent->get_blackboard();
    if (bb.get_value<int>("BouncesRemaining") < 0) {
		goOutOfBounds();
        return;
	}

    Vec3& targetPos = bb.get_value<Vec3>("BallTargetPos");
    float fallSpeed = bb.get_value<float>("BallFallSpeed");

    Vec3 currentPos = agent->get_position();

    if (agent->move_toward_point(targetPos, dt)) {
        if (currentPos.y <= 15.0f)
        {
            // Find and destroy nearby agents within the kill radius
            const float killRadius = 15.0f;
            const auto& allAgents = agents->get_all_agents();

            for (const auto& otherAgent : allAgents)
            {
                BehaviorAgent* behaviorAgent = dynamic_cast<BehaviorAgent*>(otherAgent);
                if (otherAgent != agent &&  // Don't kill self
                    behaviorAgent->get_behavior_tree().get_tree_name() != "Malfunction" && 
                    Vec3::Distance(currentPos, otherAgent->get_position()) <= killRadius)
                {
                    //std::cout << "Ball killed agent: " << otherAgent->get_type() << std::endl;
                    // set pitch of agent to PI/2
                    //audioManager->PlaySoundEffect(L"Assets\\Audio\\squelch.wav");
                    otherAgent->set_pitch(PI / 2);
                    //agentsToDie.push_back(otherAgent);
                    //agents->destroy_agent(otherAgent);
                }
            }

            // Check if we have bounces remaining
            int bouncesRemaining = bb.get_value<int>("BouncesRemaining");

            if (bouncesRemaining > 0)
            {
                // Update the target position for the next bounce
                targetPos.x = RNG::range(0.0f, 100.0f); // Generate new x position
                targetPos.z = RNG::range(0.0f, 100.0f); // Generate new z position
                targetPos.y += 40.0f; // Add height for the bounce 

                // Update the target position in the blackboard
                bb.set_value<Vec3>("BallTargetPos", targetPos);

                // Update number of bounces
                bb.set_value<int>("BouncesRemaining", bouncesRemaining - 1);
                //std::cout << "Ball new target position: (" << targetPos.x << "," << targetPos.y << "," << targetPos.z << ") | " << bouncesRemaining << std::endl;
                
                on_success();
            }
            else // No bounces remaining, destroy the ball
            {
				goOutOfBounds();
                return;
            }

        }
        else if (currentPos.y >= 30.0f) {
            targetPos.x = RNG::range(0.0f, 100.0f); // Generate new x position
            targetPos.z = RNG::range(0.0f, 100.0f); // Generate new z position
            targetPos.y = 10.0f;
            // Update the target position in the blackboard
            bb.set_value<Vec3>("BallTargetPos", targetPos);

            //std::cout << "Ball new target position: (" << targetPos.x << "," << targetPos.y << "," << targetPos.z << ")" << std::endl;

            on_success();
        }
    }
    display_leaf_text();
}

void L_BounceAndKill::goOutOfBounds() {
    
    Blackboard& bb = agent->get_blackboard();
    Vec3& targetPos = bb.get_value<Vec3>("BallTargetPos");
    Vec3 currentPos = agent->get_position();

    // Choose a random side to fall off
    int side = RNG::range(0, 3);
    switch (side)
    {
    case 0: // Left side
        targetPos = Vec3(-50.0f, 30.f, currentPos.z);
        break;
    case 1: // Right side
        targetPos = Vec3(150.0f, 30.f, currentPos.z);
        break;
    case 2: // Top side
        targetPos = Vec3(currentPos.x, 30.f, 150.0f);
        break;
    case 3: // Bottom side
        targetPos = Vec3(currentPos.x, 30.f, -50.0f);
        break;
    }

    // Update the target position and direction in the blackboard
    bb.set_value<int>("BouncesRemaining", -1);
    bb.set_value<Vec3>("BallTargetPos", targetPos);
    on_success();
}