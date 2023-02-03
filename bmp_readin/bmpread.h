#ifndef __IMGREAD_H__
#define __IMGREAD_H__
#pragma pack(1)

typedef struct
{
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
} BMPHeader;

typedef struct
{
	unsigned int biSize;
	unsigned int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
} BMPHeaderInfo;

typedef struct
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char reserved;
} BMPPalette;

typedef struct
{
	int width;
	int height;
	int imgType; // 0: No alpha channel, 1: Alpha channel
	unsigned char **imgdata;
} ImgData;

#endif
