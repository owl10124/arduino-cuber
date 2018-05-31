// this is all pseudocode
#include <array>
#include <map>
#include <ctime>
#include <cstring>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
  #include "search.h"
}

using namespace std;
using namespace cv;

const char path[] = "/dev/ttyACM0"; // arduino serial port
int serial;
char buffer;

int i, j, k, l;

unsigned int m;

array<char, 128> pipe_buffer;
string result;

const int top = 120;
const int portside = -40; //left
const int ts = 150; //tile size
const int ma = 140;  //margin
const int w = 1600; //width
const int h = 1201;  //height

Mat img;

char net[55] = {0};
char *netp = &net[0];

const int white[2] = {0, 80};   //white colour definition
const int yellow[2] = {10, 30}; //yellow colour definition
const int orange[2] = {0, 100};  //orange colour definition
const int red[2] = {10, 160};    //red colour definition
const int green[2] = {30, 100};  //green colour definition
const int blue[2] = {100, 125};  //blue colour definition

//function to read serial data
bool confirm(int s, string c) {
    string input="";
    while (!serialDataAvail(s)) delay(10);
    buffer=serialGetchar(s);
    while (buffer!='\n')
    {
	input+=buffer;
	cout<<buffer;
	delay(10);
	buffer=serialGetchar(s);
    }
    cout<<(input==c)<<"\n";
    return(input==c);
}

//identify colour of pixels
char cchar(Vec3i vec) {
    int ch(vec[0]);
    int cl(vec[1]);
    int cs(vec[2]);
    if (cs <= white[1]) return 'W';
    if (ch >= yellow[0] && ch <= yellow[1]) return 'Y';
    if (ch <= red[0] || ch >= red[1]) return cl<orange[1] ? 'R' : 'O' ;
    if (ch >= green[0] && ch <= green[1]) return 'G';
    if (ch >= blue[0] && ch <= blue[1]) return 'B';
    return 'U';
}

vector <string> split(string input, string delimiter) {
    vector <string> result;
    size_t pos = 0;
    while ((pos = input.find(delimiter)) != string::npos) {
        result.push_back(input.substr(0, pos));
        input.erase(0, pos + delimiter.length());
    }
    result.push_back(input);
    return result;
}

string replace(string input, string from, string to) {
    cout << "replace \n";
    size_t start;
    start = 0;
    while ((start = input.find(from, start)) != string::npos) {
        input.replace(start, from.length(), to);
        start += to.length();
    }
    return input;
}

