#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    wallpaper.setup();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
    wallpaper.update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofEnableDepthTest();
    
    ofBackground(0);
    
    wallpaper.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == OF_KEY_LEFT){
        wallpaper.applyEffectToAll(Tile::FLIP_OUT);
    } else if(key == OF_KEY_RIGHT){
        wallpaper.applyEffectToAll(Tile::FLIP_IN);
    } else if(key == OF_KEY_UP){
        wallpaper.applyEffectToAll(Tile::FLIP_TRANSITION_HORIZ);
    } else if(key == OF_KEY_DOWN){
        wallpaper.applyEffectToAll(Tile::FLIP_TRANSITION_VERT);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    wallpaper.triggerWave(ofVec2f(x, y));
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
