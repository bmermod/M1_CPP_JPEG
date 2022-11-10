#include <iostream>
#include "include/cCompression.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

int main(){
    unsigned int tailleBloc = 8;
    unsigned char** Image = new unsigned char*[tailleBloc];
    for(unsigned i=0;i<tailleBloc;i++){
        Image[i] = new unsigned char[tailleBloc];
    }
    int data[tailleBloc][tailleBloc] = {
        {11,16,21,25,27,27,27,27},
        {16,23,25,28,31,28,28,28},
        {22,27,32,35,30,28,28,28},
        {31,33,34,32,32,31,31,31},
        {31,32,33,34,34,27,27,27},
        {33,33,33,33,32,29,29,29},
        {34,34,33,35,34,29,29,29},
        {34,34,33,33,35,30,30,30}
    };
    for(int8_t i = 0; i<tailleBloc; i++){
        for(int8_t j = 0; j<tailleBloc; j++){
            Image[i][j] = data[i][j];
        }
    }

    for(int8_t i = 0; i<tailleBloc; i++){
        for(int8_t j = 0; j<tailleBloc; j++){
            cout << (int) Image[i][j] << " , ";
        }
        cout << endl;
    }

    //Tests
    cCompression a(16,16,Image);
    double** ImageDCT = new double*[tailleBloc];
    for(unsigned i=0;i<tailleBloc;i++){
        ImageDCT[i]=new double[tailleBloc];
    }
    a.Calcul_DCT_Block(Image, ImageDCT);
    for(int8_t i = 0; i<tailleBloc; i++){
        for(int8_t j = 0; j<tailleBloc; j++){
            cout << ImageDCT[i][j] << " , ";
        }
        cout << endl;
    }
    a.Calcul_iDCT(ImageDCT, Image);
    for(int8_t i = 0; i<tailleBloc; i++){
        for(int8_t j = 0; j<tailleBloc; j++){
            cout << (int) Image[i][j] << " , ";
        }
        cout << endl;
    }

    return 0;
}
