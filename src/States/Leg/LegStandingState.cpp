#include "LegStandingState.h"
#include "Leg.h"

using namespace std;

void LegStandingState::Enter()
{
    Serial.println("Leg Standing\n");
}

void LegStandingState::Update()
{
    if (owner.legHeight <= 0) {
        stateMachine.ChangeState(&owner.standing);
        return;
    }
}

void LegStandingState::Exit()
{
}
