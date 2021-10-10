#include<stdio.h> 
#include<stdlib.h>
#include"bitmap.h"					

ProjectImage_t* project_readBitmapFile(const char* fileName){
	FILE *fpr=fopen(fileName,"rb"); 
	ProjectImage_t *INFORMATION;
	INFORMATION=malloc(sizeof *INFORMATION);

	fread(INFORMATION,sizeof(*INFORMATION),1,fpr);
	fclose(fpr);
return INFORMATION;
}
						
Image_t* readingfile(const char* fileName,ProjectImage_t* image){
	Image_t *img;
	img=malloc(sizeof *img);
	
 	FILE *fp=fopen(fileName,"rb"); 
	
	int height=image->height;
	int width=image->width;
	int bytpp=image->bitsPerPixel;
	

	fread(image,sizeof(*image),1,fp);
	fseek(fp,image->n[10],SEEK_SET);           

	img->height=height;
 	img->width= width;

	int x,y,i,j;
 	int p,q,r;			
 	p=q=r=0;
  	
 	int Size=img->height*img->width;				
	
	int  Array[img->height][img->width][3];				
	for(i=1;i<=3;i++){
		img->RGB[i]=malloc(height*width*sizeof(unsigned char));
		
	}
	
 	int a;
	for(x=0;x<height;x++)

	{for(y=0;y<width;y++){
		int bytes_pp=bytpp/8; 			 
			for(j=0;j<bytes_pp;j++)  
				{	
	  
																	
					if(j==0){
			 		 img->RGB[1][p]=(int)getc(fp);			//Blue
			 		Array[x][y][1]=img->RGB[1][p];			
					
					  p=p+1;
							 } 
					 if(j=1){
		 	 		img->RGB[2][q]=(int)getc(fp);			//Green
			 			Array[x][y][2]=img->RGB[2][q];		
						 
						 
						 q=q+1;
							 }
			 		 if(j=2){
			 	 		img->RGB[3][r]=(int)getc(fp);			//Red
			 	 		Array[x][y][3]=img->RGB[3][r];			
					
						r=r+1;
			 				}  
							} 
			
				}
			
			
	}


  return img;				
}

