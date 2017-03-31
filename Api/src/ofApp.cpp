#include "ofApp.h"

void ofApp::setup() {
	getData();
	ofSetBackgroundColor(19, 145, 255);
	spaceBetween = ofGetWidth() / sizeof(dateList);

	myfont.load("GOTHIC.TTF", 20);
	celsius.load("GOTHIC.TTF", 15);
}


void ofApp::update() {
	spaceBetween = 2;
	/*item = ofMap(ofGetMouseX(), 0, ofGetWidth() - 100, 0, 34, true);
	ofLog() << item << endl;*/
	//temp = json["list"][item]["main"]["temp"].asFloat();

	//date = json["list"][item]["dt_txt"].asString();

	//icon = json["list"][item]["weather"]["icon"].asString();
	/*fill array with all dates to easily show them.*/
	for (int i = 0; i < 8; i++)
	{
		dateList[i] = json["list"][i]["dt_txt"].asString();
		celcius[i] = json["list"][i]["main"]["temp"].asFloat();
		iconList[i] = json["list"][i]["weather"][0]["icon"].asString();
		
	}
	for (int i = 0; i < 8; i++)
	{
		lijnPunten[i] = ofPoint(75 + 100 * i + +(myfont.stringWidth(ofToString(dateList[i]).substr(10, 6)) / 4), 500 - (16 * celcius[i]));
		spaceBetween++;
	}

	myResponse = ofLoadURL("http://openweathermap.org/img/w/" + iconList[0] + ".png");
	weatherIcon.loadImage(myResponse.data);

}

void ofApp::draw() {
	ofSetColor(ofColor::white);
	weatherIcon.draw(800, 75);
	spaceBetween = 0;
	ofSetCircleResolution(100);
	myfont.drawString("Amsterdam " + ofToString(dateList[0]).substr(0, 10), 75, 100);
	for (int i = 0; i < 8; i++)
	{
		myfont.drawString(ofToString(dateList[i]).substr(10, 6), 75 + 100 * spaceBetween - (myfont.stringWidth(ofToString(dateList[i]).substr(10, 6)) / 2),500);
		celsius.drawString(ofToString(round(celcius[i])) + "°C", 75 + 100 * spaceBetween - (myfont.stringWidth((ofToString(round(celcius[i])))) / 2), 480 - (16 * celcius[i]));
		ofDrawCircle(75 + 100 * spaceBetween + (myfont.stringWidth(ofToString(dateList[i]).substr(10, 6)) / 4), 500 - (16 * celcius[i]), 5);
	
		
		spaceBetween++;
	}
	for (int i = 0; i < 7; i++)
	{
		ofSetLineWidth(3);
		ofSetColor(ofColor::white, 100);
		ofDrawLine(lijnPunten[i], lijnPunten[i + 1]);
	}

	
}

void ofApp::keyPressed(int key) {
    getData();
}

void ofApp::getData() {
    string url = "http://api.openweathermap.org/data/2.5/forecast?q=Amsterdam,nl&appid=37f584c9d170b496e7abe382b2237a5a&units=metric";

    bool success = json.open(url);
    if (success) {
        int elementCount = json["cnt"].asInt();

        //ofLog() << json["cnt"].asInt() << " elementen gekregen" << endl;

		for (int i = 0; i < elementCount; i++) {
			ofLog() << "Datum van element #" << i << " : " << json["list"][i]["weather"][0]["id"] << endl;
        }

    } else {
        ofLog() << "Oops. No data!" << endl;
    }
}