//
//  Core.h
//  PortalLevelEditor
//
//  Created by Joseph Moore on 3/12/14.
//
//

#pragma once

#include "ofMain.h"

class Core {
    
public:
    Core();
    int scale;
    int NES_PIXELS_WIDTH;
    int NES_PIXELS_HEIGHT;
    int NES_TILE;
    int NES_W;
    int NES_H;
    int MENU_TOP;
    int MENU_BOTTOM;
    int MENU_RIGHT;
    
    void bottomMenu(ofTrueTypeFont font);
    void topMenu(ofTrueTypeFont font);
    void rightMenu(ofTrueTypeFont font);
};
