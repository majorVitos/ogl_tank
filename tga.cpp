



#include <stdio.h>
#include <string.h>



struct tgaStruct
{
	char length;
	char typePalette;
	char typeImage;
	char PaletteFirstL;
	char PaletteFirstH;
	char PaletteLengthL;
	char PaletteLengthH;
	char PaletteCellSize;
	short XAbs;
	short YAbs;
	short Width;
	short Height;
	char bitDepth;
	char bitAttribute;
};//__attribute__(packed);


//write rgb bits of image to a tga file
void TgaWrite(const char * const FileName, const char * const data, const unsigned width, const unsigned height)
{
	FILE *file;
	tgaStruct tga;
	long len = width*height*3;
	
	char *invData;	

	file = fopen(FileName, "wb");
	if( !file )
	{
		return;
	}
	
	invData = new char[len];
	
	for(long i = 0;i < len;i+= 3)
	{
		invData[i] 	= data[i + 2];
		invData[i + 1]	= data[i + 1];
		invData[i + 2]	= data[i];
	}
	
	memset(&tga, 0, sizeof(tgaStruct) );
	
	tga.typeImage = 2;
	tga.Width = width;
	tga.Height = height;
	tga.bitDepth = 24;
	
	//sizeof(tgaStruct) must be 18
	fwrite( &tga, 1, sizeof(tgaStruct), file);
	fwrite( invData, 1, len, file);
	
	delete[] invData;
	
	fclose(file);	
}



unsigned char* TgaRead(const char * const FileName, unsigned &width, unsigned &height)
{
	FILE *file;
	tgaStruct tga;
	unsigned char *data, *tmpData;
	unsigned size, readed;
	

	file = fopen(FileName, "rb");
	if( !file )
	{
		width = 0;
		height = 0;
		return 0;
	}
	
	fread( &tga, 1, sizeof(tgaStruct), file);
	width = tga.Width;
	height = tga.Height;
	size = width * height * 3;
	
	data = new unsigned char[ width * height * 4];
	tmpData = new unsigned char[size];
	readed = fread(tmpData, 1, size, file);
	if(readed != size)
	{
		perror("some error occured\n");
		delete[] tmpData;
		delete[] data;
		return 0;
	}
	for(unsigned i = 0, p = 0;i < size; i+= 3, p += 4)
	{
		data[p + 0] = tmpData[i + 2];
		data[p + 1]	= tmpData[i + 1];
		data[p + 2]	= tmpData[i];
		data[p + 3] = 255;
	}
	

	
	//sizeof(tgaStruct) must be 18
	
	//fwrite( invData, 1, len, file);
	
	delete[] tmpData;
	
	fclose(file);
	return data;
}
