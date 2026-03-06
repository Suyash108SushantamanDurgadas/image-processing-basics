#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//Function declaration......
int* hist_generator(int image[][5],int r_max,int r_min,int row,int col); 

int main(){
    int image[5][5]={{1,3,4,5,4},{2,3,4,1,4},{2,3,4,5,5},{1,2,3,2,1},{3,4,5,2,1}};
    int row=5;
    int col=5;
    int totaldatapoints=row*col;
    int r_max=7;
    int r_min=0;
    
    int* hist=hist_generator(image,r_max,r_min,row,col);
    float pdf[r_max - r_min + 1];
    float cdf[r_max - r_min + 1];
    float equalizedval[r_max - r_min + 1];
    int rounded_equalizedval[r_max - r_min + 1];
    int hist1[r_max - r_min + 1];
    printf("Frequency Table is:\n");
    for(int i = r_min; i <= r_max; i++){
        printf("%d\t",hist[i]);
        pdf[i]=(float)hist[i]/(float)totaldatapoints;
    }
    printf("\nPdf Table is:\n");
    for(int i = r_min; i <= r_max; i++){
        printf("%0.2f\t",pdf[i]);
        cdf[i]=pdf[i];
    }
    printf("\nCdf Table is:\n");
    printf("%0.2f\t",cdf[0]);
    for(int i = r_min+1; i <= r_max; i++){
        cdf[i]+=cdf[i-1];
        printf("%0.2f\t",cdf[i]);
    }
    printf("\nGenerating Equalized Values......\n");
    for(int i = r_min; i <= r_max; i++){
        equalizedval[i]=cdf[i]*r_max;
        printf("%0.2f\t",equalizedval[i]);
    }
    printf("\nRounded off Equalized Values......\n");
    for(int i = r_min; i <= r_max; i++){
        rounded_equalizedval[i]=(int)round(equalizedval[i]);
        hist1[i]=0;//Setting the New Histogram Table to zero 
        printf("%d\t",rounded_equalizedval[i]);
    }
    int equalized_image[5][5];
    printf("\nReal Image......\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%4d\t",image[i][j]);
        }printf("\n");
    }
    printf("\nEqualized Image......\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            equalized_image[i][j]=rounded_equalizedval[image[i][j]];
            printf("%4d\t",equalized_image[i][j]);
        }printf("\n");
    }
    printf("\nNew Hist Table is:\n");
    for(int i = r_min; i <= r_max; i++){
        hist1[rounded_equalizedval[i]]+=hist[i];
    }
    //printf("\nPdf Table is:\n");
    for(int i = r_min; i <= r_max; i++){
        printf("%d\t",hist1[i]);
    }
}

int* hist_generator(int image[][5], int r_max, int r_min, int row, int col){

    int size = r_max - r_min + 1;

    int *hist_arr = (int*)calloc(size, sizeof(int));

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            hist_arr[image[i][j]]++;
        }
    }
    return hist_arr;
}
