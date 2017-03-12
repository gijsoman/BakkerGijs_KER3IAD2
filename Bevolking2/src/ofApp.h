#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "SQLiteCpp.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
	private:
		SQLite::Database* db;
		ofxIntSlider year;
		ofxPanel gui;

		//columns
		int selectedYear;
		int total;
		int men;
		int women;
		int married;
		int unmarried;
		int widowed;
		int divorced;


		int lastKnownMarried;
		int lastKnownUnmarried;
		int lastKnownWidowed;
		int lastKnownDivorced ;

		ofTrueTypeFont myfont;
		ofTrueTypeFont myfont2;
		
};
