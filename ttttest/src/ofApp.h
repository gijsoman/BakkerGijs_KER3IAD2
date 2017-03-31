#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void getData();

		ofxJSONElement json;

		float temp;
		int item;

		//vector gebruiken
		string date;

		string dateList[34];
		float celcius[34];

		int spaceBetween;

		ofPoint lijnPunten[8];

		ofTrueTypeFont myfont;

};
