#include "LegPushingState.h"
#include <iostream>
#include "Leg.h"

using namespace std;

void LegPushingState::Enter()
{
    cout << "Leg Pushing\n";
}

void LegPushingState::Loop()
{
    if (owner.legHeight <= 0) {
        stateMachine.ChangeState(&owner.pushing);
        return;
    }
}

void LegPushingState::Exit()
{
}
