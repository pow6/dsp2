#include <stdio.h>
#include <stdlib.h>
/////////////////////////////////////////////////////
// 構造体 BITMAPFILEHEADER
/////////////////////////////////////////////////////
#pragma pack(1)
typedef struct TagBITMAPFILEHEADER{//14byte
	unsigned short bfType;			// ファイルタイプ("BM"：0x4D42が入る)
	unsigned long  bfSize;			// ファイルサイズ
	unsigned short bfReserved1;		// 予約領域（0）
	unsigned short bfReserved2;		// 予約領域（0）
	unsigned long  bfOffBits;		// ファイル先頭からみたデータの位置（byte）
} BITMAPFILEHEADER;
#pragma pack()
/////////////////////////////////////////////////////
// 構造体 BITMAPINFOHEADER
/////////////////////////////////////////////////////
typedef struct{//40byte
	unsigned long biSize;			// BITMAPINFOHEADERのサイズ（40[byte]）
	         long biWidth;			// 幅（ピクセル）
	         long biHeight;			// 高さ（ピクセル）
	unsigned short biPlanes;		// カラープレーン数（1）
	unsigned short biBitCount;		// ビクセル当たりビット数（1,4,8,24,32bit）
	unsigned long biCompression;		// 圧縮（0：なし）
	unsigned long biSizeimage;		// 画像データサイズ（[byte]：0でよい）
	         long biXPixPerMeter;		// 水平解像度：m当たり画素数（ピクセル：0でよい）
	         long biYPixPerMeter;		// 垂直解像度：m当たり画素数（ピクセル：0でよい）
	unsigned long biClrUsed;		// カラーパレット数:色数（0でよい）
	unsigned long biClrImportant;		// 重要なカラーインデックス数（0でよい）
} BITMAPINFOHEADER;
/////////////////////////////////////////////////////
// 構造体 カラーパレット　RGBQuad
/////////////////////////////////////////////////////
typedef struct{//1,4,8のときのみそれぞれ2,16,256組の配列を確保
	unsigned char blue;			// Bule値
	unsigned char green;			// Green値
	unsigned char red;			// Red値
	unsigned char re;			// Reserve値
} RGBQUAD;
/////////////////////////////////////////////////////
// 構造体 データ保存　RGB
/////////////////////////////////////////////////////
typedef struct{
	unsigned char blue;			// Bule値
	unsigned char green;			// Green値
	unsigned char red;			// Red値
} RGB_DATA;

int main()
{
	FILE *read;
	BITMAPFILEHEADER bmp_file;
	BITMAPINFOHEADER bmp_info;
	RGB_DATA *rbg_data;
	read = fopen("samp.bmp","rb");
	if(read==NULL){
		fputs("cannot open a file\n",stderr);
		exit(EXIT_FAILURE);
	}
	//Bitmap File Header部の読み込み
	fread(&bmp_file.bfType, sizeof(bmp_file.bfType),1,read);
	fread(&bmp_file.bfSize, sizeof(bmp_file.bfSize),1,read);
	fread(&bmp_file.bfReserved1, sizeof(bmp_file.bfReserved1),1,read);
	fread(&bmp_file.bfReserved2, sizeof(bmp_file.bfReserved2),1,read);
	fread(&bmp_file.bfOffBits, sizeof(bmp_file.bfOffBits),1,read);
	//Bitmap Info Header部の読み込み
	fread(&bmp_info.biSize, sizeof(bmp_info.biSize),1,read);
	fread(&bmp_info.biWidth, sizeof(bmp_info.biWidth),1,read);	
	fread(&bmp_info.biHeight, sizeof(bmp_info.biHeight),1,read);
	fread(&bmp_info.biPlanes, sizeof(bmp_info.biPlanes),1,read);
	fread(&bmp_info.biBitCount, sizeof(bmp_info.biBitCount),1,read);
	fread(&bmp_info.biCompression, sizeof(bmp_info.biCompression),1,read);
	fread(&bmp_info.biSizeimage, sizeof(bmp_info.biSizeimage),1,read);
	fread(&bmp_info.biXPixPerMeter, sizeof(bmp_info.biXPixPerMeter),1,read);
	fread(&bmp_info.biYPixPerMeter, sizeof(bmp_info.biYPixPerMeter),1,read);
	fread(&bmp_info.biClrUsed, sizeof(bmp_info.biClrUsed),1,read);
	fread(&bmp_info.biClrImportant, sizeof(bmp_info.biClrImportant),1,read);
	//データ部読み込み
/*	rbg_data = (RGB_DATA *)malloc(sizeof(RGB_DATA)*bmp_info.biWidth*bmp_info.biHeight);
	for(int i=0;i<bmp_info.biWidth*bmp_info.biHeight;i++){
		fread(&rbg_data[i],sizeof(RGB_DATA),1,read);
	}
*/	
	printf("【ヘッダ情報】\n");
	printf(" bmp_file.bfType=%x\n",bmp_file.bfType);
	printf(" bmp_file.bfSize=%ld\n",bmp_file.bfSize);
	printf(" bmp_file.bfReserved1=%d\n",bmp_file.bfReserved1);
	printf(" bmp_file.bfReserved2=%d\n",bmp_file.bfReserved2);
	printf(" bmp_file.bfOffBits=%ld\n",bmp_file.bfOffBits);
	printf("\n");
	printf(" bmp_info.biSize=%ld\n",bmp_info.biSize);
	printf(" bmp_info.biWidth=%ld\n",bmp_info.biWidth);
	printf(" bmp_info.biHeight=%ld\n",bmp_info.biHeight);
	printf(" bmp_info.biPlanes=%d\n",bmp_info.biPlanes);
	printf(" bmp_info.biBitCount=%d\n",bmp_info.biBitCount);
	printf(" bmp_info.biCompression=%ld\n",bmp_info.biCompression);
	printf(" bmp_info.biSizeimage=%ld\n",bmp_info.biSizeimage);
	printf(" bmp_info.biXPixPerMeter=%ld\n",bmp_info.biXPixPerMeter);
	printf(" bmp_info.biYPixPerMeter=%ld\n",bmp_info.biYPixPerMeter);
	printf(" bmp_info.biClrUsed=%ld\n",bmp_info.biClrUsed);
	printf(" bmp_info.biClrImportant=%ld\n",bmp_info.biClrImportant);
	
/*
	printf("【読み込んだRGB値の例】\n");
	printf("%5d個目：Blue(%3d) Green(%3d) red(%3d)\n",1,rbg_data[0].blue,rbg_data[0].green,rbg_data[0].red);
	printf("%5d個目：Blue(%3d) Green(%3d) red(%3d)\n",5000,rbg_data[4999].blue,rbg_data[4999].green,rbg_data[4999].red);
	printf("%5d個目：Blue(%3d) Green(%3d) red(%3d)\n",14400,rbg_data[14399].blue,rbg_data[14399].green,rbg_data[14399].red);
*/

}
