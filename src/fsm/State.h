#pragma once

#include "StateMachine.h"

class StateMachine;

class State {
    public:
        virtual void enter(StateMachine* stateMachine) = 0;
        virtual void toggleAnimation(StateMachine* stateMachine) = 0;
        virtual void exit(StateMachine* stateMachine) = 0;

        virtual ~State() {}
};