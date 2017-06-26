#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <vector>

using namespace std;

class image
{
    public:
        image();
        int getWidth();
        int getHeight();
        //const vector<int> & getPix();   // using address to avoid copy vector
        int getPix(int x, int y);
        void getHorizontal();
        void getVertical();
        void calculateEdge();
        int readFile(char* input, char* output);
        int readConfig(ifstream &istr);
        int readP2(ifstream &istr);
        int readP5(ifstream &istr);
        int outputP2(char* outputfile);
        //int outputP5(char* outputfile, const vector<int> & pix1, const vector<int> & pix2, int width, int height);
        //int outputP5(char* outputfile);
        int outputP5(char* outputfile);
    private:
        vector <vector <int> > pix;
        vector <vector <int> > vh;
        vector <vector <int> > vv;
        vector <int> edge;
        int width, height, declaredMax, maxPx, minPx;
};

#endif // IMAGE_H
