#include "LegSleepState.h"
#include "Leg.h"

using namespace std;

void LegSleepState::Enter()
{
    Serial.println("Leg Sleeping\n");
}

void LegSleepState::Update()
{
    if (owner.ONorOFF == 1) {
        stateMachine.ChangeState(&owner.pushing);
        return;
    }
}

void LegSleepState::Exit()
{
}
