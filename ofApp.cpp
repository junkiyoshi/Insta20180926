#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->number_of_targets = 48;
	for (int i = 0; i < this->number_of_targets; i++) {

		this->targets.push_back(glm::vec2());
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	float x_seed, y_seed;

	for (int i = 0; i < this->number_of_targets; i++) {

		if (i % 12 == 0) {

			x_seed = ofRandom(100);
			y_seed = ofRandom(100);
		}

		int x_base = (i / 24) * 360;
		int y_base = ((i / 12) % 2) * 360;

		int x = ofMap(ofNoise(x_seed, (ofGetFrameNum() + i) * 0.03), 0, 1, x_base, x_base + 360);
		int y = ofMap(ofNoise(y_seed, (ofGetFrameNum() + i) * 0.03), 0, 1, y_base, y_base + 360);

		this->targets[i] = glm::vec2(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &this->targets[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}