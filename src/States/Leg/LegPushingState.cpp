#include "LegPushingState.h"
#include "Leg.h"

using namespace std;

void LegPushingState::Enter()
{
    Serial.println("Leg Pushing\n");
}

void LegPushingState::Update()
{
    if (owner.legHeight <= 0) {
        stateMachine.ChangeState(&owner.pushing);
        return;
    }
}

void LegPushingState::Exit()
{
}
