#include "ofApp.h"

#define PIN_LED 13
#define PIN_BUTTON 11
#define PIN_POTMETER 1
#define PIN_LDR 0
#define PIN_VIB 2

void ofApp::setup() {
    // set listener - call ofApp::setupArduino when arduino is ready for use
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

    // connect to the Arduino
    // use the same device name used in the Arduino IDE
    arduino.connect("COM10");
    arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug

	ofSetLogLevel(OF_LOG_NOTICE);
}

void ofApp::update() {
    arduino.update();
//    ofLog() << "isArduinoReady" << arduino.isArduinoReady() << endl;
}

void ofApp::draw() {
	ofDrawBitmapString(ofToString(vibr), 100, 100);
}

void ofApp::setupArduino(const int& version) {
    // remove listener because we don't need it anymore
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

    // print firmware name and version to the console
    ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
            << " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

    arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
    arduino.sendDigitalPinMode(PIN_BUTTON, ARD_INPUT);
    arduino.sendAnalogPinReporting(PIN_LDR, ARD_ANALOG);
    arduino.sendAnalogPinReporting(PIN_POTMETER, ARD_ANALOG);

    // set listeners for pin events
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::digitalPinChanged(const int& pinNum) {
    // get value with arduino.getDigital(pinNum)
   /* ofLogNotice() << "Digital Pin " << pinNum << " value: " << arduino.getDigital(pinNum) << endl;*/
}

void ofApp::analogPinChanged(const int& pinNum) {
    // get value with arduino.getAnalog(pinNum));
    
	
	int value = arduino.getAnalog(pinNum);
	if (pinNum == PIN_VIB)
	{
		ofLogNotice() << "Analog Pin " << pinNum << " value: " << arduino.getAnalog(pinNum) << endl;
		vibr = value;
	}
}


void ofApp::mousePressed(int x, int y, int button) {
    // switch the LED on
    arduino.sendDigital(PIN_LED, ARD_HIGH);
}

void ofApp::mouseReleased(int x, int y, int button) {
    // switch the LED off
    arduino.sendDigital(PIN_LED, ARD_LOW);
}
