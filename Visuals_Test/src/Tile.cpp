//
//  Tile.cpp
//  Visuals_Test
//
//  Created by Adiel Fernandez on 10/23/16.
//
//

#include "Tile.hpp"


Tile::Tile(){
    
    
    
}

void Tile::setup(vector<ofVec3f> verts, float _tileWidth){
    
    tileWidth = _tileWidth;
    tileCenter.set(tileWidth/2, tileWidth/2);
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    //Tile will center at origin for ease of manipulation
    //but store the top left corner so we know where tile needs to be placed on wallpaper
    ofVec3f topLeftCorner(verts[0]);

    positionOnWall = topLeftCorner + tileCenter;
    
    for(int i = 0; i < verts.size(); i++){
        
        //add the vert but subtract the origin and tile center
        //so the mesh draws around (0,0)
        mesh.addVertex(verts[i] - topLeftCorner - tileCenter);
        
        //but maintain verts relative to 1920x1200 image
        //for texcoords
        mesh.addTexCoord(verts[i]);
        
    }
    

    bRotating = false;
    
    bFlipTransition = false;
    bFlipInOut = false;
    bDrawDarkBacking = true;
    bIsBackward = true;
    flipSpeed = 0.02;

    //angle = 0: tile facing forward
    rotAxis.set(0, 1, 0);
    startAngle = 0;
    endAngle = 0;
    currentAngle = 180;
    
    effectStartTime = 0.0;
    effectStagger = 0.0;
    effectEndTime = 0.0;
    effectDuration = 1.0;
    

    distSqToEpicenter = 0;
    
    debugCout = false;
    
}

void Tile::setTextures(vector<ofImage> *imgs){
    
    images = imgs;
    
}

void Tile::setActiveTexture(int num){
    
    activeTexNum = num;
    
}

void Tile::setNextTexture(int num){
    
    nextTexNum = num;
    
}

void Tile::triggerWaveTransition(ofVec2f epicenter){
    
    //calculate the angle for the flip by getting the angle to the epicenter
    ofVec2f dirToEpicenter = epicenter - positionOnWall;
    
    //then rotate 90 degrees in Z to make it purpendicular to epicenter direction
    dirToEpicenter.normalize();
//    dirToEpicenter.rotate(90);
    
    triggerEffect(FLIP_TRANSITION_HORIZ, 0.0, dirToEpicenter);
    
    
    
}

void Tile::triggerEffect(Tile::Effect e, float stagger, ofVec3f flipAxis){
    
    
    
    switch (e) {
        case FLIP_TRANSITION_HORIZ:
            
            startAngle = 0;
            endAngle = 180;
            
            rotAxis.set(0, 1, 0);
            
            bFlipTransition = true;
            bDrawDarkBacking = false;
            
            break;

        case FLIP_TRANSITION_VERT:
            
            
            
            break;
            
        case FLIP_TRANSITION_AXIS:
            
            startAngle = 0;
            endAngle = 180;
            
            rotAxis = flipAxis;
            
            bFlipTransition = true;
            bDrawDarkBacking = false;
            
            
            break;

        case FLIP_OUT:
            
            startAngle = 0;
            endAngle = 180;
            
            rotAxis.set(0, 1, 0); // flip horizontally
            
            bFlipInOut = true;
            bDrawDarkBacking = true;
            
            break;
            
        case FLIP_IN:
            
            startAngle = 180;
            endAngle = 0;
            
            rotAxis.set(0, 1, 0); // flip horizontally
            
            bFlipInOut = true;
            bDrawDarkBacking = true;

            
            break;
            
        default:
            break;
    }
    
    
    effectStagger = stagger;
    effectStartTime = ofGetElapsedTimef() + effectStagger;
    effectEndTime = effectStartTime + effectDuration;
    
    
}

void Tile::update(){
    
    if(bFlipInOut || bFlipTransition){
        
        float now = ofGetElapsedTimef();
        
        //bounce ease the angle
        currentAngle = ofxeasing::map_clamp(now, effectStartTime, effectEndTime, startAngle, endAngle, &ofxeasing::back::easeOut_s, 1.0);
        
        
        if(now > effectStartTime + effectDuration){
        
            if(bFlipTransition){
                
                //set the next texture to the active one
                activeTexNum = nextTexNum;
                
                //and set the current angle to 0 to complete the flipping illusion
                currentAngle = 0;
                
                bFlipTransition = false;
            
            } else {
                
                bFlipInOut = false;
            
            }
            
            
        }
        
    }
    
    
    
    
    
}

void Tile::draw(){

    ofPushMatrix();
    
    //Mesh is positioned around it's origin so
    //translate to the center of the tile position
    ofTranslate(positionOnWall);
    
    ofRotate(currentAngle, rotAxis.x, rotAxis.y, rotAxis.z);
    
    images -> at(activeTexNum).bind();
    
    ofSetColor(255);
    mesh.draw();
    
    images -> at(activeTexNum).unbind();
    
    
    //draw an opaque black square on the flip side of it
    if(bDrawDarkBacking){
        
        ofPushMatrix();
        ofTranslate(0, 0, -0.1);
        ofSetColor(0);
        ofDrawRectangle(-tileWidth/2, -tileWidth/2, tileWidth, tileWidth);
        ofPopMatrix();
        
    }
    
    //draw secondary texture on the flip side of it during transitions
    //we need to rotate it into place so that it is properly oriented
    //when it faces front
    if(bFlipTransition){
        
        ofPushMatrix();
        ofRotateY(180);
        //push it forward (i.e. behind since it's been turned) a bit so
        //it draws slightly off the front mesh
        ofTranslate(0, 0, 0.1);
        
        images -> at(nextTexNum).bind();
        
        ofSetColor(255);
        mesh.draw();
        
        images -> at(nextTexNum).unbind();
        
        ofPopMatrix();

    }
    
    ofPopMatrix();
    
}





