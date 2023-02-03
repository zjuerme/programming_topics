#include <stdio.h>
#include <stdlib.h>

#include "bmpread.h"
// only support image in bmp
int myCeil(float x)
{
	if ((int)x == x) return x;
	return (int)x + 1;
}

ImgData *bmpread(char *path)
{
	FILE *fp;
	ImgData *ret = NULL;
	int i,j; 
	if (NULL == (fp = fopen(path, "rb")))
	{
		return ret;
	}
	
	// 两个imgread.h里的结构体BMPHeader, BMPHeaderInfo
	// BMPHeader占14字节，BMPHeaderInfo占40个字节，这个是BMP图像的图像格式
	BMPHeaderInfo bmpHeaderInfo;
	BMPHeader bmpHeader;
	char isImgReversed = 1;

	// BMP图像的前14个字节是文件头
	// Reading bmp header
	// 首先读取前14个字节
	fread((char *)&bmpHeader, sizeof(bmpHeader), 1, fp);
	// 判断是否为BMP图像，如果不是就直接退出
	// 刚刚读到了jpg图像，所以直接退出了
	if (0x4D42 != bmpHeader.bfType)
	{
		goto exitLabel;
	}
	// Done.

	// Reading bmp header info
	// 开始读取文件信息的那个40个字节
	fread((char *)&bmpHeaderInfo, sizeof(bmpHeaderInfo), 1, fp);
	
	// 开始给那个ImgData分配内存空间
	ret = (ImgData *)malloc(sizeof(ImgData));

	// 如果文件信息中的高度是负的，就表示图像是正着放的
	// 也就是说，第一行读到的内容，就是bmp图像中的第一行
	// 与之对应的，如果高度是正的，图像就是倒着放的
	// 大部分都是倒着放的
	if (bmpHeaderInfo.biHeight < 0)
	{
		isImgReversed = 0;
		ret->height = -bmpHeaderInfo.biHeight;
	}
	else
	{
		isImgReversed = 1;
		ret->height = bmpHeaderInfo.biHeight;
	}
	ret->width = bmpHeaderInfo.biWidth;
	//Done.

	// bfOffBits表示偏移字节数，即从文件头到主体内容相距多少字节
	printf("%d\n", bmpHeader.bfOffBits);
	// biBitCount表示每个像素点占的位数，有1位（很少见，所以我没实现）、4位、8位、16位、24位、32位
	// 32位就是加个透明通道，如果图像是32位的，imgdata[0][3]表示第一行第一个元素的alpha值
	printf("%d\n", bmpHeaderInfo.biBitCount);

	// 这里是读取bmp文件的调色板（如果有的话），8位及以下的bmp图像，必有调色板
	BMPPalette *bmpPalette;
	int paletteCount = (bmpHeader.bfOffBits - 54) / 4;
	char isUsingPalette = 0;
	if (bmpHeader.bfOffBits > 54) // It means the file contains the palatte.
	{
		isUsingPalette = 1;  // Set the flag.
		bmpPalette = (BMPPalette *)malloc(sizeof(BMPPalette) * paletteCount);
		fread((char *)bmpPalette, sizeof(BMPPalette), paletteCount, fp);
	}
	
	// Now start reading...
	// First, initializing imgdata variable
	// 首先给imgdata分配内存空间
	ret->imgdata = (unsigned char **)malloc(sizeof(unsigned char *) * bmpHeaderInfo.biHeight);
	// 接下来就是分配imgdata的内存空间，如果是32位的，多一个不透明度通道，所以每个像素点分配4的单位
	if (bmpHeaderInfo.biBitCount == 32)
	{
		ret->imgType = 1;
		for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
		{
			ret->imgdata[i] = (unsigned char *)malloc(sizeof(unsigned char) * bmpHeaderInfo.biWidth * 4);
		}
	}
	else
	{
		ret->imgType = 0;
		for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
		{
			ret->imgdata[i] = (unsigned char *)malloc(sizeof(unsigned char) * bmpHeaderInfo.biWidth * 3);
		}
	}
	// 把读取文件的那个指针指向数据部分
	fseek(fp, bmpHeader.bfOffBits, SEEK_SET);

	// Starting reading the main body.
	// 因为bmp图像的格式规定，每一行储存的字节数一定是4的倍数，不是4的倍数的，要补齐
	// 所以有时候需要跳过一定字节数才能读取下一行
	int skipSize = 4 * myCeil((float)bmpHeaderInfo.biBitCount * bmpHeaderInfo.biWidth / 32) - (bmpHeaderInfo.biBitCount * bmpHeaderInfo.biWidth / 8);
	// 接下来就是分类讨论，如果是32位图像怎么读，如果是24位图像怎么读...
	// 这部分我不写了，重点写一下16位怎么读，这个有点不一样
	if (bmpHeaderInfo.biBitCount == 32)
	{
		if (isImgReversed == 0)
		{
			for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
			{
				fread((unsigned char *)ret->imgdata[i], 4, bmpHeaderInfo.biWidth, fp);
			}
		}
		else
		{
			for (i = bmpHeaderInfo.biHeight - 1; i >= 0; i --)
			{
				fread((unsigned char *)ret->imgdata[i], 4, bmpHeaderInfo.biWidth, fp);
			}
		}
	}
	else if (bmpHeaderInfo.biBitCount == 24)
	{
		if (isImgReversed == 0)
		{
			for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
			{
				fread((unsigned char *)ret->imgdata[i], 3, bmpHeaderInfo.biWidth, fp);
				fseek(fp, skipSize, SEEK_CUR);
			}
		}
		else
		{
			for (i = bmpHeaderInfo.biHeight - 1; i >= 0; i --)
			{
				fread((unsigned char *)ret->imgdata[i], 3, bmpHeaderInfo.biWidth, fp);
				fseek(fp, skipSize, SEEK_CUR);
			}
		}
	}
	else if (bmpHeaderInfo.biBitCount == 16) // Now, it becomes a little more complex
	{
		// 16位的话，每个像素点占2个字节，所以声明一个short tmp
		short tmp; // 2 bits
		char rgb888[3];
		for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
		{
			for (j = 0; j < bmpHeaderInfo.biWidth; j ++)
			{
				fread((char *)&tmp, 2, 1, fp);
				// 如果bmpHeaderInfo.biCompression是3，就表示这个16位图像的储存方式RGB565，这个可以查一下网上的。
				// 如果是0，就表示是RGB555格式储存的
				// 接下来的这部分我是通过位操作来获得r, g, b的值，将其转换为rgb888格式。
				if (bmpHeaderInfo.biCompression == 3) // It means it is RGB565
				{
					rgb888[0] = (tmp >> 11) << 3;
					rgb888[1] = ((tmp >> 5) << 10) >> 8;
					rgb888[2] = (tmp << 11) >> 8;
				}
				else if (bmpHeaderInfo.biCompression == 0) // It means it is RGB555
				{
					rgb888[0] = (tmp >> 10) << 3;
					rgb888[1] = ((tmp << 6) >> 11) << 3;
					rgb888[2] = (tmp << 11) >> 8;
				}
				if (isImgReversed == 0)
				{
					ret->imgdata[i][j * 3] = rgb888[0];
					ret->imgdata[i][j * 3 + 1] = rgb888[1];
					ret->imgdata[i][j * 3 + 2] = rgb888[2];
				}
				else
				{
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 3] = rgb888[0];
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 3 + 1] = rgb888[1];
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 3 + 2] = rgb888[2];
				}
			}
			fseek(fp, skipSize, SEEK_CUR);
		}
	}
	// 小于等于8位的时候，就要考虑调色板了，每个像素都是索引到调色板，关于这个，也可以看看bmp文件格式详解
	else if (bmpHeaderInfo.biBitCount == 8) // Now we should consider the palette.
											// In fact, we haven't considered the palette before.
	{
		unsigned char paletteInd; // 1 bit
		for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
		{
			for (j = 0; j < bmpHeaderInfo.biWidth; j ++)
			{
				fread((unsigned char *)&paletteInd, 1, 1, fp);
				if (isImgReversed == 0)
				{
					ret->imgdata[i][j * 3] = bmpPalette[paletteInd].blue;
					ret->imgdata[i][j * 3 + 1] = bmpPalette[paletteInd].green;
					ret->imgdata[i][j * 3 + 2] = bmpPalette[paletteInd].red;
				}
				else
				{
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 3] = bmpPalette[paletteInd].blue;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 3 + 1] = bmpPalette[paletteInd].green;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 3 + 2] = bmpPalette[paletteInd].red;
				}
			}
			fseek(fp, skipSize, SEEK_CUR);
		}
	}
	// 4位的话，有点复杂，因为一个字节储存两个像素的值，所以要考虑进位之类的东西，比较麻烦
	else if (bmpHeaderInfo.biBitCount == 4)
	{
		int readSize = myCeil((float)bmpHeaderInfo.biWidth / 2);
		unsigned char *paletteInd = (unsigned char *)malloc(sizeof(unsigned char) * readSize); // 1 bit
		for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
		{
			fread((char *)paletteInd, readSize, 1, fp);
			for (j = 0; j < bmpHeaderInfo.biWidth / 2; j ++)
			{
				int pInd1 = paletteInd[j] >> 4;
				int pInd2 = paletteInd[j] % 16;
				if (isImgReversed == 0)
				{
					ret->imgdata[i][j * 6] = bmpPalette[pInd1].blue;
					ret->imgdata[i][j * 6 + 1] = bmpPalette[pInd1].green;
					ret->imgdata[i][j * 6 + 2] = bmpPalette[pInd1].red;
					ret->imgdata[i][j * 6 + 3] = bmpPalette[pInd2].blue;
					ret->imgdata[i][j * 6 + 4] = bmpPalette[pInd2].green;
					ret->imgdata[i][j * 6 + 5] = bmpPalette[pInd2].red;
				}
				else
				{
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 6] = bmpPalette[pInd1].blue;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 6 + 1] = bmpPalette[pInd1].green;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 6 + 2] = bmpPalette[pInd1].red;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 6 + 3] = bmpPalette[pInd2].blue;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 6 + 4] = bmpPalette[pInd2].green;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][j * 6 + 5] = bmpPalette[pInd2].red;
				}
			}
			if (bmpHeaderInfo.biWidth % 2 != 0)
			{
				int pInd = paletteInd[bmpHeaderInfo.biWidth / 2] >> 4;
				if (isImgReversed == 0)
				{
					ret->imgdata[i][bmpHeaderInfo.biWidth * 3] = bmpPalette[pInd].blue;
					ret->imgdata[i][bmpHeaderInfo.biWidth * 3 + 1] = bmpPalette[pInd].green;
					ret->imgdata[i][bmpHeaderInfo.biWidth * 3 + 2] = bmpPalette[pInd].red;
				}
				else
				{
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][bmpHeaderInfo.biWidth * 3] = bmpPalette[pInd].blue;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][bmpHeaderInfo.biWidth * 3 + 1] = bmpPalette[pInd].green;
					ret->imgdata[bmpHeaderInfo.biHeight - i - 1][bmpHeaderInfo.biWidth * 3 + 2] = bmpPalette[pInd].red;
				}
				// 注意，如果width不是2的倍数，就表示读到最后，多读了半个字节，所以fseek的时候要skipSize-1，关于这个，你可以尝试纸上推导一下看看。
				fseek(fp, skipSize - 1, SEEK_CUR);
			}
			else
			{
				fseek(fp, skipSize, SEEK_CUR);
			}
		}
	}
	else if (bmpHeaderInfo.biBitCount == 1) // It is uncommon as well, so I don't want to realize it either.
	{
		// TODO:: Read the image data
	}

exitLabel:
	fclose(fp);
	return ret;
}

/* 
int main()
{
	ImgData *tmp = bmpread("cmu.bmp");
    int i,j; 
	printf("%d %d\n", tmp->width, tmp->height);
	for (i = 0; i < tmp->height; i ++)
	{
		for (j = 0; j < tmp->width; j ++)
		{
			printf("[%d %d %d] ", tmp->imgdata[i][j * 3], tmp->imgdata[i][j * 3 + 1], tmp->imgdata[i][j * 3 + 2]);
		}
		printf("\n");
	}
	

	return 0;
}
*/

