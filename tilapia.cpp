#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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

int main()
{
    char colours[10];
    colours[9] = '\0';
    Mat img;
    img=imread("image2.jpg");
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

    cout<<colours<<"\n";
    return 0;
}