#include "Animation.h"
#include "ConcreteAnimationStates.h"

Animation::Animation() {
    this->currentState = &Idle::getInstance();
}

void Animation::setState(AnimationState& newState) {
    this->currentState->exit(this);
    this->currentState = &newState;
    this->currentState->enter(this);
}

void Animation::toggleAnimation(AnimationState& animationState) {
    this->currentState->toggleAnimation(this, animationState);
}