int main() {
    raspicam::RaspiCam_Cv Camera;

    // camera stuff
    cout << "Opening camera\n";
    #if 1
	if (!Camera.open()) {
        cout << "Error opening camera\n";
        return 1;
    }
    //more properties
    Camera.set(CV_CAP_PROP_FRAME_WIDTH, 1600);
    Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1201);
    Camera.set(CV_CAP_PROP_SATURATION, 100);
    Camera.set(CV_CAP_PROP_CONTRAST, 20);
    #endif
    // establish serial connection
    if ((serial = serialOpen(path, 115200)) < 0) {
        cout << serial <<" Cannot open serial\n";
        return 1;
    }

    if (wiringPiSetup() == -1) {
        cout << "Cannot start pi\n";
        return 1;
    }
    cout<<"Setup complete.\n";

	if (!confirm(serial, "ready"))  //handshake with arduino
	    return 1;
	    cout<<"reddy\n"; //arduino sent ready
        serialPuts(serial, "pi_is_ready"); //confirm

    while (true) {
        if (!confirm(serial, "init_scan")) //receive scancube go ahead from arduino
            return 1;
        serialPuts(serial,"GO");
        strcpy(net, "");
        for (int m = 0; m < 6; m++) {
            if (!confirm(serial, "scan"))
                return 1;
#if 0
            Camera.grab();  //take picture
            Camera.retrieve(img); //get image
            char colours[10];
            colours[9] = '\0';
            if (!img.data) {
                cout << "No data.\n";
                return 1;
            }
            for (i = -1; i < 2; i++) 
            {
                for (j = -1; j < 2; j++) 
                {
                    int b[2];
                    cout << "Tile (" << i << ", " << j << "):\n";
                    b[0] = (w + portside - ts) / 2 + (j * (ts + ma)); //x coord of tile
                    b[1] = (h + top - ts) / 2 + (i * (ts + ma)); //y coord of tile
                    Rect mask(b[0], b[1], ts, ts);
                    Mat tile = img(mask);
                    imwrite("tile" + to_string((i + 1) * 3 + j + 1) + ".jpg", tile);
                        
                    cvtColor(tile, tile, CV_BGR2HLS); //converts to HLS colour space
                    char col;
                    map<char, int> colmap; //map of how many times each colour appears
                    for (k = 0; k < tile.rows; k++) {
                        for (l = 0; l < tile.cols; l++) {
                            col = cchar(tile.at<Vec3b>(k, l)); //colour of current pixel
                            if (col != 'U') {
                                if (colmap.count(col) == 0) { 
                                    colmap.insert(pair<char, int>(col, 0));
                                } else {
                                    colmap[col] += 1;
                                } //basically frequency table
                            }
                        }
                    }	
                    char colour;
                    for (auto const &x : colmap) {
                        cout << "hi\n";
                        if (colmap[colour] < x.second) colour = x.first;
                    } //get most often occuring colour
                    colours[(i + 1) * 3 + j + 1] = colour;
                }
            }
#endif
            cout<<"Meow!\n"; //prints 'Meow!' to stdout; 1 face scanned
            serialPuts(serial,"done_side");
            delay(500);
        }
        // scan_cube done
        /*cout << net;
        char nU = net[4];
        char nR = net[13];
        char nF = net[22];
        char nD = net[31];
        char nL = net[40];
        char nB = net[49];
        for (m = 0; m < strlen(net); m++) {
            if (net[m] == nU)
                net[m] = 'U';
            if (net[m] == nR)
                net[m] = 'R';
            if (net[m] == nF)
                net[m] = 'F';
            if (net[m] == nD)
                net[m] = 'D';
            if (net[m] == nL)
                net[m] = 'L';
            if (net[m] == nB)
                net[m] = 'B';
        }
        char *facelets = net;
	*/
	char *facelets = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
        string result = (string)solution(facelets, 24, 1000, 0, "cache"); //solve cube
        if (result=="") {
            printf("Unsolvable cube!");
        }

        result = replace(result, "U2", "U U"); =
        result = replace(result, "D2", "D D");
        result = replace(result, "L2", "L L");
        result = replace(result, "R2", "R R");
        result = replace(result, "F2", "F F");
        result = replace(result, "B2", "B B");

        cout << result << "\n";

        vector <string> moves = split(result, " ");
	    moves.pop_back();
        char solution[moves.size() + 1]; //string to be sent to serial; convert
        for (m = 0; m < moves.size(); m++) {
            if (moves[m] == "U")
                solution[m] = 'A';
            else if (moves[m] == "U'")
                solution[m] = 'B';
            else if (moves[m] == "D")
                solution[m] = 'C';
            else if (moves[m] == "D'")
                solution[m] = 'D';
            else if (moves[m] == "F")
                solution[m] = 'E';
            else if (moves[m] == "F'")
                solution[m] = 'F';
            else if (moves[m] == "B")
                solution[m] = 'G';
            else if (moves[m] == "B'")
                solution[m] = 'H';
            else if (moves[m] == "L")
                solution[m] = 'I';
            else if (moves[m] == "L'")
                solution[m] = 'J';
            else if (moves[m] == "R")
                solution[m] = 'K';
            else if (moves[m] == "R'")
                solution[m] = 'L';
	    cout<<(int)solution[m]<<" meow\n"; //meow
        }
        solution[moves.size()] = '\0';
        serialPuts(serial, solution);
    }
}