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
    double *data,*dftData;
    int mode,n,k,N;
    int i,win;
    int a,beta;
    FILE *fpIn;
    char filenameIn[24];
    intro();
    printf("File Name to Read >>");
    //gets(filenameIn);
    scanf("%s",filenameIn);
    fpIn=fopen(filenameIn,"r");
    if(fpIn==NULL){
        printf("cannot open file[%s]",filenameIn);
        exit(1);
    }
    printf("Amount of Data >>");
    scanf("%d",&N);
    xn=(struct complex*)malloc(sizeof(struct complex)*N);
    XK=(struct complex*)malloc(sizeof(struct complex)*N);
    for(i=0;i<N;i++){
        xn[i].re=0;
        xn[i].im=0;
        XK[i].re=0;
        XK[i].im=0;
    }
    win=0;
    for(i=0;i<N;i++){
        //fscanf(fpIn,"%lf,%lf",&xn[i].re,&xn[i].im);
        fscanf(fpIn,"%lf",&xn[i].re);
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
    
    for(i=0;i<N;i++){
        printf("Rxx(%d)=%lf\n",i,XK[i].re/4);
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
    printf("2019年 課題2-1-2 5J02 池口恭司\n");
    printf("使い方：\n");
    printf("非巡回自己相関を求めたいデータと同じ数だけ，データの末尾に0を追加したファイルを用意する\n");
    printf("実行することで，非巡回自己相関を求める\n");
    printf("**************************\n");
}

double Hwindow(double data,int n,int N)
{
    return (0.54-0.46*cos(2*PI*n/N))*data;
}
