#include "image.h"
#include <cmath>
#include <iostream>


using namespace std;
image :: image() {
    width = -1, height = -1, declaredMax = -1;
    maxPx = -1435, minPx = 2566;
}

int image :: getWidth() {
    return width;
}

int image :: getHeight() {
    return height;
}

int image :: getPix(int x, int y) {
    //cout << "(" << x << ", " << y << "): ";
    if (x < 0 || y < 0 || x >= height || y >= width){
        //cout << "0" << endl;
        return 0;
    }
    //cout << pix.at(x).at(y) << endl;
    return pix.at(x).at(y);
}

int image :: readFile(char* input, char* outputfile) {
    //cout << "readFile" << endl;
    ifstream istr(input);
    if (istr.fail()) {
        //cout << "File open failed! at " << input << endl;
        return -1;
    }
    char firstchar = istr.get();
    if (firstchar != 'P') {
        return -1;
    }
    char secondchar = istr.get();
    if (secondchar == '2') {             // Input is ascii format
        if (readConfig (istr) == -1) {
            return -1;
        }
        if (readP2 (istr) == -1) {
                return -1;
        }
    } else if (secondchar == '5') {     // Input is binary format
        if (readConfig (istr) == -1) {
            return -1;
        }
        if (readP5(istr) == -1) {
            return -1;
        }
    } else {                            // Input is neither type
        return -1;
    }

    getHorizontal();
    getVertical();
    calculateEdge();

//    cout <<"max: " << maxPx << " min: " << minPx << endl;

//    cout << "VH size: " << vh.size() << endl;
//    for (unsigned int i = 0; i < height; i++){
//        for (unsigned int j = 0; j < width; j++){
//            cout << vh.at(i).at(j) << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
////
//    cout << "VV size: " << vv.size() << endl;
//    for (unsigned int i = 0; i < height; i++){
//        for (unsigned int j = 0; j < width; j++){
//            cout << vv.at(i).at(j) << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//
//    cout << "PIX size: " << pix.size() << endl;
//    for (unsigned i = 0; i < height; i++){
//        for (unsigned j = 0; j < width; j++){
//            cout << pix.at(i).at(j) << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
    if (secondchar == '2') {
        if (outputP2 (outputfile) == -1) {
            return -1;
        }
    } else if (secondchar == '5') {
        if (outputP5 (outputfile) == -1) {
            return -1;
        }
    }

    return 0;
}


// Horizontal edge
void image :: getHorizontal(){
//    cout << "getHorizontal!!!" << endl;
    vector <int> row;
    for(int x = 0; x < height; x++) {
        //cout << x << endl;
        for (int y = 0; y < width; y++){
            row.push_back(getPix(x+1, y-1) + 2*getPix(x+1, y) + getPix(x+1, y+1) - getPix(x-1, y-1) - 2*getPix(x-1, y) - getPix(x-1, y+1));
//            cout << "horizontal at " <<"[" << x << ", " << y << "] "<< " is " << row.at(y) << endl;
//            cout << "***************************" << endl;
        }

        vh.push_back(row);
        row.clear();
        //cout << endl;
    }
}


// Vertical edge
void image :: getVertical(){
    vector <int> row;
    for(int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++){
            row.push_back(getPix(x-1, y+1) + 2*getPix(x, y+1) + getPix(x+1, y+1) - getPix(x-1, y-1) - 2*getPix(x, y-1) - getPix(x+1, y-1));
            //cout << "vertical at " <<"[" << x << ", " << y << "] "<< " is " << row.at(y) << endl;
            //cout << "***************************" << endl;
        }
        vv.push_back(row);
        row.clear();
    }
}

void image :: calculateEdge(){
    int xi,xj, mx,mj;
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            //double value = (sqrt(vh[x][y]*vh[x][y] + vv[x][y]*vv[x][y])) + 0.5;
            //int rounded = (int) value;

            int rounded = round(sqrt((double)vh[x][y]*vh[x][y] + vv[x][y]*vv[x][y]));

            if (rounded > maxPx) {
                maxPx = rounded;
                xi = x;
                xj = y;
            }
            if (rounded < minPx) {
                minPx = rounded;
                mx = x;
                mj = y;
            }

            pix[x][y] = rounded;
        }
    }
    //cout << "max cord: " << xi << ", " << xj << " min cord: " << mx << ", " << mj << endl;
}

