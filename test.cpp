//this is all pseudocode
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <raspicam/raspicam_cv.h>
#include <array>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

bool done_side = false;
const char* path = "/dev/ttyUSB0"; //idek work it out yourself
int serial;
char buffer;
string input;
int i,j,k;
array<char,128> pipe_buffer;
string result;
const int ts = 140;
const int m = 45;
const int w = 1280;
const int h = 720;
Mat img;
char net[55] = {0};

bool confirm(int s, string c)
{
    input = "";

    while (!serialDataAvail(s))
    {
        delay(1);
    }

    while (serialDataAvail(s))
    {
        buffer=serialGetchar(s);
        input+=buffer;
    }

    return (input==c);
}

string readFile(fstream strm)
{
    string buffer;
    stringstream result;
    if (strm.is_open())
    {
        while (strm)
        {
            getline(strm, buffer);
            result<<buffer;
            buffer="";
        }
        return result.str();
    }
    else
    {
        return "";
    }
}

char cchar(Scalar scalar) {
    int tred(scalar[2]);
    int tgreen(scalar[1]);
    int tblue(scalar[0]);
    if (max(max(abs(tred-tgreen), abs(tgreen-tblue)), abs(tblue-tred))<20){
        return 'W';
    }
    else if (tred/tgreen<2 and tred>tgreen){
        return 'Y';
    }
    else if (tred/tgreen>4 and tred/tblue<4){
        return 'O';
    }
    else if (min(tred-tgreen, tred-tblue)>50 and min(tred/tgreen, tred/tblue)>2){
        return 'R';
    }
    else if (min(tgreen-tred, tgreen-tblue)>20){
        return 'G';
    }
    else if (min(tblue-tgreen, tblue-tred)>20){
        return 'B';
    }
    else {
        return 'U';
    }
}

vector<string> split(string input, string delimiter)
{
    vector<string> result;
    size_t pos = 0;
    while ((pos = input.find(delimiter))!=string::npos)
    {
        result.push_back(input.substr(0, pos));
        input.erase(0, pos+delimiter.length());
    }
    result.push_back(input);
    return result;
}

string replace (string input, string from, string to)
{
    cout<<"replace \n";
    size_t start;
    start = 0;
    while ((start = input.find(from, start))!=string::npos)
    {
        input.replace(start, from.length(), to);
        start+=to.length();
    }
    return input;
}

int main()
{
    raspicam::RaspiCam_Cv Camera;

    //camera stuff
    cout<<"Opening camera\n";
    if (!Camera.open())
    {
        printf("Error opening camera\n");
        return 1;
    }
    
    //establish serial connection
    if ((serial = serialOpen(path, 28800))<0)
    {
        printf("Cannot open serial\n");
        return 1;
    }

    if (wiringPiSetup()==-1)
    {
        printf("Cannot start pi\n");
        return 1;
    }
    while (true) 
    {
        if (!confirm(serial, "ready")) return 1;

        serialPrintf(serial, "pi_is_ready");
        
        if (!confirm(serial, "scan_cube")) return 1;

        strcpy(net, "");

        for (int i=0; i<6; i++){
            if (!confirm(serial, "scan")) return 1;
            done_side = false;
            while (!done_side)
            {
                Camera.grab();
                Camera.retrieve(img);
                char colours[10];
                colours[9]='\0';
                if (!img.data)
                {
                    cout<<"No data.\n";
                    return 1;
                }
                for (k=-1;k<2;k++)
                {
                    for (j=-1;j<2;j++)
                    {
                        
                        int b[2];
                        //cout<<"Tile ("<<i<<", "<<j<<"):\n";
                        b[0]=(w-ts)/2+(i*(ts+m));
                        b[1]=(h-ts)/2+(j*(ts+m));
                        Rect mask(b[0], b[1], ts, ts);
                        Mat tile = img(mask);
                        Scalar colour = mean(tile);
                        //imwrite("tile"+to_string((i+1)*3+j+1)+".jpg", tile);
                        
                        /*
                        Mat colourTile = img(Rect(0, 0, 10, 10));
                        colourTile.setTo(colour);
                        imwrite("colour"+to_string((i+1)*3+j+1)+".jpg", colourTile);
                        */
                        
                        colours[(i+1)*3+j+1]=cchar(colour);
                        
                        /*
                        cout<<"x: "<<b[0]<<"\n";
                        cout<<"y: "<<b[1]<<"\n";
                        cout<<"x2: "<<b[0]+ts<<"\n";
                        cout<<"y2: "<<b[1]+ts<<"\n";
                        cout<<"\n";
                        */
                    }
                }
                if (colours.find('U')==string::npos) 
                {
                    serialPrintf(serial, "done_side");
                    done_side = true;
                    switch(i){
                        case 0: //bottom
                            strcpy(net[27], colours);
                            break;
                        case 1: //top
                            strcpy(net[0], colours);
                            break;
                        case 2: //left
                            strcpy(net[36], colours);
                            break;
                        case 3: //right
                            strcpy(net[9], colours);
                            break;
                        case 4: //front
                            strcpy(net[18], colours);
                            break;
                        case 5: //back
                            strcpy(net[45], colours);
                            break;
                    }

                }
            }
        }
        //scan_cube done
        cout<<net;
        char nU = net[4];
        char nR = net[13];
        char nF = net[22];
        char nD = net[31];
        char nL = net[40];
        char nB = net[49];
        for (i=0;i<strlen(net);i++)
        {
                if (net[i] == nU) net[i]='U';
                if (net[i] == nR) net[i]='R';
                if (net[i] == nF) net[i]='F';
                if (net[i] == nD) net[i]='D';
                if (net[i] == nL) net[i]='L';
                if (net[i] == nB) net[i]='B';
            }
        }
        shared_ptr<FILE> pipe(popen((string("./kociemba ")+net).c_str(), "r"), pclose);
        if (!pipe) return 1;
        while (!feof(pipe.get()))
        {
            if (fgets(pipe_buffer.data(), 128, pipe.get()) != nullptr){
                result=pipe_buffer.data();
            }
        }
        cout<<result;
        if (result=="Unsolvable cube!") continue;
        result = replace(result, "U2", "U U");
        result = replace(result, "D2", "D D");
        result = replace(result, "L2", "L L");
        result = replace(result, "R2", "R R");
        result = replace(result, "F2", "F F");
        result = replace(result, "B2", "B B");

        cout<<result<<"\n";

        vector<string> moves = split(result, " ");
        char solution[moves.size()+1];
        for (i=0;i<moves.size();i++)
        {
                cout<<moves[i]<<"\n";
                if (moves[i]== "U") solution[i]='A';
                else if (moves[i]== "U'") solution[i]='B';
                else if (moves[i]== "D") solution[i]='C';
                else if (moves[i]== "D'") solution[i]='D';
                else if (moves[i]== "F") solution[i]='E';
                else if (moves[i]== "F'") solution[i]='F';
                else if (moves[i]== "B") solution[i]='G';
                else if (moves[i]== "B'") solution[i]='H';
                else if (moves[i]== "L") solution[i]='I';
                else if (moves[i]== "L'") solution[i]='J';
                else if (moves[i]== "R") solution[i]='K';
                else if (moves[i]== "R'") solution[i]='L';
        }
        solution[moves.size()]='\0';
        serialPrintf(solution);
    }
}