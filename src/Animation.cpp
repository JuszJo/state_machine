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

void Animation::animate() {
    if(this->currentState->currentFrame != this->currentState->totalFrames) {
        ++this->currentState->currentFrame;
    }
    else {
        this->currentState->currentFrame = 1;
    }
}