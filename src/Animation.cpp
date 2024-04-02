#include "Animation.h"

Animation::Animation() {

}

void Animation::setState(AnimationState& newState) {
    this->currentState->exit(this);
    this->currentState = &newState;
    this->currentState->enter(this);
}

void Animation::toggle() {
    this->currentState->toggleAnimation(this);
}