//this is all pseudocode
#include <ctime>
#include <fstream>
#include <sstream>
#include <stdio>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <raspicam/raspicam_cv.h>
using namespace std;

bool ready = false;
bool inserted = false;
bool solving = false;
string path = "/dev/ttyUSB0"; //idek work it out yourself
int serial;
char buffer;
string input;

bool confirm(s, c)
{
    input = "";

    while (!serialDataAvail(s))
    {
        delay(1);
    }

    while (serialDataAvail(s))
    {
        buffer=serialGetChar(s);
        input+=buffer;
    }

    return (input===c)
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

void status()
{

}

int main()
{
    raspicam::RaspiCam Camera;

    sFile.seekp(1);

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

    if (!confirm(serial, "ready")) return 1;

    serialPrintf(serial, "pi_is_ready");
    
    if (!confirm(serial, "scan_cube")) return 1;

    for (int i=0; i<6; i++){
        if (!confirm(serial, "scan")) return 1;
        Camera.grab();
        unsigned char *data=new unsigned char[Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
	    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );
        serialPrintf(serial, "done_side");
    }

    return 0;
}
