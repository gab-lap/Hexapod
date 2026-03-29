#include "LegLiftingState.h"
#include "Leg.h"

using namespace std;

void LegLiftingState::Enter()
{
    Serial.println("Leg Lifting\n");
}

void LegLiftingState::Update()
{
    if (owner.legHeight <= 0) {
        stateMachine.ChangeState(&owner.sleeping);
        return;
    }
}

void LegLiftingState::Exit()
{
}
