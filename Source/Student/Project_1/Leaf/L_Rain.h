#pragma once
#include "BehaviorNode.h"

class L_Rain : public BaseNode<L_Rain>
{
public:
    L_Rain();
protected:
    float totalDuration;
    float elapsedTime = 0.0f;
    float nextSpawnTime = 0.0f;
    size_t numTrees;
    float spawnRadius;
    float fallSpeed;

    std::vector<Agent*> spawnedTrees; // To keep track of spawned trees

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    void spawnTrees();    // Function to spawn the small trees
    void updateTrees(float dt); // Function to update the positions of the small trees
};