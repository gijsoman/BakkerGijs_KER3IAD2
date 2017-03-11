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
		ofxToggle menWomen;
		ofxToggle marriedUnmarried;
		ofxPanel gui;
		int selectedYear;
		int total;
		int men;
		int women;
		int married;
		int unmarried;
		
};
