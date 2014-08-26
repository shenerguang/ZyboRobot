#include "eye.h"
#include "roadctl.h"
#include "sign.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define CAMERA 0
#define WIDTH 640
#define HEIGHT 240
#define ROI1_X 0
#define ROI1_Y 240
#define ROI2_X 640
#define ROI2_Y 480
#define DEPTH 8
CvCapture * capture=NULL;
IplImage * vision=NULL;
IplImage * road_vision=NULL;
IplImage * sign_vision=NULL;
IplImage * reg_vision=NULL;
IplImage * gray_vision=NULL;
IplImage * blank=NULL;
IplImage * querybuf=NULL;
CvMemStorage *mem;
int blink_cnt;
char blink_name[30]="";
char sbuf[64];
char *img_post=".jpg";
char *img_pre="../img/";

void eye_open()
{
	blink_cnt=0;
	mem=cvCreateMemStorage(0);
	capture=cvCreateCameraCapture(CAMERA);
	gray_vision= cvCreateImage(cvSize(WIDTH,HEIGHT),DEPTH,1);
	vision= cvCreateImage(cvSize(WIDTH,HEIGHT),DEPTH,3);
	sign_vision= cvCreateImage(cvSize(WIDTH,HEIGHT),DEPTH,1);
	road_vision= cvCreateImage(cvSize(WIDTH,HEIGHT),DEPTH,1);
	blank= cvCreateImage(cvSize(WIDTH,HEIGHT),DEPTH,1);
}

void eye_close()
{
	cvReleaseImage(&gray_vision);
	cvReleaseImage(&vision);
	cvReleaseImage(&sign_vision);
	cvReleaseImage(&road_vision);
	cvReleaseMemStorage(&mem);
	cvReleaseImage(&blank);
	cvReleaseCapture(&capture);
}

void see()
{
	querybuf=cvQueryFrame(capture);
	cvSetImageROI(querybuf,cvRect(ROI1_X,ROI1_Y,ROI2_X,ROI2_Y));
	cvCopyImage(querybuf,vision);
}
void blink()
{
	strcpy(blink_name,img_pre);
	sprintf(sbuf,"%d",blink_cnt);	
	strcat(blink_name,sbuf);
	strcat(blink_name,img_post);
	cvSaveImage(blink_name,vision,0);
	blink_cnt++;
}
void sharingan()
{
	int lowtherd =120;
	int hightherd=130;
	int small_size=500;
	int contour_num;

	cvCvtColor(vision,gray_vision,CV_BGR2GRAY);
	//Gauss smooth
	cvSmooth( gray_vision,gray_vision,CV_GAUSSIAN,3,3,0,0);
	//Canny edge detect
	cvCanny(gray_vision,gray_vision,lowtherd,hightherd,3);
	//Threshold
	cvThreshold(gray_vision,gray_vision,0,255,CV_THRESH_BINARY);
	//picture used to display
	//find countor
	CvSeq * fc=NULL;
	CvSeq * c;
	cvClearMemStorage(mem);
	contour_num=cvFindContours(gray_vision,mem,&fc,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
	//    printf("find counters:%d\n",contour_num);

	c=fc;
	cvCopyImage(blank,road_vision);
	cvCopyImage(blank,sign_vision);
	sign_flag=0;
	line_num=0;
	corn_num=0;
	while(c!=NULL)
	{
		CvBox2D rect = cvMinAreaRect2(c,mem);
		double width=rect.size.height>rect.size.width?rect.size.height:rect.size.width;
		double height=rect.size.height<=rect.size.width?rect.size.height:rect.size.width;
		if(height*width>small_size)
		{
			double s;
			s=cvContourArea(c,CV_WHOLE_SEQ,0);
			if(s>500)
			{
				sign_flag=1;
				cvDrawContours(sign_vision,c,cvScalar(255,255,255,0), cvScalar(255,255,255,0),0, 1,8,cvPoint(0,0));
			}
			else if(s<=500) 
			{
				if(width>50&&height<15)
				{
					line_box[line_num]=rect;
					line_num++;
				}		
				else
				{
					corn_box[line_num]=rect;
					corn_num++;
				}
				cvDrawContours(road_vision,c,cvScalar(255,255,255,0), cvScalar(255,255,255,0),0, 1,8,cvPoint(0,0));
			}
		}
		c=c->h_next;
	}
}
