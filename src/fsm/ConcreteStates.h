#pragma once

#include "StateMachine.h"
#include "State.h"

class Idle: public State {
    public:
        Idle();

        void enter(StateMachine* stateMachine);
        void toggleState(StateMachine* stateMachine);
        void exit(StateMachine* stateMachine);

        static State& getInstance();
};

class MoveRight: public State {
    public:
        MoveRight();

        void enter(StateMachine* stateMachine);
        void toggleState(StateMachine* stateMachine);
        void exit(StateMachine* stateMachine);

        static State& getInstance();
};