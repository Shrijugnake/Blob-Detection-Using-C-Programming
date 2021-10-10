#ifndef	_IMAGE_H_
#define _IMAGE_H_

#include<stdint.h>
#pragma pack(push,1) 


typedef struct _proj_image{


	uint8_t n[18];        
	int32_t width;
	int32_t height;
	int16_t colorPlanes;  
	int16_t bitsPerPixel;
	int32_t compression; 
	int32_t imgSize;  
	int32_t notUsed[16]; 
	
}ProjectImage_t;
#pragma pack(pop)

typedef struct IMAGE{
	int height;
	int width;
	unsigned char *RGB[3];  
							
}Image_t;	





ProjectImage_t* project_readBitmapFile(const char* fileName);  //Read bitmap image
Image_t* readingfile(const char* fileName,ProjectImage_t* image);
int Detect_blob(Image_t* bmp);	
int min(int l1,int l2);		
void project_writeBitmapFile(ProjectImage_t* image,const char* fileName,Image_t* bmp);
int freeImage(ProjectImage_t* image);
#endif          
