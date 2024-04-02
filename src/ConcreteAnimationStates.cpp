#include "ConcreteAnimationStates.h"

void Idle::exit(Animation* animation) {
    animation->currentState->currentFrame = 1;
}

void Idle::toggleAnimation(Animation* animation, AnimationState& animationState) {
    animation->setState(animationState);
}

void Idle::enter(Animation* animation) {

}

AnimationState& Idle::getInstance() {
    static Idle singleton;

	return singleton;
}

void RunRight::exit(Animation* animation) {
    animation->currentState->currentFrame = 1;
}

void RunRight::toggleAnimation(Animation* animation, AnimationState& animationState) {
    animation->setState(animationState);
}

void RunRight::enter(Animation* animation) {

}

AnimationState& RunRight::getInstance() {
    static RunRight singleton;

	return singleton;
}