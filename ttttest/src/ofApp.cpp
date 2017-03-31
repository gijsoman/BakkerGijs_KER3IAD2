#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	myfont.load("GOTHIC.TTF", 50);
	void getData();
}

//--------------------------------------------------------------
void ofApp::update(){

	/*item = ofMap(ofGetMouseX(), 0, ofGetWidth() - 100, 0, 34, true);
	ofLog() << item << endl;*/
	temp = json["list"][item]["main"]["temp"].asFloat();

	date = json["list"][item]["dt_txt"].asString();

	/*fill array with all dates to easily show them.*/
	for (int i = 2; i < 10; i++)
	{
		dateList[i] = json["list"][i]["dt_txt"].asString();
		celcius[i] = json["list"][i]["main"]["temp"].asFloat();
	}
	for (int i = 0; i < 8; i++)
	{
		lijnPunten[i] = ofPoint(75 + 100 * spaceBetween, 400 - (4 * celcius[i]));
	}


}

//--------------------------------------------------------------
void ofApp::draw(){
	myfont.drawString("HALLO DOET IE HET NOU?", 100, 100);
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

	}
	else {
		ofLog() << "Oops. No data!" << endl;
	}
}