int Detect_blob(Image_t* bmp){
	int Size=bmp->height*bmp->width;
	int i,j,x,y,bytes_pp,index;
	bytes_pp=3;
	int height=bmp->height;
	int width=bmp->width;
	int p,q,r;
	p=q=r=0;
	
	int  Array[bmp->height][bmp->width][3];				
	int a;
	//Creating 3D matrix.
	for(x=0;x<height;x++){for(y=0;y<width;y++){for(j=0;j<3;j++){ 
		if(j==0){Array[x][y][1]=bmp->RGB[1][p]; p=p+1; }		
	 	if(j=1){Array[x][y][2]=bmp->RGB[2][q];		 q=q+1;	 }
		if(j=2){Array[x][y][3]=bmp->RGB[3][r];r=r+1;			
		} 														
		}			
		}	 	 	
		}
	
	printf("Height of Image:%d\n",bmp->height);
	printf("Width of Image:%d\n",bmp->width);

	
	
	int cc=0;   
	int L[height][width];
	for(x=0;x<height;x++)
	{for(y=0;y<width;y++){
		int index=y+x*width; 			
						
		if(x==0){
			
			if (Array[x][y][1]==255){			
			
			  
										  
			 if(Array[x][y-1][1]!=0){					
			 L[x][y]=L[x][y-1];
										  }								
			else {															 
			cc++;
			L[x][y]=cc;
										  }	
										  }
										  }
		
		
		if(y==0){
			
			if (Array[x][y][1]==255){			
		
			 	if(Array[x][y][1]==Array[x-1][y][1]){				
				L[x][y]=L[x-1][y];
										  }	
			else {															
			cc++;
			L[x][y]=cc;
										  }															  
										  }									
								          }
				
		else if (Array[x][y][1]==255){		
			
			
			
			if(Array[x][y][1]==Array[x-1][y][1] && Array[x][y-1][1]==0){				
			L[x][y]=L[x-1][y];
										  }											
												  
										  
			else if(Array[x-1][y][1]==0 && Array[x][y-1][1]!=0){				
			L[x][y]=L[x][y-1];
										  }								
										  							  
										  
			else if(Array[x-1][y][1]!=0 && Array[x][y-1][1]!=0){					
			L[x][y]=min(L[x-1][y],L[x][y-1]);										
				int a=L[x-1][y];		
				int b=L[x][y-1];			
				int c=L[x][y];			
				int	m=min(L[x-1][y],L[x][y-1]);			 
			for(i=1;i<width;i++){for(j=1;j<height;j++){
								
				if(L[i][j]==a){
					L[i][j]=m;
				}
				
				
				if( L[i][j]==b){
					L[i][j]=m;
				}
				
				if(L[i][j]==c){
					L[i][j]=m;
				}
				
										
			}
			}							 
										 
										 
			}										
										  
			else {														
			cc++;
			L[x][y]=cc;
				 }																  
		         }									

		else{									//*********if black pixel*******.
			L[x][y]=0;		
		}
		
		}}//end of for loop.



int max;
max=0;

int store[height*width];
unsigned int rem[height*width];
int l=0;
int c,d;
unsigned int count=0;
for(x=0;x<height;x++){for(y=0;y<width;y++){
	
	store[l]=L[x][y];  
	l++;
	
	if(max<L[x][y]){
		
		max=L[x][y];			
	}
}}

//printf("Max: %d\n",max); 


  for (c = 0; c <Size; c++)
  {if(store[c]>0){
    for (d = 0; d < count; d++)
    {
	
	if(store[c] == rem[d])
        break;
	
      
    }
    if (d == count)
    {
      rem[count] = store[c];
      count++;
    }}
  }

printf("\nTotal No. of Blobs: %d\n",count);
/*
for (c = 0; c < count; c++){
	printf("Label: %d\n", rem[c]);
}
 */
 	c=0;
    int t=10;

for(x=0;x<height;x++){for(y=0;y<width;y++){



		
			if(L[x][y]==rem[c]){
				Array[x][y][1]=0;		//B
				Array[x][y][2]=0;		//G
				Array[x][y][3]=250;		//R	
						
			}
		
			if(L[x][y]==rem[c+1]&& rem[c+1]!=count&&rem[c+1]!=0){
				Array[x][y][1]=255;		//B
				Array[x][y][2]=0;		//G
				Array[x][y][3]=0;		//R	
					}
		
		
	}}

//Changing RGB values from 3D array Array[x][y]
	p=q=r=0;
	for(x=0;x<height;x++){for(y=0;y<width;y++){for(j=0;j<3;j++){ 
		if(j==0){bmp->RGB[1][p]=Array[x][y][1]; p=p+1; }		
	 	if(j=1){bmp->RGB[2][q]=Array[x][y][2];		 q=q+1;	 }
		if(j=2){bmp->RGB[3][r]=Array[x][y][3];r=r+1;				 			 
			
		} 														
		}			
		}	 	 	
		}



	
}	//end of function




//********************************************************//
//**********min function**********************************//
int min(int l1,int l2){
	
	int small;
    if(l1<l2){
    	small=l1;
	}
        
    else if(l2<l1){
    	small=l2;
	}
     else{
     	small=l1=l2;
	 }   
	return small;
}

//******************************************************//



//**************************************************************************************//
//*************************Write*********************************************************//
void project_writeBitmapFile(ProjectImage_t* image,const char* fileName,Image_t* bmp){

	
	FILE *fp=fopen(fileName,"rb"); 
	fread(image,sizeof(*image),1,fp);
	fseek(fp,image->n[10],SEEK_SET); 
	FILE *fpw=fopen("Output.bmp","wb");
	fwrite(image,sizeof(*image),1,fpw);

	fseek(fpw,image->n[10],SEEK_SET);                          //offset

	int height=bmp->height;
	int width=bmp->width;
	int p,q,r,x,y,j,i;
	p=q=r=0;
	int Size=height*width;

	

	p=q=r=0;		
	int a;
	for(x=0;x<height;x++)

	{for(y=0;y<width;y++){
			 
			for(j=0;j<3;j++)  
				{	
	  
																	
					if(j==0){
						int B=bmp->RGB[1][p];
						
						fputc(B,fpw);
			 	        p=p+1;
			 	              } 
					 if(j=1)  {
					 	int G=bmp->RGB[2][q];
					 
						 fputc(G,fpw);
		 	 		   	 q=q+1;
							 }
			 		 if(j=2) {
			 		 	int R=bmp->RGB[3][r];
			 		 	fputc(R,fpw);
						  r=r+1;
			 				 }  
							 } 
			
				}
		
			
	}


	fclose(fp);
	fclose(fpw);

}


int freeImage(ProjectImage_t* image){
	free(image);
}


