#include "StateMachine.h"
#include "ConcreteStates.h"

class ConcreteStates;

StateMachine::StateMachine() {
    this->currentState = &Idle::getInstance();
}

void StateMachine::setState(State& state) {
    this->currentState->exit(this);
    this->currentState = &state;
    this->currentState->enter(this);
}

void StateMachine::toggleState(State& state) {
    this->currentState->toggleState(this);
}