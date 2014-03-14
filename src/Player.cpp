//
//  Player.cpp
//  PortalLevelEditor
//
//  Created by Joseph Moore on 3/12/14.
//
//

#include "Player.h"

Player::Player(){
    
}

void Player::spawn(ofVec3f sp){
    setPosition(sp);
}

void Player::draw(){
    if(!isBody()) return;
    ofPushStyle();
    ofRotate(getRotation(), 0, 0, 1);
    ofSetColor(255,255,0);
    ofRect(ofVec2f(getPosition().x,getPosition().y), getWidth()*2,getHeight()*2);
    ofPopStyle();
}