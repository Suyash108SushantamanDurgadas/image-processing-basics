#include <iostream>
#include <cmath>
#include <cstdlib> 

using namespace std;

int imagearr[5][5] = {{2, 3, 4, 5, 4}, {2, 3, 4, 6, 2}, {4, 5, 3, 4, 4}, {5, 3, 2, 2, 3}, {5, 4, 3, 2, 1}};

class AutoContrastStretched {
private:
    int imgsize, imgrow, imgcol;
    int hpixel, lpixel, maxpixel, minpixel;
    int* imgptr;
    float histratio;

public:
    AutoContrastStretched(int size, int row, int col, int* image) {
        imgsize = size;
        imgrow = row;
        imgcol = col;
        imgptr = image;

        // Initialize variables and stretch
        histratiogen(); 
        stretchimg();
    }

    void gethpixel() {
        hpixel = imgptr[0];
        for (int k = 0; k < imgsize; k++) {
            if (hpixel < imgptr[k]) hpixel = imgptr[k];
        }
    }

    void getlpixel() {
        lpixel = imgptr[0];
        for (int k = 0; k < imgsize; k++) {
            if (lpixel > imgptr[k]) lpixel = imgptr[k];
        }
    }

    void histratiogen() {
        this->gethpixel();
        this->getlpixel();
        minpixel = 0;
        
        int count = 0;
        int dummy = hpixel;
        while (dummy != 0) {
            dummy = dummy / 2;
            count++;
        }
        
        maxpixel = pow(2, count) - 1;
        
        
        if (hpixel == lpixel) histratio = 1.0;
        else histratio = (float)(maxpixel - minpixel) / (float)(hpixel - lpixel);
        cout<<"Histogram ratio is: "<<histratio<<endl;
    }

    void stretchimg() {
        float* processptr = (float*)calloc(imgsize, sizeof(float));
        
        float quarterpt = (float) maxpixel/ 4;
        cout<<"Quarter pt is:"<<quarterpt<<endl;
        float s1=(histratio-0.0875)/(1+(histratio*0.0875))*(quarterpt);
        float s2=((histratio+0.0875)/(1-(histratio*0.0875))*2*quarterpt);

        for (int i = 0; i < imgsize; i++) {
            if(imgptr[i]<=quarterpt){
                processptr[i]=(histratio-0.0875)/(1+(histratio*0.0875))*(imgptr[i]-lpixel);
            }else if(imgptr[i]>quarterpt&&imgptr[i]<=3*quarterpt){
                processptr[i]=((histratio-0.0875)/(1+(histratio*0.0875))*(imgptr[i]-quarterpt))+s1;
            }else{
                processptr[i]=((histratio-0.0875)/(1+(histratio*0.0875))*(imgptr[i]-3*quarterpt))+s2;
            }
        }

        cout << "Printing auto contrast stretched image:" << endl;
        for (int i = 0; i < imgrow; i++) {
            for (int j = 0; j < imgcol; j++) {
                cout << processptr[i * imgcol + j] << "  ";
            }
            cout << endl;
        }
        
        free(processptr); // Clean up memory
    }
};

int main() {
    int size = sizeof(imagearr)/sizeof(imagearr[0][0]);
    int row = sizeof(imagearr)/sizeof(imagearr[0]);
    int col = size/row;
    AutoContrastStretched Ops(size, row, col, &imagearr[0][0]);
    return 0;
}
