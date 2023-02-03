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
	
	// ����imgread.h��Ľṹ��BMPHeader, BMPHeaderInfo
	// BMPHeaderռ14�ֽڣ�BMPHeaderInfoռ40���ֽڣ������BMPͼ���ͼ���ʽ
	BMPHeaderInfo bmpHeaderInfo;
	BMPHeader bmpHeader;
	char isImgReversed = 1;

	// BMPͼ���ǰ14���ֽ����ļ�ͷ
	// Reading bmp header
	// ���ȶ�ȡǰ14���ֽ�
	fread((char *)&bmpHeader, sizeof(bmpHeader), 1, fp);
	// �ж��Ƿ�ΪBMPͼ��������Ǿ�ֱ���˳�
	// �ոն�����jpgͼ������ֱ���˳���
	if (0x4D42 != bmpHeader.bfType)
	{
		goto exitLabel;
	}
	// Done.

	// Reading bmp header info
	// ��ʼ��ȡ�ļ���Ϣ���Ǹ�40���ֽ�
	fread((char *)&bmpHeaderInfo, sizeof(bmpHeaderInfo), 1, fp);
	
	// ��ʼ���Ǹ�ImgData�����ڴ�ռ�
	ret = (ImgData *)malloc(sizeof(ImgData));

	// ����ļ���Ϣ�еĸ߶��Ǹ��ģ��ͱ�ʾͼ�������ŷŵ�
	// Ҳ����˵����һ�ж��������ݣ�����bmpͼ���еĵ�һ��
	// ��֮��Ӧ�ģ�����߶������ģ�ͼ����ǵ��ŷŵ�
	// �󲿷ֶ��ǵ��ŷŵ�
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

	// bfOffBits��ʾƫ���ֽ����������ļ�ͷ�����������������ֽ�
	printf("%d\n", bmpHeader.bfOffBits);
	// biBitCount��ʾÿ�����ص�ռ��λ������1λ�����ټ���������ûʵ�֣���4λ��8λ��16λ��24λ��32λ
	// 32λ���ǼӸ�͸��ͨ�������ͼ����32λ�ģ�imgdata[0][3]��ʾ��һ�е�һ��Ԫ�ص�alphaֵ
	printf("%d\n", bmpHeaderInfo.biBitCount);

	// �����Ƕ�ȡbmp�ļ��ĵ�ɫ�壨����еĻ�����8λ�����µ�bmpͼ�񣬱��е�ɫ��
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
	// ���ȸ�imgdata�����ڴ�ռ�
	ret->imgdata = (unsigned char **)malloc(sizeof(unsigned char *) * bmpHeaderInfo.biHeight);
	// ���������Ƿ���imgdata���ڴ�ռ䣬�����32λ�ģ���һ����͸����ͨ��������ÿ�����ص����4�ĵ�λ
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
	// �Ѷ�ȡ�ļ����Ǹ�ָ��ָ�����ݲ���
	fseek(fp, bmpHeader.bfOffBits, SEEK_SET);

	// Starting reading the main body.
	// ��Ϊbmpͼ��ĸ�ʽ�涨��ÿһ�д�����ֽ���һ����4�ı���������4�ı����ģ�Ҫ����
	// ������ʱ����Ҫ����һ���ֽ������ܶ�ȡ��һ��
	int skipSize = 4 * myCeil((float)bmpHeaderInfo.biBitCount * bmpHeaderInfo.biWidth / 32) - (bmpHeaderInfo.biBitCount * bmpHeaderInfo.biWidth / 8);
	// ���������Ƿ������ۣ������32λͼ����ô���������24λͼ����ô��...
	// �ⲿ���Ҳ�д�ˣ��ص�дһ��16λ��ô��������е㲻һ��
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
		// 16λ�Ļ���ÿ�����ص�ռ2���ֽڣ���������һ��short tmp
		short tmp; // 2 bits
		char rgb888[3];
		for (i = 0; i < bmpHeaderInfo.biHeight; i ++)
		{
			for (j = 0; j < bmpHeaderInfo.biWidth; j ++)
			{
				fread((char *)&tmp, 2, 1, fp);
				// ���bmpHeaderInfo.biCompression��3���ͱ�ʾ���16λͼ��Ĵ��淽ʽRGB565��������Բ�һ�����ϵġ�
				// �����0���ͱ�ʾ��RGB555��ʽ�����
				// ���������ⲿ������ͨ��λ���������r, g, b��ֵ������ת��Ϊrgb888��ʽ��
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
	// С�ڵ���8λ��ʱ�򣬾�Ҫ���ǵ�ɫ���ˣ�ÿ�����ض�����������ɫ�壬���������Ҳ���Կ���bmp�ļ���ʽ���
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
	// 4λ�Ļ����е㸴�ӣ���Ϊһ���ֽڴ����������ص�ֵ������Ҫ���ǽ�λ֮��Ķ������Ƚ��鷳
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
				// ע�⣬���width����2�ı������ͱ�ʾ������󣬶���˰���ֽڣ�����fseek��ʱ��ҪskipSize-1���������������Գ���ֽ���Ƶ�һ�¿�����
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

