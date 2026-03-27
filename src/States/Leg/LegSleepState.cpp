#include "LegSleepState.h"
#include <iostream>
#include "Leg.h"

using namespace std;

void LegSleepState::Enter()
{
    cout << "Leg Sleeping\n";
}

void LegSleepState::Loop()
{
    if (owner.legHeight > 0) {
        stateMachine.ChangeState(&owner.lifting);
        return;
    }
}

void LegSleepState::Exit()
{
}
