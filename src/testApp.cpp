#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    target = "empty";
    g = .08;
    xoff = 40;
    
    invisible.categoryBits = 0x000001;
    invisible.maskBits = 0x000000;
    collide.categoryBits = 0x000001;
    collide.maskBits = 0xFFFFFF;
    
    // Box 2D stuff
    box.init();
	box.setGravity(0, 5);
	box.setFPS(30.0);
    ofRectangle bounds(xoff, core.MENU_TOP, (core.NES_PIXELS_WIDTH*2)+5, core.NES_PIXELS_HEIGHT);
    box.createBounds(bounds);
//    box.enableGrabbing();
//    box.registerGrabbing();
    
    player.setPhysics(300.0, 1.0, 1.0);
    player.setup(box.getWorld(), xoff, core.MENU_TOP, core.NES_TILE*core.scale*2.0/2.0, core.NES_TILE*core.scale*4.0/2.0);

    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetFrameRate(60);
    
    // allocate room for all the rows
    blocks_side.resize( core.NES_W );
    blocks_top.resize( core.NES_W );
    // for each row
    for ( int k=0;k<core.NES_W; k++ )
    {
        // allocate room for all the columns
        blocks_side[k].resize( core.NES_H );
        blocks_top[k].resize( core.NES_H );
    }
    
    for (int i = 0; i <blocks_side.size();i++) {
        for (int j = 0; j<blocks_side[i].size(); j++) {
            Square b;
            Square b2;
            b.setPhysics(0.0, 0.0, 0.0);
            b2.setPhysics(0.0, 0.0, 0.0);
            b.setup(box.getWorld(), xoff+i*core.NES_TILE*core.scale, j*core.NES_TILE*core.scale, core.NES_TILE*core.scale/2.0, core.NES_TILE*core.scale/2.0);
            b2.setup(box.getWorld(), (xoff+5+core.NES_PIXELS_WIDTH)+i*core.NES_TILE*core.scale, j*core.NES_TILE*core.scale, core.NES_TILE*core.scale/2.0, core.NES_TILE*core.scale/2.0);
            b.tile_size(core.NES_TILE*core.scale);
            b2.tile_size(core.NES_TILE*core.scale);
            for (b2Fixture* f = b.body->GetFixtureList(); f; f = f->GetNext())
            {
                f->SetFilterData(invisible);
            }
            for (b2Fixture* f = b2.body->GetFixtureList(); f; f = f->GetNext())
            {
                f->SetFilterData(invisible);
            }

            blocks_side[i][j] = b;
            if (j>=core.NES_H-2) {
                blocks_side[i][j].type = "ground1";
            }
            else {
                blocks_side[i][j].type = "empty";
            }
            blocks_side[i][j].pos.set(i*(core.NES_TILE*core.scale)+xoff, j*(core.NES_TILE*core.scale));
            blocks_top[i][j] = b2;
            blocks_top[i][j].type = "ground1";
            blocks_top[i][j].pos.set(i*(core.NES_TILE*core.scale)+xoff+5+core.NES_PIXELS_WIDTH, j*(core.NES_TILE*core.scale));
        }
    }
    spawn_set = false;
}

//--------------------------------------------------------------
void testApp::update(){
    for (int i = 0; i <core.NES_W;i++) {
        for (int j = 0; j<core.NES_H; j++) {
            blocks_side[i][j].update();
            if(blocks_side[i][j].isSolid && !blocks_side[i][j].boxed){
                blocks_side[i][j].setPhysics(300.0, 1.0, 1.0);
                for (b2Fixture* f = blocks_side[i][j].body->GetFixtureList(); f; f = f->GetNext())
                {
                    f->SetFilterData(collide);
                }
                blocks_side[i][j].boxed = true;
            } else {
                blocks_side[i][j].setPhysics(0.0, 0.0, 0.0);
                for (b2Fixture* f = blocks_side[i][j].body->GetFixtureList(); f; f = f->GetNext())
                {
                    f->SetFilterData(invisible);
                }
            }
            if(blocks_side[i][j].fixture.filter.categoryBits == 0x000001){
//                cout<<(uint16)blocks_side[i][j].fixture.filter.maskBits<<endl;
            }
        }
    }
    if (player.alive) {
        player.update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    core.bottomMenu(font);
    core.topMenu(font);
    core.rightMenu(font);
    if (drawing) {
        paint();
    }
    ofPushMatrix();
    ofTranslate(xoff, core.MENU_TOP);
    for (int i = 0; i <core.NES_W;i++) {
        for (int j = 0; j<core.NES_H; j++) {
            if (blocks_side[i][j].isPortalable) {
//                stroke(100);
            }
            else {
//                noStroke();
            }
            blocks_side[i][j].drawer();
            if (blocks_top[i][j].isPortalable) {
//                stroke(100);
            }
            else {
//                noStroke();
            }
            blocks_top[i][j].drawer();
        }
    }
    if (player.alive) {
        player.draw();
    }
}

void testApp::paint() {
    for (int i = 0; i <core.NES_W;i++) {
        for (int j = 0; j<core.NES_H; j++) {
            if (mouseX-xoff>blocks_side[i][j].pos.x &&
                mouseX-xoff<blocks_side[i][j].pos.x + core.NES_TILE*core.scale &&
                mouseY-core.MENU_TOP>blocks_side[i][j].pos.y &&
                mouseY-core.MENU_TOP<blocks_side[i][j].pos.y + core.NES_TILE*core.scale) {
                blocks_side[i][j].change(target);
                if(target == "spawn"){
                    spawn = blocks_side[i][j].pos;
                }
                // need logic to control top from here
                        blocks_top[i][16].change(target);
            }
            if (mouseX-xoff>blocks_top[i][j].pos.x &&
                mouseX-xoff<blocks_top[i][j].pos.x + core.NES_TILE*core.scale &&
                mouseY-core.MENU_TOP>blocks_top[i][j].pos.y &&
                mouseY-core.MENU_TOP<blocks_top[i][j].pos.y + core.NES_TILE*core.scale) {
                blocks_top[i][j].change(target);
                // need logic to control side from here
                        if(mouseY-core.MENU_TOP>(core.NES_H*core.NES_TILE*core.scale)/2){
                          blocks_side[i][core.NES_H-3].change(target);
                        } else {
                          blocks_side[i][core.NES_H-4].change(target);
                        }
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key=='1') {
        target = "ground1";
    }
    if (key=='2') {
        target = "ground2";
    }
    if (key=='3') {
        target = "pit";
    }
    if (key=='4') {
        target = "wall1";
    }
    if (key=='5') {
        target = "wall2";
    }
    if (key=='6') {
        target = "door";
    }
    if (key=='7') {
        target = "p1";
    }
    if (key=='8') {
        target = "p2";
    }
    if (key=='9') {
        target = "spawn";
    }
    if (key==' ') {
        int myi, myj;
        for (int i = 0; i <core.NES_W;i++) {
            for (int j = 0; j<core.NES_H; j++) {
                if(blocks_side[i][j].spawn_set){
                    myi = i;
                    myj = j;
                    player.setPosition(spawn);
                    player.alive = true;
                }
            }
        }

    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    if(true){
        
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    drawing = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    drawing = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
