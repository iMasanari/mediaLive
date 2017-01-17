#include "ofApp.h"

void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    cam.setVerbose(true);
    cam.listDevices();
    cam.setDeviceID(0);
    
    ofSetVerticalSync(true);
    cam.initGrabber(640, 480);
    
    image.load("Cinderella_Base.png");
    hair.load("Cinderella_Hair02.png");
    
    tracker.setup();
    
    gui.setup();
    gui.add(posX.setup("posX", 0.242, 0, 1));
    gui.add(posY.setup("posY", 0.335, 0, 1));
    gui.add(rotateX.setup("rotateX", 9, -180, 180));
    gui.add(rotateY.setup("rotateY", 7.2, -180, 180));
    gui.add(scale.setup("scale", 1.05, 0, 10));
    
    gui.add(screenY.setup("screenY", 110, 0, ofGetHeight()));
    
    ofBackground(0);
}

void ofApp::update() {
    cam.update();
    
    if(cam.isFrameNew()) {
        tracker.update(ofxCv::toCv(cam));
    }
}

ofMesh ofApp::getNewMesh(ofMesh baseMesh, int indexs[], int len) {
    ofMesh mesh = ofMesh();
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    vector<ofVec3f> vertices = baseMesh.getVertices();
    vector<ofVec2f> texCoords = baseMesh.getTexCoords();
    
    for (int i = 0; i < len; ++i) {
        mesh.addVertex( vertices[indexs[i]] );
        mesh.addTexCoord( texCoords[indexs[i]] );
    }
    
    return mesh;
}

void ofApp::draw() {
    ofSetColor(255);
    
    image.draw(0, screenY, ofGetWidth(), ofGetWidth() * 0.56);
    
    if (guiFrag) {
        cam.draw(0, 0);
        gui.draw();
        ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
        
        if(tracker.getFound()) {
            tracker.draw();
        }
    }
    
    if(tracker.getFound()) {
//        faceMesh = tracker.getMeanObjectMesh();
        faceMesh = tracker.getObjectMesh();
        
        int leftEye[] = {36, 37, 41, 38, 40, 39};
        leftEyeMesh = getNewMesh(faceMesh, leftEye, arraySize(leftEye));
        
        int rightEye[] = {42, 43, 47, 44, 46, 45};
        rightEyeMesh = getNewMesh(faceMesh, rightEye, arraySize(rightEye));
        
        int mouse[] = {48, 60, 65, 61, 64, 62, 63, 54};
        mouseMesh = getNewMesh(faceMesh, mouse, arraySize(mouse));
        
        alpha += 10;
        
        if (alpha > 255) {
            alpha = 255;
        }
    }
    else {
        alpha -= 20;
        
        if (alpha < 0) {
            alpha = 0;
        }
    }
    
    ofSetupScreenOrtho(ofGetWidth(), ofGetHeight(), -1000, 1000);
    ofPushMatrix();
    ofTranslate(ofGetWidth() * posX, ofGetWidth() * 0.56 * posY + screenY);
    float currentScale = scale * ofGetWidth() / 1000;
    ofScale(currentScale, currentScale, currentScale);
    
    ofRotateX(rotateX);
    ofRotateY(rotateY);
    
    ofSetColor(255, alpha);
    
    cam.getTexture().bind();
    leftEyeMesh.draw();
    rightEyeMesh.draw();
    mouseMesh.draw();
    faceMesh.draw();
    cam.getTexture().unbind();
    
    ofPopMatrix();
    
    ofSetColor(255);
    hair.draw(0, screenY, ofGetWidth(), ofGetWidth() * 0.56);
}

void ofApp::keyPressed(int key) {
    if(key == 'r') {
        tracker.reset();
    }
    else if (key == 'f') {
        ofToggleFullscreen();
    }
    else if(key == ' ') {
        guiFrag = !guiFrag;
    }
}
