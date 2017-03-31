#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		//Creating the variables for the images
		ofImage homeScreen;
		ofImage slideScreen;

		//These bools are used to deside if the homeScreen and slideScreen may be drawn
		//I use them to make the draw function responsible for drawing not the keyPressed function.
		bool drawHomescreen = true;
		bool drawSlidescreen;

		//variables to animate screen.
		int homeY = 0;
		int slideY = 1080;
		bool scrollUp = false;
		bool scrollDown = false;
		bool scrolledUp = false;

		//for connection with firmata
		ofArduino arduino;
		void setupArduino(const int& version);
		void digitalPinChanged(const int& pin);

		//font for years
		ofTrueTypeFont myfont;

		//control year
		int year = 1930;
};
