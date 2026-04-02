#include "LegPushingState.h"
#include "Leg.h"

using namespace std;

void LegPushingState::Enter()
{
    Serial.println("Leg Starts Pushing\n");

    owner.walkingData.cycleStartPoint = owner.walkingData.currentLegPosition;
}

void LegPushingState::Update()
{
    if (owner.ONorOFF <= 0) {
        stateMachine.ChangeState(&owner.sleeping);
        return;
    }

    float t = owner.walkingData.t;
    float pushFraction = owner.walkingData.pushFraction;

    if (t >= pushFraction) {
        stateMachine.ChangeState(&owner.lifting);
        return;
    }
}

void LegPushingState::Exit()
{
}
