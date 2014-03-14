//
//  Core.cpp
//  PortalLevelEditor
//
//  Created by Joseph Moore on 3/12/14.
//
//

#include "Core.h"

Core::Core(){
    scale = 2;
    NES_PIXELS_WIDTH = 256*scale;
    NES_PIXELS_HEIGHT = 240*scale;
    NES_TILE = 8;
    NES_W = (NES_PIXELS_WIDTH/scale)/NES_TILE; // 32
    NES_H = (NES_PIXELS_HEIGHT/scale)/NES_TILE; // 30
    MENU_TOP = 100;
    MENU_BOTTOM = 170;
    MENU_RIGHT = 5;
}

//--------------------------------------------------------------
void Core::topMenu(ofTrueTypeFont font) {
    font.loadFont("PressStart2P-Regular.ttf", 24);
    font.drawString("Side view", (NES_PIXELS_WIDTH/2)-80, 80);
    font.drawString("Top view", NES_PIXELS_WIDTH + ((NES_PIXELS_WIDTH/2)-80), 80);
}

//--------------------------------------------------------------

void Core::bottomMenu(ofTrueTypeFont font) {
    font.loadFont("PressStart2P-Regular.ttf", 13);
    font.drawString("1) Ground (portal)", 10, MENU_TOP+NES_PIXELS_HEIGHT+40);
    font.drawString("2) Ground (no portal)", 10, MENU_TOP+NES_PIXELS_HEIGHT+70);
    font.drawString("3) Pit (fatal)", 10, MENU_TOP+NES_PIXELS_HEIGHT+100);
    font.drawString("4) Wall (portal)", 410, MENU_TOP+NES_PIXELS_HEIGHT+40);
    font.drawString("5) Wall (no portal)", 410, MENU_TOP+NES_PIXELS_HEIGHT+70);
    font.drawString("6) Door (exit)", 410, MENU_TOP+NES_PIXELS_HEIGHT+100);
    font.drawString("7) Portal 1 (orange)", 810, MENU_TOP+NES_PIXELS_HEIGHT+40);
    font.drawString("8) Portal 2 (blue)", 810, MENU_TOP+NES_PIXELS_HEIGHT+70);
    font.drawString("9) Spawn (begin)", 810, MENU_TOP+NES_PIXELS_HEIGHT+100);
    font.drawString("SPACE Respawn", 460, MENU_TOP+NES_PIXELS_HEIGHT+150);
}

//--------------------------------------------------------------
void Core::rightMenu(ofTrueTypeFont font) {
}