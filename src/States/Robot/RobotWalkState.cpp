#include "RobotWalkState.h"
/*
// Inside RobotWalkingState.cpp
void RobotWalkingState::Update() {
    // Tripod Gait Logic:
    // Move Group A (FrontRight, MidLeft, BackRight)
    if (stepPhase == 0) {
        legFR->stateMachine.ChangeState(legFR->lifting);
        legML->stateMachine.ChangeState(legML->lifting);
        legBR->stateMachine.ChangeState(legBR->lifting);

        // Group B stays on the ground
        legFL->stateMachine.ChangeState(legFL->pushing);
        // ... etc
    }
}*/
void RobotWalkState::Enter()
{
}

void RobotWalkState::Loop()
{
}

void RobotWalkState::Exit()
{
}
