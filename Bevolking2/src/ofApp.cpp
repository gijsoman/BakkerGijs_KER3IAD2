#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(ofColor::black);
	db = new SQLite::Database("data/bevolking.sqlite");

	gui.setup();
	gui.add(year.setup("year", 1947, 1947, 2016));

	myfont.load("GOTHIC.TTF", 50);
	myfont2.load("GOTHIC.TTF", 12);
}


//--------------------------------------------------------------
void ofApp::update(){

	if (year != selectedYear)
	{
		selectedYear = year;
		string statement = "SELECT divorced, widowed, married, unmarried FROM bevolking WHERE year =?";
		SQLite::Statement query(*db, statement);
		query.bind(1, year);
		if (query.executeStep())
		{
			married = query.getColumn(2).getInt();
			unmarried = query.getColumn(3).getInt();
			widowed = query.getColumn(1).getInt();
			divorced = query.getColumn(0).getInt();
			ofLog() << selectedYear << " | " << married << " | " << unmarried << " | " << divorced << " | " << widowed << " | " << endl;
		}
		query.reset();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();

	if (married != 0)
	{
		lastKnownMarried = married;
		ofSetColor(ofColor(173,141,87));
		ofDrawRectangle(400, 500, 100, -(married / 50));
		myfont2.drawString("married", 400, 500 + 20);
		myfont2.drawString(ofToString(married) , 400, 500 - (married / 50) - 10);
	}
	else
	{
		ofSetColor(ofColor(173, 141, 87));
		ofDrawRectangle(400, 500, 100, -(lastKnownMarried / 50));
		myfont2.drawString("married", 400, 500 + 20);
		myfont2.drawString(ofToString(lastKnownMarried), 400, 500 - (lastKnownMarried / 50) - 10);
	}

	if (divorced != 0)
	{
		lastKnownDivorced = divorced;
		ofSetColor(ofColor(121, 129, 161));
		ofDrawRectangle(500, 500, 100, -(divorced / 50));
		myfont2.drawString("divorced", 500, 500 + 20);
		myfont2.drawString(ofToString(divorced), 500, 500 - (divorced / 50) - 10);
	}
	else
	{
		ofSetColor(ofColor(121, 129, 161));
		ofDrawRectangle(500, 500, 100, -(lastKnownDivorced / 50));
		myfont2.drawString("divorced", 500, 500 + 20);
		myfont2.drawString(ofToString(lastKnownDivorced), 500, 500 - (lastKnownDivorced / 50) - 10);
	}


	if (selectedYear > 1971 && selectedYear < 1991)
	{
		ofSetColor(ofColor(212,198,183));
		myfont.drawString("Invoer echtscheidingsrecht", 75, 700);
	}
	else if (selectedYear >= 1991)
	{
		ofSetColor(ofColor(212, 198, 183));
		myfont.drawString("World Wide Web gepubliceerd", 75, 700);
	}
	//if(widowed)
	
	/*ofDrawBitmapString(total, 500, ofMap(total / 50, 102, 339, 339 , 102) +50);*/
	//start value 380 end value 150

}
