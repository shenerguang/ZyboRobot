#include "sign.h"
#include "eye.h"
#include <stdio.h>

enum SIGN last_sign=NONE;
enum SIGN cur_sign;
CvRect sign_rect;
int sign_flag=0;
CvMemStorage *mem;
void sign_init()
{   
    last_sign=NONE;
    sign_flag=0;
    mem=cvCreateMemStorage(0);
}
void sign_clean()
{
    cvReleaseMemStorage(&mem);
}
void split_sign()
{
    CvSeq * sc;
	CvSeq * c;
	CvSeq * cmax;
    cvClearMemStorage(mem);
	cvFindContours(sign_vision,mem,&sc,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
    double smax=0;
    double s;
    c=sc;
	while(c!=NULL)
	{
        s=cvContourArea(c,CV_WHOLE_SEQ,0);
        if(s>smax)
        {
            smax=s;
            cmax=c;
        }
        c=c->h_next;
    }
    sign_rect=cvBoundingRect(cmax,0);
    cvSetImageROI(vision,sign_rect);
    reg_vision= cvCreateImage(cvSize(sign_rect.width,sign_rect.height),8,3);
	cvCopyImage(vision,reg_vision);
    cvResetImageROI(vision);
}
void reg_sign()
{
    int counter_num=0;
    IplImage * temp;
	temp= cvCreateImage(cvSize(sign_rect.width,sign_rect.height),8,1);
    cvCvtColor(reg_vision,temp,CV_BGR2GRAY);
    //Gauss smooth
    cvSmooth(temp,temp,CV_GAUSSIAN,3,3,0,0);
    //Canny edge detect
	cvCanny(temp,temp,120,150,3);
    //Threshold
    CvSeq * sc;
	CvSeq * c;
 cvThreshold(temp,temp,0,255,CV_THRESH_BINARY);
    counter_num=cvFindContours(temp,mem,&sc,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
    double rmin=-1;
    double r;
    c=sc;
    CvBox2D minrect;
	while(c!=NULL)
	{

        CvBox2D rect = cvMinAreaRect2(c,mem);
        r=((double)(rect.size.width*rect.size.height))/(sign_rect.width*sign_rect.height);
        if(r>0.1)
        {
            if(r<rmin||rmin<0)
            {
                rmin=r;
                minrect=rect;
            }
        }
        c=c->h_next;
    }
    //printf("counter:%d rate:%f\n",counter_num,rmin);
    //cvShowImage("reg_vision",reg_vision);
    if(rmin<0.2)
    {
       cur_sign=GO_AHEAD; 
        printf("GO_AHEAD!\n");
    }
    else if(rmin<0.5)
    {
       cur_sign=TURN_RIGHT; 
        printf("TURN_RIGHT!\n");
    }
    else if(rmin<0.7)
    {
        cur_sign=STOP;
        printf("STOP!\n");
    }
    else
    {
        cur_sign=NONE;
        printf("NONE!\n");
    }
    
    cvReleaseImage(&reg_vision);
    cvReleaseImage(&temp);
}