// Read width, height and max pixel
int image :: readConfig(ifstream &istr) {
//    cout << "readConfig" << endl;
    char thirdChar = istr.get();
    if (istr.fail()) {
        //cout << "Third Char Failed" << endl;
        return -1;
    }
    // ****** Skip Comments for P2# ******
    if (thirdChar == '#') {
        //cout << "Is #" << endl;
        string line;
        getline(istr, line);
    }

    // ****** Skip Comments for P2 space or P2 \n ******
    else if (thirdChar != '\n' && thirdChar != ' ') {
        //cout << "thirdChar is neither nor " << thirdChar << endl;
        return -1;
    }

    //int width = -1, height = -1, declaredMax = -1;
    string line;
    int next_int;

    //cout << width << " " << height << " " << declaredMax << endl;

    while (width == -1 || height == -1 || declaredMax == -1) {

        istr >> next_int;
        //cout << next_int << endl;

        if (istr.fail()) {         // Check if # is encountered
            char next_char;
            istr.clear();
            istr >> next_char;
            //cout << "Head " << next_char << " Tail" << endl;

            if (next_char != '#') {      // Skip Comments For P2 space #Comments
                return -1;
            } else {
                getline(istr, line);
                //cout << "Line after encountering #: " << line << endl;
                continue;
            }

            //cout << "Line after Comments: " << line << endl;
        }

        if (width == -1) {
            if (next_int <= 0){
                //cout << "Width 0!" << endl;
                return -1;
            }
            width = next_int;
            continue;
        }

        if (height == -1) {
            if (next_int <= 0) {
                //cout << "Height 0!" << endl;
                return -1;
            }
            height = next_int;
            continue;
        }

        if (declaredMax == -1) {
            if (next_int < 0 || next_int > 256) {
                //cout << "Max Not Right!" << endl;
                return -1;
            }
            declaredMax = next_int;
            if (declaredMax < 0 || declaredMax > 255) {
                //cout << "Declared Max out of Bounds!" << endl;
                return -1;
            }
            break;
        }
    }

    //cout << "W H M: " << width << " " << height << " " << declaredMax << endl;
    return 0;
}



// read pixels for p2
int image :: readP2(ifstream &istr) {
    //cout << "Read P2 " << endl;
    int counter = 0;
    int next_int;
    int y = 0;   // x: height, y: width (counter). y % width == 0: full, x++
    vector <int> row;

    while (!istr.eof()) {
        istr >> next_int;
        if (istr.fail()) {
            if (istr.eof()) {
                break;
            } else {
                //cout << "Pix Error At: " << next_int << endl;
                //cout << "Count: " << counter << endl;
                return -1;
            }
        } else {
            if (next_int < 0 || next_int > declaredMax) {
                return -1;
            }
            //cout << next_int;
            row.push_back(next_int);
            //cout << row.at(y) << " ";
            y ++;
            if (y % width == 0){
                pix.push_back(row);
                row.clear();
                //cout << endl;
                //x += 1;
                y = 0;
            }
            counter ++;
        }
    }

    if (counter != width*height) { return -1; }   // impossible, just make sure.
    //cout << "Counter at readP2: " << counter << " " << width*height << endl;

    if (maxPx == minPx) {
        return -1;
    }
    return 0;
}



int image :: outputP2(char* outputfile){

    ofstream output(outputfile);
    if (output.fail()){
        //cout << "file cannot be overwritten!" << endl;
        return -1;
    }
    output << "P2" << endl;
    output << width << " " << height << " " << endl;
    output << 255 << endl;
    for (unsigned int x = 0; x < height; x++){
        for (unsigned int y = 0; y < width; y++){
            output << (int) (255*(pix.at(x).at(y) - minPx) / (maxPx - minPx) + 0.5) << " ";
        }
        output << endl;
    }

    //cout << "Success!"  << endl;
    int counter = 0;

//    for (unsigned i = 0; i < height; i ++){
//        for (unsigned j= 0; j < width; j++){
//            cout << pix.at(i).at(j) << " ";
//            counter ++;
//        }
//        cout << endl;
//    }
//
//    cout << counter << endl;
    return 0;
}

int image :: readP5(ifstream &istr){

    //cout << "Read P5" << endl;

    const int tot = width * height;
    char bytes[tot + 1];
    istr.read(bytes, tot);
    if (istr.fail()){
        //cout << "istr Failed after read bytes!" << endl;
        return -1;
    }
    bytes[tot] = '\0';
    //cout << "YEA!!!" << endl;
    int y = 0;
    vector <int> row;
    for (int i = 0; i < tot; i++){
        int next_bin = static_cast<int>(static_cast<unsigned char> (bytes[i]));
        //cout << next_bin << " " << endl;
        if (next_bin < 0 || next_bin > declaredMax){
            //cout << "next_bin error: "  << next_bin << " at: " << i << endl;
            return -1;
        }

        row.push_back(next_bin);
        y ++;

        if (y % width == 0){
            y = 0;
            pix.push_back(row);
            row.clear();
        }

    }
    //cout << bytes << endl;

    return 0;
}


int image :: outputP5(char* outputfile){
    //cout << "Output P5" << endl;
    ofstream output(outputfile);
    if (output.fail()){
        return -1;
    }
    char ch;
    output << "P5" << endl;
    output << width << " " << height << " " << endl;
    output << 255 << endl;

    for (unsigned int x = 0; x < height; x++){
        for (unsigned int y = 0; y < width; y++){
            int val = (int)(255*(pix.at(x).at(y) - minPx) / (maxPx - minPx) + 0.5);
            ch = val & 0x000000ff;
            output.write(&ch, 1);
        }
    }

    return 0;
}






