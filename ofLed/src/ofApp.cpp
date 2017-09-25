#include "ofApp.h"

vector <ofVec4f> stars;
bool toggle;

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0, 0, 0);                      // default background to black / LEDs off
	ofDisableAntiAliasing();                    // we need our graphics sharp for the LEDs
	ofSetVerticalSync(false);
	ofSetFrameRate(60);

	// SYSTEM SETTINGS
	//--------------------------------------
	stripWidth = 16;                            // pixel width of strip
	stripHeight = 128;                            // pixel height of strip
	rowHeight = 16;
	stripsPerPort = 1;                          // total number of strips per port
	numPorts = 1;                               // total number of teensy ports?
	brightness = 100;                             // LED brightness

	rectWidth = 1;

	// setup our teensys
	teensy.setup(stripWidth, stripHeight, rowHeight, stripsPerPort, numPorts);

	/* Configure our teensy boards (portName, xOffset, yOffset, width%, height%, direction) */
	//teensy.serialConfigure("cu.usbmodem2809741", 0, 0, 100, 100, 0);
	teensy.serialConfigure("ttyACM0", 0, 0, 100, 100, 0);
	//teensy.serialConfigure("cu.usbmodem2733511", 0, 0, 100, 100, 0);
	teensy.setBrightness(brightness);

	// allocate our pixels, fbo, and texture
	fbo.allocate(stripWidth, stripHeight*stripsPerPort*numPorts, GL_RGB);

	toggle = false;
	stars.resize(80);

	for(int i=0; i < stars.size(); i++) {
		stars[i].x = ofRandom(-stripWidth, stripWidth);
		stars[i].y = ofRandom(-rowHeight, rowHeight);
		stars[i].z = ofRandom(0, stripWidth);
		stars[i].w = stars[i].z;
		ofLog(OF_LOG_NOTICE, ofToString(stars[i]));
	}
}

void ofApp::exit(){
	/* turn all leds to black */
	/*
	fbo.begin();
	ofClear(0,0,0);
	fbo.end();
	fbo.readToPixels(teensy.pixels1);
	teensy.update();
	*/
}

//--------------------------------------------------------------
void ofApp::update(){
	for(int i=0; i < stars.size(); i++) {
		stars[i].z = stars[i].z - .5;

		if(!toggle)
			stars[i].w = stars[i].z;

		if(stars[i].z < 1) {
			stars[i].x = ofRandom(-stripWidth, stripWidth);
			stars[i].y = ofRandom(-rowHeight, rowHeight);
			stars[i].z = stripWidth;
			stars[i].w = stars[i].z;
		}
	}

	updateFbo();                                // update our Fbo functions
	teensy.update();                            // update our serial to teensy stuff
}

//--------------------------------------------------------------
void ofApp::updateFbo(){
	fbo.begin();                                // begins the fbo
	ofClear(0,0,0);                             // refreshes fbo, removes artifacts

	ofSetColor(255);

	ofPushStyle();
	ofPushMatrix(); 

	ofTranslate( stripWidth / 2.f, rowHeight / 2.f );
	
	for(int i=0; i < stars.size(); i++) {
		star(stars[i].x, stars[i].y, stars[i].z, stars[i].w);
	}
	
	ofPopMatrix();

	ofPopStyle();

	fbo.end();                                  // closes the fbo

	fbo.readToPixels(teensy.pixels1);           // send fbo pixels to teensy
}

void ofApp::star(float x, float y, float z, float w) {
	ofSetColor(255,130,0);
	ofFill();

	float sx = ofMap(x / z, 0, 1, 0, stripWidth);
	float sy = ofMap(y / z, 0, 1, 0, rowHeight);
	float r = ofMap(z, 0, stripWidth, 2, 0);
	if(!toggle)
		ofDrawCircle(sx, sy, r);

	float px = ofMap(x / w, 0, 1, 0, stripWidth);
	float py = ofMap(y / w, 0, 1, 0, rowHeight);
	if(toggle)
		ofDrawLine(px,py,sx,sy);
}

//--------------------------------------------------------------
void ofApp::draw(){
	teensy.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 
	switch (key){
		//-----------------------------------------------
		case OF_KEY_UP:
			brightness += 2;
			if (brightness > 255) brightness = 255;
			teensy.setBrightness(brightness);
			break;
			
		case OF_KEY_DOWN:
			brightness -= 2;
			if (brightness < 0) brightness = 0;
			teensy.setBrightness(brightness);
			break;
		default:
			toggle = !toggle;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
