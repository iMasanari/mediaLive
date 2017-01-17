#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
    ofVideoPlayer video;
    ofVideoPlayer video1;
    
    bool videoToggleFlag = false;
    bool isPlay = false;
    
    ofSerial serial;
    string getSerialString(ofSerial &serial, char until);
    
    ofxPanel gui;
    
    ofxFloatSlider posX;
    ofxFloatSlider posY;
    ofxFloatSlider scale;
    
    bool isGuiDraw = false;
};
