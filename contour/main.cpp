#include <iostream>
#include "image.h"

using namespace std;

int main(int argc, char* argv[]){

    if (argc != 3){
        //cout << "arg not right!" << endl;
        return -1;
    }

    image im;

    if (im.readFile (argv[1], argv[2])){
        return -1;
    }

    return 0;
}
