//2019年 課題2-1-2 5J02 池口恭司
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI M_PI
struct complex{
    double re;
    double im;
};
void DFT(int N,int k,int a,int beta,struct complex *xn,struct complex *XK,int win);
void intro(void);
double Hwindow(double data,int n,int N);

int main(){
    struct complex *xn;
    struct complex *XK;
    double *datas,*resultData;
    int mode,n,k,N;
    int i,j,z,win;
    int a,beta;
    FILE *fpIn,*fpOut;
    char filenameIn[24],filenameOut[24];
    intro();
    printf("File Name to Read >>");
    scanf("%s",filenameIn);
    fpIn=fopen(filenameIn,"r");
    if(fpIn==NULL){
        printf("cannot open file[%s]",filenameIn);
        exit(1);
    }
    printf("File Name to Write >>");
    scanf("%s",filenameOut);
    fpOut=fopen(filenameOut,"w");
    if(fpOut==NULL){
        printf("cannot open file[%s]",filenameOut);
        exit(1);
    }
    printf("Amount of Data >>");
    scanf("%d",&N);
    N=N*2;  //0を同じ数だけ後程付与するので
    xn=(struct complex*)malloc(sizeof(struct complex)*N);
    XK=(struct complex*)malloc(sizeof(struct complex)*N);
    datas=(double*)malloc(sizeof(double)*N/2);
    resultData=(double*)malloc(sizeof(double)*N/2);
    for(i=0;i<N;i++){
        xn[i].re=0;
        xn[i].im=0;
        XK[i].re=0;
        XK[i].im=0;
        if(i<N/2){
            datas[i]=0;
            resultData[i]=0;
        }
    }
    win=0;
    for(i=0;i<N;i++){
        fscanf(fpIn,"%lf",&xn[i].re);
        if(i<N/2)datas[i]=xn[i].re;
    }
    for(i=0;i<N;i++){
        DFT(N,i,1,1,xn,XK,win);
    }
    for(i=0;i<N;i++){
        xn[i].re=XK[i].re*XK[i].re + XK[i].im*XK[i].im;
        xn[i].im=0;
        XK[i].re=0;
        XK[i].im=0;        
    }
    //IDFT
    for(i=0;i<N;i++){
        DFT(N,i,-1,N,xn,XK,win);
    }
    for(i=0;i<N/2;i++){
        for(j=0;j+i<N/2;j++){
            resultData[i] += datas[i+j]*datas[j];
        }
        resultData[i] = resultData[i]/(N/2);
    }
    printf("DFTを用いた計算    | 通常計算\n");
    for(i=0;i<N/2;i++){
        printf("Rxx(%2d)=% 3.5f   | Rxx(%2d)=% 3.5f\n",i,XK[i].re/(N/2),i,resultData[i]);
        fprintf(fpOut,"%d,%lf,%lf\n",i,XK[i].re/(N/2),resultData[i]);
    }
    fclose(fpIn);
}

void DFT(int N,int k,int a,int beta,struct complex *xn,struct complex *XK,int win)
{
    int n;
    XK[k].re=0;
    XK[k].im=0;
    for(n=0;n<N;n++){
        XK[k].re+=xn[n].re*cos(2*PI*n*k/N)+a*xn[n].im*sin(2*PI*n*k/N);
        XK[k].im+=xn[n].im*cos(2*PI*n*k/N)-a*xn[n].re*sin(2*PI*n*k/N);
        if(win==1){
            XK[k].re=Hwindow(XK[k].re,n,N);
            XK[k].im=Hwindow(XK[k].im,n,N);
        }
    }
    XK[k].re=XK[k].re/beta;
    XK[k].im=XK[k].im/beta;
}

void intro(void)
{
    printf("2019年 課題2-1-3 5J02 池口恭司\n");
    printf("使い方：\n");
    printf("非巡回自己相関を求めたいデータファイル名を入力し，\n");
    printf("実行することで，非巡回自己相関を求める\n");
    printf("**************************\n");
}

double Hwindow(double data,int n,int N)
{
    return (0.54-0.46*cos(2*PI*n/N))*data;
}
