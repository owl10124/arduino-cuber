//this is all pseudocode
#include <ctime>
#include <iostream>
#include <fstream>
#include <raspicam/raspicam_cv.h>
using namespace std;

bool ready = false;
bool inserted = false;
bool solving = false;
string path = "/dev/ttyUSB0"; //idek work it out yourself

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

int main()
{
    fstream ardFile;
    raspicam::RaspiCam Camera;

    //camera stuff
    cout<<"Opening camera\n";
    if (!Camera.open())
    {
        cerr<<"Error opening camera\n";
    }
    
    //establish serial connection
    ardFile = fstream::open(path, fstream::in|fstream::out)
    while (true)
    {
        
    }
}
