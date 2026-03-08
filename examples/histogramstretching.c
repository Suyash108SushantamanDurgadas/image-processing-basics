#include<stdio.h>
#include<math.h>

//Function Declaration for getting min and max pixels......
int getmaxpixelval(int image[][5], int row, int col);
int getminpixelval(int image[][5], int row, int col);

int main(){
    //Program for Histogram Stretching of pseudoimage.......
    int row=5;
    int col=5;
    int image[5][5]={{1,3,4,5,4},{2,3,4,1,4},{2,3,4,5,5},{1,2,3,2,1},{3,4,5,2,1}};
    int r_max=0;
    int r_min=0;
    
    int s_max=7;
    int s_min=0;
    
    r_max=getmaxpixelval(image,row,col);
    r_min=getminpixelval(image,row,col);
    
    printf("Max pixel val is: %d\n",r_max);
    printf("Min pixel val is: %d\n",r_min);
    
    float mul_factor=(float)(s_max-s_min)/(r_max-r_min);
    
    float str_image[5][5];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            str_image[i][j]=(mul_factor*(image[i][j]-r_min)) + s_min;
        }
    }
    
    printf("Histogram Stretched image is......\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%0.2f\t",str_image[i][j]);
        }
        printf("\n");
    }
    int numstr_image[5][5];
    
    printf("Histogram Stretched with rounded off pixel val image is......\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            numstr_image[i][j]=(int)round(str_image[i][j]);
            printf("%d\t\t",numstr_image[i][j]);
        }
        printf("\n");
    }
}

int getmaxpixelval(int image[][5], int row, int col){
    int max[row];
    for(int i=0;i<row;i++){
        max[i]=image[i][0];
        for(int j=0;j<col;j++){
            if(image[i][j]>max[i]){
                max[i]=image[i][j];
            }
        }
    }
    int maxval=max[0];
    for(int i=0;i<row;i++){
        if(max[i]>maxval){
            maxval=max[i];
        }
    }
    return maxval;
}

int getminpixelval(int image[][5], int row, int col){
    int min[row];
    for(int i=0;i<row;i++){
        min[i]=image[i][0];
        for(int j=0;j<col;j++){
            if(image[i][j]<min[i]){
                min[i]=image[i][j];
            }
        }
    }
    int minval=min[0];
    for(int i=0;i<row;i++){
        if(min[i]<minval){
            minval=min[i];
        }
    }
    return minval;
}
