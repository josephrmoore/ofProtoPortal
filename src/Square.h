//
//  Square.h
//  PortalLevelEditor
//
//  Created by Joseph Moore on 3/13/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Square : public ofxBox2dRect {
public:
    Square();
    bool isPortalable;
    bool isSolid;
    string type;
    ofColor c;
    ofVec3f pos, spawn;
    string target;
    float w, h;
    void change(string _type);
    void drawer();
    bool spawn_set;
    void tile_size(float tile);
    void draw();
};
