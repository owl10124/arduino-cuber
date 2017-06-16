//this is all pseudocode
#include <ctime>
#include <iostream>
#include <fstream>
#include <stringstream>
#include <raspicam/raspicam_cv.h>
using namespace std;

bool ready = false;
bool inserted = false;
bool solving = false;
string path = "/dev/ttyUSB0"; //idek work it out yourself
string serial;

void long_press()
{
    ready = false;
    inserted = false;
    solving = false;
}

void short_press()
{
    if (!ready)
    {
        ready = true;
        return nil;
    }
    else if (!inserted)
    {
        inserted = true;
        return nil;
    }
}

string readFile(fstream strm)
{
    string buffer;
    sstream result;
    if (strm.is_open())
    {
        while (strm)
        {
            getline(strm, buffer);
            result<<buffer;
            buffer="";
        }
        return result;
    }
    else
    {
        return "";
    }
}

int main()
{
    fstream sFile(path, fstream::in|fstream::out);
    raspicam::RaspiCam Camera;

    sFile.seekp(1);

    //camera stuff
    cout<<"Opening camera\n";
    if (!Camera.open())
    {
        cerr<<"Error opening camera\n";
    }
    
    //establish serial connection
    sFile<<"a";
    sFile.close();
    sFile.open();
    sFile>>serial;
    while ()


    while (true)
    {
        
    }

    return 0;
}
