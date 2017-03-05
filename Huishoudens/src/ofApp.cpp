#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(ofColor::black);
	db = new SQLite::Database("data/huishoudens.sqlite");

	
	//SQLite::Statement query(*db, "SELECT * FROM huish WHERE year");
	//while (query.executeStep())
	//{
	//	ofLog() << query.getColumn("year") << " " << query.getColumn("hh_total") << endl;
	//}

	SQLite::Statement query(*db, "SELECT * FROM huish WHERE year=?");
	for (int year = 2012; year <= 2016; year++)
	{
		query.bind(1, year);
		if (query.executeStep())
		{
			ofLog() << query.getColumn("year") << " " << query.getColumn("hh_total") << endl;
		}
		query.reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	int year = ofMap(ofGetMouseX(), 0, ofGetWidth() - ofGetWidth() / 5, 2012, 2016, true);

	if (year != selectedYear)
	{
		selectedYear = year;
		string statement = "SELECT hh_total, (hh_single*1.0/hh_total * 100), (hh_multiple*1.0/hh_total * 100) FROM huish WHERE year =?";
		SQLite::Statement query(*db, statement);
		query.bind(1, selectedYear);
		if (query.executeStep())
		{
			pctSingle = query.getColumn(1).getDouble();
			pctMultiple = query.getColumn(2).getDouble();
			ofLog() << selectedYear << " | " << pctSingle << " " << pctMultiple << endl;
		}
		query.reset();
	}

	for (int i = 0; i < 20; i++)
	{
		//sine = sin(ofGetElapsedTimef() * i / pctSingle) * (pctSingle * 5);
		//ballsSine[i] = sine;
		//cose = cos(ofGetElapsedTimef() * i / pctMultiple) * (pctMultiple * 5);
		//ballsCose[i] = cose;
		sine = sin(ofGetElapsedTimef() * i / 20) * (pctSingle * 5);
		ballsSine[i] = sine;
		cose = cos(ofGetElapsedTimef() * i / 20) * (pctMultiple * 5);
		ballsCose[i] = cose;
		//sine = sin(ofGetElapsedTimef() * pctSingle * i / 100) * (pctSingle * 5);
		//ballsSine[i] = sine;
		//cose = cos(ofGetElapsedTimef() * pctMultiple * i / 100) * (pctMultiple * 5);
		//ballsCose[i] = cose;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::white);
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	if (selectedYear == 2012)
	{
		ofDrawBitmapString(selectedYear, -10, 0);
	}
	if (selectedYear == 2013)
	{
		ofDrawBitmapString(selectedYear, -10, 0);
	}
	if (selectedYear == 2014)
	{
		ofDrawBitmapString(selectedYear, -10, 0);
	}
	if (selectedYear == 2015)
	{
		ofDrawBitmapString(selectedYear, -10, 0);
	}
	if (selectedYear == 2016)
	{
		ofDrawBitmapString(selectedYear, -10, 0);
	}
	for (int i = 0; i < 20; i++)
	{
		ofCircle(ballsSine[i], ballsCose[i], 30);
	}

}