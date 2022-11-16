#ifndef CCOMPRESSION_H
#define CCOMPRESSION_H
#include <cmath>
#define _USE_MATH_DEFINES
#include <iostream>
using namespace std;
const unsigned int tailleBloc = 8;
class cCompression
{
    private:
        unsigned int mLargeur;
        unsigned int mHauteur;
        unsigned char **mBuffer;
        unsigned int mQualite;
        const int Quant[tailleBloc][tailleBloc] = {
            {16,11,10,16,24,40,51,61},
            {12,12,14,19,26,58,60,55},
            {14,13,16,24,40,57,69,56},
            {14,17,22,29,51,87,80,62},
            {18,22,37,56,68,109,103,77},
            {24,35,55,64,81,104,113,92},
            {49,64,78,87,103,121,120,101},
            {72,92,955,98,112,100,103,99}
        };

    public:
        //Constructeurs & Destructeurs
        cCompression(int mLargeur, int mHauteur, unsigned char** mBuffer, int mQualite=50){
            this->mLargeur = mLargeur;
            this->mHauteur = mHauteur;
            this->mBuffer = mBuffer;
            //BOUCLES FOR ?
            /*
            for(int8_t i = 0; i<tailleBloc; i++){
                for(int8_t j = 0; j<tailleBloc; j++){
                    this->mBuffer[i][j] = mBuffer[i][j];
                }
            }
            */
            this->mQualite = mQualite;


        };
        ~cCompression(){};

        //Fct DCT
        void Calcul_DCT_Block(unsigned char **Bloc, double **DCT_Img){
            double Cu,Cv,sommexy = 0;
            for(unsigned int u=0; u<tailleBloc; u++){
                u==0 ? Cu=1./sqrt(2) : Cu=1.0;
                for(unsigned int v=0; v<tailleBloc; v++){
                    v==0 ? Cv=1./sqrt(2) : Cv=1.0;
                    sommexy = 0;
                    //Calcul de la somme
                    for(unsigned int x=0; x<tailleBloc; x++){
                        for(unsigned int y=0; y<tailleBloc; y++){
                            double val = cos( ( ((2*x)+1)*M_PI*u )/16 )*cos( ( ((2*y)+1)*M_PI*v )/16 );
                            sommexy+=Bloc[x][y] * val;
                            //cout << "Pour (" << u << ":" << v << "),(" << x << ":" << y << "), Cu=" << Cu << ", Cv=" << Cv << endl;
                            //cout << "Valeur calculee = " << val << endl;
                        }
                    }
                    //cout << "Pour (" << u << ":" << v << "), Cu=" << Cu << ", Cv=" << Cv << ", sommexy=" << sommexy << ", valeur finale=" << (1/.4)*Cu*Cv*sommexy << endl;
                    DCT_Img[u][v] = (1./4)*Cu*Cv*sommexy;

                }
            }
            //cout << "DCT done" << endl;
        };
        void Calcul_iDCT(double **DCT_Img, unsigned char **Bloc){
            double Cu,Cv,sommexy = 0;
            for(unsigned int x=0; x<tailleBloc; x++){
                for(unsigned int y=0; y<tailleBloc; y++){
                    sommexy = 0;
                    for(unsigned int u=0; u<tailleBloc; u++){
                        u==0 ? Cu=1/sqrt(2) : Cu=1.0;
                        for(unsigned int v=0; v<tailleBloc; v++){
                            v==0 ? Cv=1/sqrt(2) : Cv=1.0;
                            double val = cos( ( ((2*x)+1)*M_PI*u )/16 )*cos( ( ((2*y)+1)*M_PI*v )/16 );
                            sommexy+=DCT_Img[u][v] * val * Cu * Cv;
                        }
                    }
                    Bloc[x][y] = (1./4)*sommexy;
                }
            }
            //cout << "iDCT done" << endl;
        };

        //Fct Quantification

        void quant_JPEG(double **img_DCT, int **Img_Quant){
            /*
            Calcul de Qtab, matrice contenant soit des 1 soit des 255
            ou autre val
            λ def selon val this->mQualite
            Puis round(P/Qtab)
            */
            double lambda = 0;
            this->mQualite < 50 ? lambda = 5000./this->mQualite : lambda = 200-2.*this->mQualite;
            for(int i=0; i<tailleBloc;i++){
                for(int j=0; j<tailleBloc;j++){
                    double comparer = floor((Quant[i][j]*lambda+50)/100);
                    if(comparer < 1){
                        Img_Quant[i][j]=round(img_DCT[i][j]);
                    }else if(comparer > 255){
                        Img_Quant[i][j]=round(img_DCT[i][j]/255);
                    }else{
                        Img_Quant[i][j]=round(img_DCT[i][j]/comparer);
                    }
                }
            }
        }

        unsigned char** dequant_JPEG(int** Img_Quant, double **img_DCT){
            double lambda = 0;
            this->mQualite < 50 ? lambda = 5000./this->mQualite : lambda = 200-2.*this->mQualite;
            for(int i=0; i<tailleBloc;i++){
                for(int j=0; j<tailleBloc;j++){
                    double comparer = floor((Quant[i][j]*lambda+50)/100);
                    if(comparer < 1){
                        img_DCT[i][j]=round(Img_Quant[i][j]);
                    }else if(comparer > 255){
                        img_DCT[i][j]=round(Img_Quant[i][j] * 255);
                    }else{
                        img_DCT[i][j]=round(Img_Quant[i][j] * comparer);
                    }
                }
            }

        }

        double EQM(int **Bloc8x8){
            double val = 0.;
            for(int i=0; i<tailleBloc;i++){
                for(int j=0; j<tailleBloc;j++){

                }
            }

            return val;
        }

        double Taux_Compression(int **Bloc8x8){

        }
        //Getters & Setters
        unsigned int getLargeur() { return mLargeur; }
        void setLargeur(unsigned int val) { mLargeur = val; }
        unsigned int getHauteur() { return mHauteur; }
        void setHauteur(unsigned int val) { mHauteur = val; }
        unsigned char** getBuffer() { return mBuffer; }
        void setBuffer(unsigned char** val) { mBuffer = val; }
        unsigned int getQualite() { return mQualite; }
        void setQualite(unsigned int val) { mQualite = val; }
};

#endif // CCOMPRESSION_H
