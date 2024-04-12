#include "ConcreteStates.h"

Idle::Idle() {

}

void Idle::enter(StateMachine* stateMachine) {
    
}

void Idle::toggleState(StateMachine* stateMachine) {

}

void Idle::exit(StateMachine* stateMachine) {

}

State& Idle::getInstance() {
    static Idle singleton;

	return singleton;
}

MoveRight::MoveRight() {

}

void MoveRight::enter(StateMachine* stateMachine) {
    
}

void MoveRight::toggleState(StateMachine* stateMachine) {

}

void MoveRight::exit(StateMachine* stateMachine) {

}

State& MoveRight::getInstance() {
    static MoveRight singleton;

	return singleton;
}