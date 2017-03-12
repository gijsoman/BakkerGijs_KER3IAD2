#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(ofColor::black);
	db = new SQLite::Database("data/bevolking.sqlite");

	gui.setup();
	gui.add(year.setup("year", 1900, 1900, 2016));
	gui.add(menWomen.setup("Men/Women", false));
	gui.add(marriedUnmarried.setup("Married/Unmarried", false));
}


//--------------------------------------------------------------
void ofApp::update(){

	if (year != selectedYear)
	{
		selectedYear = year;
		string statement = "SELECT total, men, women, married, unmarried FROM bevolking WHERE year =?";
		SQLite::Statement query(*db, statement);
		query.bind(1, year);
		if (query.executeStep())
		{
			total = query.getColumn(0).getInt();
			men = query.getColumn(1).getInt();
			women = query.getColumn(2).getInt();
			married = query.getColumn(3).getInt();
			unmarried = query.getColumn(4).getInt();
			ofLog() << selectedYear << " | " << total << endl;
		}
		query.reset();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();

	ofSetColor(ofColor::white);
	ofDrawRectangle(500, 500, 100, -(total/50));
	if (menWomen)
	{
		ofSetColor(ofColor::pink);
		ofDrawRectangle(600, 500, 100, -(women / 50));
		ofSetColor(ofColor::blue);
		ofDrawRectangle(400, 500, 100, -(men / 50));
		ofSetColor(ofColor::green);
		ofDrawBitmapString("men", 400, 500 + 20);
		ofDrawBitmapString(men, 400, 500 - (men / 50) - 10);
		ofDrawBitmapString("women", 600, 500 + 20);
		ofDrawBitmapString(women, 600, 500 - (women / 50) - 10);
	}
	if (marriedUnmarried)
	{
		if (!menWomen)
		{
			if (married != 0)
			{
				lastKnownMarried = married;
				lastKnownUnmarried = unmarried;
				ofSetColor(ofColor::red);
				ofDrawRectangle(300, 500, 100, -(unmarried / 50));
				ofSetColor(ofColor::green);
				ofDrawRectangle(400, 500, 100, -(married / 50));
				ofDrawBitmapString("unmarried", 300, 500 + 20);
				ofDrawBitmapString(unmarried, 300, 500 - (unmarried / 50) - 10);
				ofDrawBitmapString("married", 400, 500 + 20);
				ofDrawBitmapString(married, 400, 500 - (married / 50) - 10);
			}
			else
			{
				ofSetColor(ofColor::red);
				ofDrawRectangle(300, 500, 100, -(lastKnownUnmarried / 50));
				ofSetColor(ofColor::green);
				ofDrawRectangle(400, 500, 100, -(lastKnownMarried / 50));
				ofDrawBitmapString("unmarried", 300, 500 + 20);
				ofDrawBitmapString(lastKnownUnmarried, 300, 500 - (lastKnownUnmarried / 50) - 10);
				ofDrawBitmapString("married", 400, 500 + 20);
				ofDrawBitmapString(lastKnownMarried, 400, 500 - (lastKnownMarried / 50) - 10);
			}
		}
		else
		{
			if (married != 0)
			{
				lastKnownMarried = married;
				lastKnownUnmarried = unmarried;
				ofSetColor(ofColor::red);
				ofDrawRectangle(200, 500, 100, -(unmarried / 50));
				ofSetColor(ofColor::green);
				ofDrawRectangle(300, 500, 100, -(married / 50));
				ofDrawBitmapString("unmarried", 200, 500 + 20);
				ofDrawBitmapString(unmarried, 200, 500 - (unmarried / 50) - 10);
				ofDrawBitmapString("married", 300, 500 + 20);
				ofDrawBitmapString(married, 300, 500 - (married / 50) - 10);
			}
			else
			{
				ofSetColor(ofColor::red);
				ofDrawRectangle(200, 500, 100, -(lastKnownUnmarried / 50));
				ofSetColor(ofColor::green);
				ofDrawRectangle(300, 500, 100, -(lastKnownMarried / 50));
				ofDrawBitmapString("unmarried", 200, 500 + 20);
				ofDrawBitmapString(lastKnownUnmarried, 200, 500 - (lastKnownUnmarried / 50) - 10);
				ofDrawBitmapString("married", 300, 500 + 20);
				ofDrawBitmapString(lastKnownMarried, 300, 500 - (lastKnownMarried / 50) - 10);
			}
		}

		
	}
	
	ofSetColor(ofColor::green);
	ofDrawBitmapString("total", 500, 500 + 20);
	ofDrawBitmapString(total, 500, 500 -(total/50) - 10);
	/*ofDrawBitmapString(total, 500, ofMap(total / 50, 102, 339, 339 , 102) +50);*/
	//start value 380 end value 150

}
