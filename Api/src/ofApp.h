#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxTrueTypeFontUC.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);


		void getData();

		ofxJSONElement json;

		float temp;
		int item;

		string date;
		string icon;

		string dateList[34];
		string iconList[34];
		float celcius[34];

		

		int spaceBetween;

		//ofURLFileLoader fileLoader;

		ofHttpResponse myResponse;
		string currentIconName;

		ofPoint lijnPunten[8];

		//ofTrueTypeFont myfont;
		ofxTrueTypeFontUC myfont;
		ofxTrueTypeFontUC celsius;

		ofImage weatherIcon;
		


};
