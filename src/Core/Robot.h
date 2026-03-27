#include "StateMachine.h"
#include "State.h"
#include "RobotWalkState.h"
#include "models.h"

class Robot {
public:
    StateMachine<Robot> stateMachine;
    State<Robot>* sleepState;  // change from pointers to normal variables once specific state files are created
    State<Robot>* standingState;
    State<Robot>* idleState;
    RobotWalkState walkState;
    RobotPhysicalData physicalData;
    // add legs, maybe in a struct?

    Robot(RobotPhysicalData initPhysicalData);
    void Begin();
    void Loop();
};