#include <stdio.h>
#include <math.h>
#define DATA_SIZE 4
#define PI M_PI

void main(){
	int i,j,k;
	double xn[DATA_SIZE][DATA_SIZE]={{1,1,1,1},{2,1,2,1},{3,1,3,1},{4,1,4,1}};
	double XN[DATA_SIZE][DATA_SIZE];
	double XN2[DATA_SIZE][DATA_SIZE];
	
	for(i=0;i<DATA_SIZE;i++){
		for(j=0;j<DATA_SIZE;j++){
			XN[i][j] = 0;
		}
	}
	for(i=0;i<DATA_SIZE;i++){
		for(k=0;k<DATA_SIZE;k++){
			for(j=0;j<DATA_SIZE;j++){
				if(k==0)XN[k][i] += xn[j][i] * 1/sqrt(DATA_SIZE);
				else XN[k][i] += xn[j][i] * sqrt((double)2/DATA_SIZE) * cos( ((2*j+1)*k*PI)/ (2*DATA_SIZE));
			}
		}
	}
	for(i=0;i<DATA_SIZE;i++){
		for(k=0;k<DATA_SIZE;k++){
			for(j=0;j<DATA_SIZE;j++){
				if(k==0)XN2[i][k] += XN[i][j] * 1/sqrt(DATA_SIZE);
				else XN2[i][k] += XN[i][j] * sqrt((double)2/DATA_SIZE) * cos( ((2*j+1)*k*PI)/ (2*DATA_SIZE));
			}
		}
	}
	for(k=0;k<DATA_SIZE;k++){
		printf("[ ");
		for(j=0;j<DATA_SIZE;j++){
			printf("%lf ",XN2[k][j]);
		}
		printf("]\n");
	}
}



