#pragma once

// Include all node headers in this file

// Example Control Flow Nodes
#include "ControlFlow/C_ParallelSequencer.h"
#include "ControlFlow/C_RandomSelector.h"
#include "ControlFlow/C_Selector.h"
#include "ControlFlow/C_Sequencer.h"

// Student Control Flow Nodes
#include "ControlFlow/C_RandomSequencer.h"


// Example Decorator Nodes
#include "Decorator/D_Delay.h"
#include "Decorator/D_InvertedRepeater.h"
#include "Decorator/D_RepeatFourTimes.h"

// Student Decorator Nodes
#include "Decorator/D_DistanceCheck.h"
#include "Decorator/D_AnimationFinished.h"
#include "Decorator/D_DelayRandom.h"
#include "Decorator/D_Counter.h"
#include "Decorator/D_HumanCheck.h"
#include "Decorator/D_DeathCheck.h"
#include "Decorator/D_IsInBounds.h"
#include "Decorator/D_BallCheck.h"
#include "Decorator/D_BounceCheck.h"

// Example Leaf Nodes
#include "Leaf/L_CheckMouseClick.h"
#include "Leaf/L_Idle.h"
#include "Leaf/L_MoveToFurthestAgent.h"
#include "Leaf/L_MoveToMouseClick.h"
#include "Leaf/L_MoveToRandomPosition.h"
#include "Leaf/L_PlaySound.h"

// Student Leaf Nodes
#include "Leaf/L_MoveToRandomAgent.h"
#include "Leaf/L_Scale.h"
#include "Leaf/L_Rotate.h"
#include "Leaf/L_ChangeModel.h"
#include "Leaf/L_Chase.h"
#include "Leaf/L_PlayAnimation.h"
#include "Leaf/L_PlayScream.h"
#include "Leaf/L_PlayGrowl.h"
#include "Leaf/L_PlaySquelch.h"

#include "Leaf/L_ChangeToBird.h"
#include "Leaf/L_ChangeToMan.h"
#include "Leaf/L_ChangeToTree.h"
#include "Leaf/L_Rain.h"
#include "Leaf/L_GiveBirth.h"
#include "Leaf/L_SpawnBird.h"
#include "Leaf/L_RunAway.h"
#include "Leaf/L_IdleAbout.h"
#include "Leaf/L_Die.h"
#include "Leaf/L_Freeze.h"
#include "Leaf/L_SpawnBall.h"
#include "Leaf/L_BounceAndKill.h"
#include "Leaf/L_FallOutOfBounds.h"
#include "Leaf/L_MoveToKill.h"