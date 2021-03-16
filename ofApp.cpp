/************************************************************
************************************************************/
#include "ofApp.h"

/* for dir search */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <dirent.h>
#include <string>

// using namespace std;

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(){
}

/******************************
******************************/
ofApp::~ofApp(){
	printf("destructor:Enter\n");
	fflush(stdout);
	
	for(int i = 0; i < Sounds.size(); i++){
		Sounds[i]->unload();
		delete Sounds[i];
	}
	
	for(int i = 0; i < SoundFileNames.size(); i++){
		delete SoundFileNames[i];
	}
	
	printf("destructor:Exit\n");
	fflush(stdout);
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("test_sound");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(300, 300);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	makeup_music_table();
	load_music_table();
}

/******************************
******************************/
void ofApp::makeup_music_table()
{
	/********************
	********************/
	const string dirname = "../../../data/sound/";
	
	DIR *pDir;
	struct dirent *pEnt;
	struct stat wStat;
	string wPathName;

	pDir = opendir( dirname.c_str() );
	if ( NULL == pDir ) { ERROR_MSG(); std::exit(1); }
	
	pEnt = readdir( pDir );
	while ( pEnt ) {
		// .と..は処理しない
		if ( strcmp( pEnt->d_name, "." ) && strcmp( pEnt->d_name, ".." ) ) {
		
			// wPathName = dirname + "/" + pEnt->d_name;
			wPathName = dirname + pEnt->d_name;
			
			// ファイルの情報を取得
			if ( stat( wPathName.c_str(), &wStat ) ) {
				printf( "Failed to get stat %s \n", wPathName.c_str() );
				break;
			}
			
			if ( S_ISDIR( wStat.st_mode ) ) {
				// nothing.
			} else {
			
				vector<string> str = ofSplitString(pEnt->d_name, ".");
				if(str[str.size()-1] == "mp3"){
					// string str_NewFileName = wPathName;
					// string str_NewFileName = pEnt->d_name;
					string* str_NewFileName = new string(pEnt->d_name);
					
					SoundFileNames.push_back(str_NewFileName);
				}
			}
		}
		
		pEnt = readdir( pDir ); // 次のファイルを検索する
	}

	closedir( pDir );
	
	/********************
	********************/
	if(SoundFileNames.size() == 0){
		ERROR_MSG();
		std::exit(1);
	}
 }

/******************************
******************************/
void ofApp::load_music_table()
{
	/********************
	********************/
	if(SoundFileNames.size() <= 0)	return;

	/********************
	********************/
	const string dirname = "../../../data/sound/";
	
	printf("> load Sound Files\n");
	
	Sounds.resize(SoundFileNames.size());
	for(int i = 0; i < Sounds.size(); i++){
		Sounds[i] = new ofSoundPlayer;
		
		Sounds[i]->loadSound(dirname + SoundFileNames[i]->c_str());
		printf("%3d:%s(isLoaded = %d)\n", i, SoundFileNames[i]->c_str(), Sounds[i]->isLoaded());
		fflush(stdout);
		
		Sounds[i]->setLoop(false);
		Sounds[i]->setMultiPlay(true);
		Sounds[i]->setVolume(1.0);
	}
	printf("--------------------\n");
	fflush(stdout);
}

/******************************
******************************/
void ofApp::update(){

}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(50);
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			if(Sounds.size() <= id) id = 0;
			
			printf("[%d] : %s\n", id, SoundFileNames[id]->c_str());
			fflush(stdout);
			Sounds[id]->play();
			
			id++;
			if(Sounds.size() <= id) id = 0;
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
