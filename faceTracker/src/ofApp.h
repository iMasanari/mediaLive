#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
    
    ofMesh faceMesh;
    ofMesh leftEyeMesh;
    ofMesh rightEyeMesh;
    ofMesh mouseMesh;
    
    ofxPanel gui;
    bool guiFrag = false;
    
    ofxFloatSlider posX;
    ofxFloatSlider posY;
    ofxFloatSlider rotateX;
    ofxFloatSlider rotateY;
    ofxFloatSlider scale;
    
    
    ofxFloatSlider screenY;
    
    ofImage image;
    ofImage hair;
    ofFbo fbo;
    
    int alpha = 255;
    
    ofMesh getNewMesh(ofMesh baseMesh, int indexs[], int len);
    
    template <typename Array, int N>
    constexpr int arraySize( Array (&)[N] ) const {
        return N;
    }
};
