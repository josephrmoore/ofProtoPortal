#pragma once

#include "ofMain.h"
#include "Square.h"
#include "Core.h"
#include "Player.h"
#include "Portal.h"
#include "ofxBox2d.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    std::vector< std::vector<Square> > blocks_side, blocks_top;

    void paint();

    ofTrueTypeFont font;
    bool drawing;
    string target;
    float g;
    bool alive, spawn_set;
    Player player;
    ofVec3f spawn;
    Core core;
    float xoff;
    ofxBox2d box;
    b2Filter collide, invisible;
};
