#include <SQLiteCpp/include/SQLiteCpp/Database.h>
#include "ofApp.h"

void ofApp::setup() {
    string databasePath = ofToDataPath("bevolking.sqlite", true);
    db = new SQLite::Database(databasePath);
	ofSetBackgroundColor(ofColor::grey);

	myfont.load("ALGER.TTF", 100);
	myfont2.load("GOTHIC.TTF", 20);
}

void ofApp::update() {
    int year = ofMap(ofGetMouseX(), 0, ofGetWidth() - 100, 1900, 2016, true);

    if (year != selectedYear) {
        selectedYear = year;
        string sql = "SELECT year, north, east, south, west, north+east+south+west AS total FROM bevolking WHERE year=?";

        SQLite::Statement query(*db, sql);

        query.bind(1, selectedYear); // vervang 1e vraagteken door de waarde van de variabele
        if (query.executeStep()) {
            total = query.getColumn("total").getInt();
            year = query.getColumn("year").getInt();
            north = query.getColumn("north").getInt();
            east = query.getColumn("east").getInt();
            south = query.getColumn("south").getInt();
            west = query.getColumn("west").getInt();
            ofLog() << selectedYear << " " << total << " "
                    << north << " " << east << " " << south << " " << west
                    << endl;
        }

        query.reset();
    }

}

void ofApp::draw() {
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetCircleResolution(100);
	
	ofSetColor(ofColor::black);
	ofDrawLine(0, -200, 0, 200);
	ofSetColor(ofColor::red);
	ofDrawLine(-200, 0, 200, 0);

	//ofSetColor(ofColor::black);
	myfont.drawString("W", -440, 40);
	ofSetColor(ofColor::red);
    ofDrawCircle(-200, 0, west * 1.0f / total * 200);
	ofSetColor(ofColor::white);
	myfont2.drawString(ofToString(west), -200 - (myfont2.stringWidth(ofToString(west)) / 2) , 0 + (myfont2.stringHeight(ofToString(west)) / 2));

	//ofSetColor(ofColor::black);
	myfont.drawString("E", 360, 40);
	ofSetColor(ofColor::red);
    ofDrawCircle(200, 0, east * 1.0f / total * 200);
	ofSetColor(ofColor::white);
	myfont2.drawString(ofToString(east), 200 - (myfont2.stringWidth(ofToString(east)) / 2), 0 + (myfont2.stringHeight(ofToString(east)) / 2));

	//ofSetColor(ofColor::black);
	myfont.drawString("N", -40, -280);
	ofSetColor(ofColor::black);
    ofDrawCircle(0 , -200, north * 1.0f / total * 200);
	ofSetColor(ofColor::white);
	myfont2.drawString(ofToString(north), 0 - (myfont2.stringWidth(ofToString(north)) / 2), -200 - (myfont2.stringHeight(ofToString(north)) / 2));

	//ofSetColor(ofColor::black);
	myfont.drawString("S", -40, 360);
	ofSetColor(ofColor::black);
    ofDrawCircle(0 , 200, south * 1.0f / total * 200);
	ofSetColor(ofColor::white);
	ofDrawBitmapString(south, -16, 196);
}

void ofApp::keyPressed(int key) {

}

void ofApp::keyReleased(int key) {

}

void ofApp::mouseMoved(int x, int y) {

}