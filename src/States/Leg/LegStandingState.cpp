#include "LegStandingState.h"
#include <iostream>
#include "Leg.h"

using namespace std;

void LegStandingState::Enter()
{
    cout << "Leg Standing\n";
}

void LegStandingState::Loop()
{
    if (owner.legHeight <= 0) {
        stateMachine.ChangeState(&owner.standing);
        return;
    }
}

void LegStandingState::Exit()
{
}
