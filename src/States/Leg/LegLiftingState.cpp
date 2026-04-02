#include "LegLiftingState.h"
#include "Leg.h"

using namespace std;

void LegLiftingState::Enter()
{
    Serial.println("Leg Starts Lifting\n");
    owner.walkingData.cycleStartPoint = owner.walkingData.currentLegPosition;
}

void LegLiftingState::Update()
{
    if (owner.ONorOFF <= 0) {
        stateMachine.ChangeState(&owner.sleeping);
        return;
    }

    if (owner.walkingData.t < owner.walkingData.pushFraction) {
        owner.stateMachine.ChangeState(&owner.pushing);
        return;        
    }
}

void LegLiftingState::Exit()
{
}
