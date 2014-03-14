//
//  Square.cpp
//  PortalLevelEditor
//
//  Created by Joseph Moore on 3/12/14.
//
//

#include "Square.h"

Square::Square(){
    isPortalable=false;
    isSolid=false;
    type="empty";
    c = ofColor(255);
    pos.set(0, 0);
    boxed = false;
}

void Square::tile_size(float tile){
    w = tile;
    h = tile;
}

void Square::change(string _type) {
    if (target=="P") {
        isPortalable=!isPortalable;
    }
    else {
        type=_type;
    }
}
void Square::drawer() {
    if (type == "empty") {
        isPortalable = false;
        isSolid = false;
        c = ofColor(255);
        
    }
    else if (type == "ground1") {
        isSolid=true;
        isPortalable=true;
        c=ofColor(100);
    }
    else if (type == "ground2") {
        isSolid=true;
        isPortalable=false;
        c=ofColor(50);
    }
    else if (type=="pit") {
        isSolid=false;
        isPortalable=false;
        c=ofColor(150,0,0);
    }
    else if (type=="wall1") {
        isSolid=true;
        isPortalable=true;
        c=ofColor(0,0,100);
    }
    else if (type=="wall2") {
        isSolid=true;
        isPortalable=false;
        c=ofColor(0,0,50);
    }
    else if (type=="door") {
        isPortalable=false;
        isSolid=false;
        c=ofColor(0, 170, 0);
    }
    else if (type=="p1") {
        c=ofColor(255, 150, 0);
        isSolid=false;
    }
    else if (type=="p2") {
        c=ofColor(0,0,255);
        isSolid = false;
    }
    else if (type=="spawn") {
        isPortalable=false;
        isSolid=false;
        c=ofColor(0, 255, 0);
        spawn = pos;
        spawn_set = true;
    }
    else
    {
        type="empty";
        ofSetColor(c);
        isPortalable = false;
        isSolid = false;
        c = ofColor(255);
    }
    if(!isSolid){
        boxed = false;
    }
    draw();
    ofPushStyle();
    ofSetColor(0, 20);
    ofLine(pos.x, pos.y, pos.x, pos.y+h);
    ofLine(pos.x, pos.y+h, pos.x+w, pos.y+h);
    ofPopStyle();
}

void Square::draw(){
    if(!isBody()) return;
    ofPushStyle();
    ofRotate(getRotation(), 0, 0, 1);
    ofSetColor(c);
    ofRect(ofVec2f(getPosition().x,getPosition().y), getWidth()*2,getHeight()*2);
    ofPopStyle();
}