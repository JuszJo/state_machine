#include "ConcreteAnimationStates.h"

Idle::Idle() {
    name = "idle";

    totalFrames = 11.0f;
    currentFrame = 1.0f;

    frameBuffer = 4;

    loadImage(texturePath, &TBO);
}

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

RunRight::RunRight() {
    name = "run right";

    totalFrames = 8.0f;
    currentFrame = 1.0f;

    frameBuffer = 4;

    loadImage(texturePath, &TBO);
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

RunLeft::RunLeft() {
    name = "run left";

    totalFrames = 8.0f;
    currentFrame = 1.0f;

    frameBuffer = 4;

    loadImage(texturePath, &TBO);
}

void RunLeft::exit(Animation* animation) {
    animation->currentState->currentFrame = 1;
}

void RunLeft::toggleAnimation(Animation* animation, AnimationState& animationState) {
    animation->setState(animationState);
}

void RunLeft::enter(Animation* animation) {

}

AnimationState& RunLeft::getInstance() {
    static RunLeft singleton;

	return singleton;
}