#pragma once
#include "BehaviorNode.h"

class L_SpawnBird : public BaseNode<L_SpawnBird>
{
public:
    L_SpawnBird();
protected:
    float totalDuration;  // Total duration for the bird to circle
    float elapsedTime = 0.0f;
    float circleRadius;   // Radius of the circle around the tree
    float circleSpeed;    // Angular speed of the circling bird
    Agent* spawnedBird = nullptr;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    void spawnBird();
};