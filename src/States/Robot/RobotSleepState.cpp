#include "RobotSleepState.h"
#include "Robot.h"
#include "Leg.h"
#include "config.h"
#include "utils.h"


void RobotSleepState::Enter()
{
    Serial.println("Robot Sleeping\n");
    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = owner.getLeg(i);
        
        leg->walkingData.cycleStartPoint = leg->walkingData.currentLegPosition;
    }
}

void RobotSleepState::Update()
{
    // Definizione posizione Home
    Vector3 targetHome(0, owner.getLeg(0)->walkingData.distanceFromCenter, owner.physicalData.distanceFromGround);

    // Muoviamo lentamente ogni gamba verso Home usando LERP
    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = owner.getLeg(i);
        
        // Portiamo la posizione attuale verso targetHome (0.02 è la velocità, circa 1-2 secondi)
        leg->walkingData.currentLegPosition = lerp(leg->walkingData.currentLegPosition, targetHome, 0.02f);
        
        leg->MoveToPosition(leg->walkingData.currentLegPosition);
    }


    if (owner.getLeg(0)->ONorOFF == 1) {
        stateMachine.ChangeState(&owner.walkState);
        return;
    }

    if (owner.getLeg(0)->ONorOFF == 0) {
        for (int i = 0; i < NUM_LEGS; i++) {
            Leg* leg = owner.getLeg(i);
            if (leg->stateMachine.currentState != &leg->sleeping)
                leg->stateMachine.ChangeState(&leg->sleeping);
        }
        return;
    }
}

void RobotSleepState::Exit()
{
}
