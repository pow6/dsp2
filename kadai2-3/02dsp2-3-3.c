#include <stdio.h>
#include <math.h>
#define SIZE 3
#define EPSILON 0.0001


void main(void){
    double matrix[SIZE][SIZE]={{2,1,3},{1,2,3},{3,3,20}};
    double oldV[SIZE];
    double nextV[SIZE]= {1,0,0};
    double nextVD[SIZE];
    double diff[SIZE][SIZE];
    double tmp,abs,lamb;
    for(int z=1;z<=3;z++){
        do{
            for(int i=0;i<SIZE;i++){
                tmp = 0;
                oldV[i] = nextV[i];
                for(int j=0;j<SIZE;j++){
                    tmp += matrix[i][j] *nextV[j]; 
                }
                nextVD[i] = tmp;
            }
            abs = 0;
            for(int i=0;i<SIZE;i++){
                abs += nextVD[i]*nextVD[i];
            }
            abs = sqrt(abs);
            for(int i=0;i<SIZE;i++){
                nextV[i] = nextVD[i]/abs;
            }
            abs = 0;
            for(int i=0;i<SIZE;i++){
                abs += (nextV[i] - oldV[i])*(nextV[i] - oldV[i]);
            }
            abs = sqrt(abs);
        }while(abs > EPSILON);
    
        printf("[%d]固有値：",z);
        lamb = 0;
        for(int i=0;i<SIZE;i++){
            lamb += nextVD[i] * oldV[i];
        }
        printf("%lf\n",lamb);
        printf("[%d]固有ベクトル：{",z);
        for(int i=0;i<SIZE-1;i++){
            printf("%lf,",nextV[i]);
        }
        printf("%lf}\n",nextV[SIZE-1]);
        

        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE  ;j++){
                matrix[i][j] = matrix[i][j] - lamb * nextV[i] * nextV[j];
            }
        }
    }
}


