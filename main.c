#include<stdio.h> 
#include"bitmap.h"					

//int count_bgr[3];
	
int main(){

	const char* fileName;
	fileName="blob.bmp";
//	fileName="blobback.bmp";
	printf("\nSource: %s\n",fileName);
	ProjectImage_t* image=project_readBitmapFile(fileName);     
	Image_t* bmp=readingfile(fileName,image);      			

	
	Detect_blob(bmp);
	project_writeBitmapFile(image,fileName,bmp);			//write fun 
	freeImage(image);
	return 0;

	
}





