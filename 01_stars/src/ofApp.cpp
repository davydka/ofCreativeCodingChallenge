#include "ofApp.h"

vector <ofVec4f> stars;
bool toggle;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
	ofSetFrameRate(60); 

	ofSetWindowPosition(0, 0);
	ofSetWindowShape(320, 320);

	toggle = false;
	stars.resize(800);

	for(int i=0; i < stars.size(); i++) {
		stars[i].x = ofRandom(-ofGetWidth(), ofGetWidth());
		stars[i].y = ofRandom(-ofGetHeight(), ofGetHeight());
		stars[i].z = ofRandom(0, ofGetWidth());
		stars[i].w = stars[i].z;
		// ofLog(OF_LOG_NOTICE, ofToString(stars[i]));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for(int i=0; i < stars.size(); i++) {
		stars[i].z = stars[i].z - 10;

		if(!toggle)
			stars[i].w = stars[i].z;

		if(stars[i].z < 1) {
			stars[i].x = ofRandom(-ofGetWidth(), ofGetWidth());
			stars[i].y = ofRandom(-ofGetHeight(), ofGetHeight());
			stars[i].z = ofGetWidth();
			stars[i].w = stars[i].z;
		}
	}

}


void ofApp::star(float x, float y, float z, float w) {
	ofSetColor(255,130,0);
	ofFill();

	float sx = ofMap(x / z, 0, 1, 0, ofGetWidth());
	float sy = ofMap(y / z, 0, 1, 0, ofGetHeight());
	float r = ofMap(z, 0, ofGetWidth(), 8, 0);
	if(!toggle)
		ofDrawCircle(sx, sy, r);

	float px = ofMap(x / w, 0, 1, 0, ofGetWidth());
	float py = ofMap(y / w, 0, 1, 0, ofGetHeight());
	if(toggle)
		ofDrawLine(px,py,sx,sy);
}


//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix(); 

	ofTranslate( ofGetWidth() / 2.f, ofGetHeight() / 2.f );
	for(int i=0; i < stars.size(); i++) {
		star(stars[i].x, stars[i].y, stars[i].z, stars[i].w);
	}
	
	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	toggle = !toggle;
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
