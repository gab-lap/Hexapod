#include "LegLiftingState.h"
#include <iostream>
#include "Leg.h"

using namespace std;

void LegLiftingState::Enter()
{
    cout << "Leg Lifting\n";
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
