//2019年 課題2-2-1 5J02 池口恭司
#include <stdio.h>
#include <math.h>
#define PI M_PI

void main(){
    int i,j,k;
    int dataSize = 4;
    double xn[] ={1,2,3,4};
    double XN[dataSize];

    //結果保存用配列の初期化
    for(i=0;i<dataSize;i++){
        XN[i] = 0;
    }

    for(k=0;k<dataSize;k++){
        for(j=0;j<dataSize;j++){
            if(k==0)XN[k] += xn[j] * 1/sqrt(dataSize);
            else XN[k] += xn[j] * sqrt((double)2/dataSize) * cos( ((2*j+1)*k*PI)/ (2*dataSize));
        }
    }

    for(k=0;k<dataSize;k++){
        printf("X%d :%lf\n",k,XN[k]);
    }

}

