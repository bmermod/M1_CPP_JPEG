#include <iostream>
#include "include/cCompression.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

void printList(unsigned char **liste, int offset=0){
    for(int8_t i = 0; i<8; i++){
        for(int8_t j = 0; j<8; j++){
            cout << (int) liste[i][j] + offset << " , ";
        }
        cout << endl;
    }
}
void printList(double **liste, int offset=0){
    for(int8_t i = 0; i<8; i++){
        for(int8_t j = 0; j<8; j++){
            cout << liste[i][j] + offset << " , ";
        }
        cout << endl;
    }
}
void printList(int **liste, int offset=0){
    for(int8_t i = 0; i<8; i++){
        for(int8_t j = 0; j<8; j++){
            cout << liste[i][j] + offset << " , ";
        }
        cout << endl;
    }
}
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

    //Création des listes nécessaires
    double** ImageDCT = new double*[tailleBloc];
    for(unsigned i=0;i<tailleBloc;i++){
        ImageDCT[i]=new double[tailleBloc];
    }
    int** ImageQUANT = new int*[tailleBloc];
    for(unsigned i=0;i<tailleBloc;i++){
        ImageQUANT[i]=new int[tailleBloc];
    }
    double** ImageDEQUANT = new double*[tailleBloc];
    for(unsigned i=0;i<tailleBloc;i++){
        ImageDEQUANT[i]=new double[tailleBloc];
    }
    unsigned char** ImageDCTi = new unsigned char*[tailleBloc];
    for(unsigned i=0;i<tailleBloc;i++){
        ImageDCTi[i] = new unsigned char[tailleBloc];
    }

    //Tests
    cout << "Création compression" << endl;
    cCompression a(16,16,Image);

    cout << "Bloc original:" << endl;
    printList(Image);



    cout << "Bloc DCT:" << endl;
    a.Calcul_DCT_Block(Image, ImageDCT);
    printList(ImageDCT);
    /*
    cout << "Bloc iDCT:" << endl;
    a.Calcul_iDCT(ImageDCT, ImageDCTi);
    printList(ImageDCTi);
    */
    cout << "Bloc QUANT:" << endl;
    a.quant_JPEG(ImageDCT,ImageQUANT);
    printList(ImageQUANT);

    cout << "Bloc DEQUANT:" << endl;
    a.dequant_JPEG(ImageQUANT,ImageDEQUANT);
    printList(ImageDEQUANT);

    cout << "Bloc iDCT:" << endl;
    a.Calcul_iDCT(ImageDEQUANT, ImageDCTi);
    printList(ImageDCTi);

    cout << "Block iDCT+128:" << endl;
    printList(ImageDCTi, 128);

    return 0;
}
