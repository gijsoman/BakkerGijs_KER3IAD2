#include "ofApp.h"

#define SENSOR 2

//--------------------------------------------------------------
void ofApp::setup(){
	homeScreen.load("homeScreen.png");
	slideScreen.load("slideScreen.png");
	
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	arduino.connect("COM2");
	arduino.sendFirmwareVersionRequest();

	myfont.load("Insignia.ttf",75);
}

//--------------------------------------------------------------
void ofApp::update(){
	arduino.update();
	//scroll up the home screen
	if (scrollUp)
	{
		if (homeY > -1080)
		{
			homeY -= 20;
			slideY -= 20;
		}
		else
		{
			scrolledUp = true;
		}
	}
	//scroll down the home screen
	if (scrollDown)
	{
		if (homeY < 0)
		{
			homeY += 20;
			slideY += 20;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//check if they are allowed to be drawn. then draw them.
	if (drawHomescreen)
	{
		homeScreen.draw(0, homeY);
	}
	if (drawSlidescreen)
	{
		slideScreen.draw(0, slideY);
	}
	if (scrolledUp)
	{
		ofSetColor(ofColor::black);
		myfont.drawString(ofToString(year), ofGetWindowWidth()/2 - myfont.stringWidth(ofToString(year))/2, 945);
		ofSetColor(255, 255, 255, 255);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//check the keypressed and change the booleans if sensor not works
	if (key == 's')
	{
		scrollUp = true;
		scrollDown = false;
		drawSlidescreen = true;
	}
	if (key == 'r')
	{
		scrollUp = false;
		scrollDown = true;
		scrolledUp = false;
	}
	if (key == OF_KEY_RIGHT)
	{
		year++;
		if (year > 2017)
		{
			year = 2017;
		}
	}
	if (key == OF_KEY_LEFT)
	{
		year--;
		if (year < 1930)
		{
			year = 1930;
		}
	}
}


void ofApp::setupArduino(const int& version) {
	ofLogNotice() << "Arduino initialized" << endl;
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	arduino.sendDigitalPinMode(SENSOR, ARD_INPUT);

	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);


}
void ofApp::digitalPinChanged(const int& pin) {
	int value = arduino.getDigital(pin);
	ofLogVerbose() << "Digital pin" << pin << " changed to " << value << endl;
	if (pin == SENSOR && value == 0) {
		ofLog() << "hallo" << endl;
		scrollUp = true;
		scrollDown = false;
		drawSlidescreen = true;
	}
	else
	{
		ofLog() << "doei" << endl;
	}
}





