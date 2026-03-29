#include "LegSleepState.h"
#include "Leg.h"

using namespace std;

void LegSleepState::Enter()
{
    Serial.println("Leg Sleeping\n");
}

void LegSleepState::Update()
{
    if (owner.legHeight > 0) {
        stateMachine.ChangeState(&owner.lifting);
        return;
    }
}

void LegSleepState::Exit()
{
}
