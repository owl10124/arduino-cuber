// this is all pseudocode
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <sstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include "search.h"

using namespace std;
using namespace cv;

bool done_side = false;
const char *path = "/dev/ttyUSB0"; // arduino serial port
int serial;
char buffer;
string input;

int i, j, k, l;

unsigned int m;

array<char, 128> pipe_buffer;
string result;

const int ts = 140; //tile size
const int ma = 45;  //margin
const int w = 1280; //width
const int h = 720;  //height

Mat img;

char net[55] = {0};
char *netp = &net[0];

const int white[2] = {0, 80};   //white colour definition
const int yellow[2] = {25, 45}; //yellow colour definition
const int orange[2] = {3, 25};  //orange colour definition
const int red[2] = {3, 170};    //red colour definition
const int green[2] = {45, 75};  //green colour definition
const int blue[2] = {75, 125};  //blue colour definition

//function to read serial data
bool confirm(int s, string c) {
    input = "";

    while (!serialDataAvail(s)) {
        delay(1);
    }

    while (serialDataAvail(s)) {
        buffer = serialGetchar(s);
        input += buffer;
    }

    return (input == c);
}

//function to read file contents. returns as string of file contents
string readFile(fstream strm) {
    string buffer;
    stringstream result;
    if (strm.is_open()) {
        while (strm) {
            getline(strm, buffer);
            result << buffer;
            buffer = "";
        }
        return result.str();
    } else {
        return "";
    }
}


//identify colour of pixels
char cchar(Vec3i vec) {
    int ch(vec[0]);
    int cl(vec[1]);
    int cs(vec[2]);
    if (cs <= white[1]) {
        return 'W';
    } else if (ch >= yellow[0] && ch <= yellow[1]) {
        return 'Y';
    } else if (ch >= orange[0] && ch <= orange[1]) {
        return 'O';
    } else if (ch <= red[0] || ch >= red[1]) {
        return 'R';
    } else if (ch >= green[0] && ch <= green[1]) {
        return 'G';
    } else if (ch >= blue[0] && ch <= blue[1]) {
        return 'B';
    } else {
        return 'U';
    }
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
    if (!Camera.open()) {
        cout << "Error opening camera\n";
        return 1;
    }

    // establish serial connection
    if ((serial = serialOpen(path, 28800)) < 0) {
        cout << "Cannot open serial\n";
        return 1;
    }

    if (wiringPiSetup() == -1) {
        cout << "Cannot start pi\n";
        return 1;
    }
    while (true) {
        if (!confirm(serial, "ready"))  //handshake with arduino
            return 1;

        serialPrintf(serial, "pi_is_ready");    //confirm

        if (!confirm(serial, "scan_cube"))  //receive scancude go ahead from arduino
            return 1;

        strcpy(net, "");

        for (int m = 0; m < 6; m++) {
            if (!confirm(serial, "scan"))
                return 1;
            done_side = false;
            while (!done_side) {
                Camera.grab();  //take picture
                Camera.retrieve(img);   //get image
                char colours[10];
                colours[9] = '\0';
                if (!img.data) {
                    cout << "No data.\n";
                    return 1;
                }
                for (i = -1; i < 2; i++) {
                    for (j = -1; j < 2; j++) {
                        int b[2];
                        cout << "Tile (" << i << ", " << j << "):\n";
                        b[0] = (w - ts) / 2 + (i * (ts + ma));
                        b[1] = (h - ts) / 2 + (j * (ts + ma));
                        Rect mask(b[0], b[1], ts, ts);
                        Mat tile = img(mask);
                        imwrite("tile" + to_string((i + 1) * 3 + j + 1) + ".jpg", tile);

                        cvtColor(tile, tile, CV_BGR2HLS);
                        char col;
                        map<char, int> colmap;
                        /*Scalar colour = mean(tile);

                        Mat colourTile = img(Rect(0, 0, 10, 10));
                        colourTile.setTo(colour);
                        cvtColor(colourTile, colourTile, CV_HLS2BGR);
                        imwrite("colour"+to_string((i+1)*3+j+1)+".jpg", colourTile);
                        colours[(i+1)*3+j+1]=cchar(colour);*/

                        for (k = 0; k < tile.rows; k++) {
                            for (l = 0; l < tile.cols; l++) {
                                col = cchar(tile.at<Vec3b>(k, l));
                                if (col != 'U') {
                                    if (colmap.count(col) == 0) {
                                        colmap.insert(pair<char, int>(col, 0));
                                    } else {
                                        colmap[col] += 1;
                                    }
                                }
                            }
                        }

                        char colour;
                        for (auto const &x : colmap) {

                            cout << "hi\n";
                            if (colmap[colour] < x.second) {
                                colour = x.first;
                            }
                        }
                        colours[(i + 1) * 3 + j + 1] = colour;
                        cout << "x: " << b[0] << "\n";
                        cout << "y: " << b[1] << "\n";
                        cout << "x2: " << b[0] + ts << "\n";
                        cout << "y2: " << b[1] + ts << "\n";
                        cout << "\n";
                    }
                }
                if (find(begin(colours), end(colours), 'U') == end(colours)) {
                    serialPrintf(serial, "done_side");
                    done_side = true;
                    switch (m) {
                        case 0: // bottom
                            strncpy(&net[27], colours, 9);
                            break;
                        case 1: // top
                            strncpy(&net[0], colours, 9);
                            break;
                        case 2: // left
                            strncpy(&net[36], colours, 9);
                            break;
                        case 3: // right
                            strncpy(&net[9], colours, 9);
                            break;
                        case 4: // front
                            strncpy(&net[18], colours, 9);
                            break;
                        case 5: // back
                            strncpy(&net[45], colours, 9);
                            break;
                    }
                }
            }
        }
        // scan_cube done
        cout << net;
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
        /*shared_ptr<FILE> pipe(popen((string("./kociemba ") + net).c_str(), "r"),
                              pclose);
        if (!pipe)
          return 1;
        while (!feof(pipe.get())) {
          if (fgets(pipe_buffer.data(), 128, pipe.get()) != nullptr) {
            result = pipe_buffer.data();
          }
        }
        cout << result;
        if (result == "Unsolvable cube!") {
          continue;
        }*/
        char facelets[] = net;

        char *result = solution(facelets, 24, 1000, 0, "cache"); //solve cube
        if (result == NULL) {
            printf("Unsolvable cube!");
        }

        result = replace(result, "U2", "U U");
        result = replace(result, "D2", "D D");
        result = replace(result, "L2", "L L");
        result = replace(result, "R2", "R R");
        result = replace(result, "F2", "F F");
        result = replace(result, "B2", "B B");

        cout << result << "\n";

        vector <string> moves = split(result, " ");
        char solution[moves.size() + 1];
        for (m = 0; m < moves.size(); m++) {
            cout << moves[m] << "\n";
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
        }
        solution[moves.size()] = '\0';
        serialPrintf(serial, solution);
    }
}
