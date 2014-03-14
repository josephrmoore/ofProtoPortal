//
//  Player.h
//  PortalLevelEditor
//
//  Created by Joseph Moore on 3/12/14.
//
//
#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class Player : public ofxBox2dRect {
    
public:
    Player();
    void spawn(ofVec3f sp);
    void draw();
};
