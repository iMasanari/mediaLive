#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    serial.setup(0, 9600);
    video.load("anime.mp4");
    video1.load("anime1.mp4");
    video.setLoopState(OF_LOOP_NONE);
    video1.setLoopState(OF_LOOP_NONE);
    
    gui.setup();
    gui.add(posX.setup("posX", 0, 0, ofGetWidth()));
    gui.add(posY.setup("posY", 23.04, 0, ofGetHeight()));
    gui.add(scale.setup("scale", 0.94, 0, 2));
    
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    video1.update();
    
    string str;
    do {
        str = getSerialString(serial, '\n'); //read until end of line
        
        if (str == "" || str == "-") continue;
        
        ofLog() << str;
        
        int rotate = std::stoi(str);
        
        if (isPlay && rotate > 0){
            if (videoToggleFlag) {
                video.stop();
            }
            else {
                video1.stop();
            }
            
            isPlay = false;
            ofLog() << "video.stop();";
        }
        else if (!isPlay && rotate < -40){
            videoToggleFlag = !videoToggleFlag;
            
            if (videoToggleFlag) {
                video.play();
            }
            else {
                video1.play();
            }
            
            isPlay = true;
            ofLog() << "video.play();";
        }

        //do something with str
    } while (str != "");
}

//--------------------------------------------------------------
void ofApp::draw(){
//    int alpha = ofMap(rotate, 60, -60, 0, 255);
//    ofSetColor(255, alpha);
    
    if (videoToggleFlag) {
        video.draw(posX, posY, video.getWidth() * scale, video.getHeight() * scale);
    }
    else {
        video1.draw(posX, posY, video1.getWidth() * scale, video1.getHeight() * scale);
    }
    
    
    if (isGuiDraw) {
        gui.draw();
    }
}

string ofxTrimStringRight(string str) {
    size_t endpos = str.find_last_not_of(" \t\r\n");
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
}

string ofxTrimStringLeft(string str) {
    size_t startpos = str.find_first_not_of(" \t\r\n");
    return (string::npos != startpos) ? str.substr(startpos) : str;
}

string ofxTrimString(string str) {
    return ofxTrimStringLeft(ofxTrimStringRight(str));;
}

string ofApp::getSerialString(ofSerial &serial, char until) {
    static string str;
    stringstream ss;
    char ch;
    int ttl = 1000;
    
    while ((ch = serial.readByte()) > 0 && ttl-- > 0 && ch != until) {
        ss << ch;
    }
    str += ss.str();
    
    if (ch==until) {
        string tmp = str;
        str = "";
        return ofxTrimString(tmp);
    }
    else {
        return "";
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ': {
            isGuiDraw = !isGuiDraw;
            break;
        }
        case 'f': {
            ofToggleFullscreen();
            break;
        }
    }
}
