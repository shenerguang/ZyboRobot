#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

using namespace std;
using namespace cv;
char rgb_buffer[640*480*3];
char *buffer;
pid_t ppid;

/*yuv格式转换为rgb格式*/
int convert_yuv_to_rgb_buffer(char *yuv_buffer_pointer,char *rgb_buffer)
{
    unsigned long in, out = 0;
    int y0, u, y1, v;
    int r, g, b;
    for(in = 0; in < 640 * 480 * 2; in += 4)
    {
        y0 = yuv_buffer_pointer[in + 0];
        u  = yuv_buffer_pointer[in + 1];
        y1 = yuv_buffer_pointer[in + 2];
        v  = yuv_buffer_pointer[in + 3];

        r = y0 + (1.370705 * (v-128));
        g = y0 - (0.698001 * (v-128)) - (0.337633 * (u-128));
        b = y0 + (1.732446 * (u-128));

        if(r > 255) r = 255;
        if(g > 255) g = 255;
        if(b > 255) b = 255;
        if(r < 0) r = 0;
        if(g < 0) g = 0;
        if(b < 0) b = 0;
        rgb_buffer[out++] = r;
        rgb_buffer[out++] = g;
        rgb_buffer[out++] = b;

        r = y1 + (1.370705 * (v-128));
        g = y1 - (0.698001 * (v-128)) - (0.337633 * (u-128));
        b = y1 + (1.732446 * (u-128));

        if(r > 255) r = 255;
        if(g > 255) g = 255;
        if(b > 255) b = 255;
        if(r < 0) r = 0;
        if(g < 0) g = 0;
        if(b < 0) b = 0;
        rgb_buffer[out++] = r;
        rgb_buffer[out++] = g;
        rgb_buffer[out++] = b;
    }
    return 0;
}

/*rgb格式转换为yuv格式*/
int convert_rgb_to_yuv_buffer(char *yuv_buffer_pointer,unsigned char *rgb_buffer)
{
    unsigned long in=0, out = 0;
    int y0, u, y1, v;
    int r, g, b;
    for(out = 0; out < 640 * 480 * 2; out += 4)
    {  
    	/*   		
		Y =   0.257R + 0.504G + 0.098B + 16
		U = -0.148R - 0.291G + 0.439B + 128
		V  =  0.439R - 0.368G - 0.071B + 128		
    	*/
    	r = rgb_buffer[in++];
        g = rgb_buffer[in++];
        b = rgb_buffer[in++];

		y0 = 0.257*r + 0.504*g + 0.098*b + 16;
		u  = -0.148*r - 0.291*g + 0.439*b + 128;
		v  = 0.439*r - 0.368*g - 0.071*b + 128;

        if(y0 > 255) y0 = 255;
        if(u > 255) u = 255;
        if(v > 255) v = 255;
        if(y0 < 0) y0 = 0;
        if(u < 0) u = 0;
        if(v < 0) v = 0;
        
		r = rgb_buffer[in++];
		g = rgb_buffer[in++];
		b = rgb_buffer[in++];
		
		y1 = 0.257*r + 0.504*g + 0.098*b + 16;
		if(y1 > 255) y1 = 255;
		if(y1 < 0) y1 = 0;        
        		
		yuv_buffer_pointer[out + 0]= y0;
        yuv_buffer_pointer[out + 1]= u;
        yuv_buffer_pointer[out + 2]= y1;
        yuv_buffer_pointer[out + 3]= v ;
    }
    return 0;
}

/**Global variables*/
String face_cascade_name = "haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;

void facedetection(char * buf)
{
	convert_yuv_to_rgb_buffer(buf,rgb_buffer);
	Mat Qframe(480,640,CV_8UC3,rgb_buffer);
    	Mat frame_gray;

	std::vector<Rect> faces;
	cvtColor(Qframe, frame_gray, CV_RGB2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	face_cascade.detectMultiScale( frame_gray, faces, 2.4, 2, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50) );
	
	//printf("size :%d\n",faces.size());
	//-- Draw faces areas
	//printf("facenum:%d\n",faces.size());
	for(unsigned int i = 0; i < faces.size(); i++ )
	{
     	Point center( (faces[i].x + faces[i].width*0.5), (faces[i].y + faces[i].height*0.5));
    	ellipse(Qframe, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 0, 255, 0 ), 4, 8, 0);
	}
	//ellipse(Qframe, Point(320,240), Size( 100, 100), 0, 0, 360, Scalar( 0, 255, 0 ), 4, 8, 0);
	convert_rgb_to_yuv_buffer(buf,Qframe.data);            	
	//-- Release
	frame_gray.release();
    Qframe.release();
}

void detection(int sign_no)
{
	//printf("song1\n");
	facedetection(buffer);	
	//kill(ppid,SIGUSR2);
	//printf("song2\n");
}

int main()
{
	key_t key;
	int shmid;

	if( !face_cascade.load( face_cascade_name ) ){
            printf("load wrong!\n");
	    exit(1);
        }
	//sleep(1);
	key=ftok("/tmp/a",'a');
	shmid=shmget(key,640*480*3,IPC_CREAT|0666);
	if(shmid<0)
		{
			printf("get share memory wrong!\n");
			exit(0);
		}
	buffer =(char *)shmat(shmid,0,0);
		if(buffer==NULL)
		{
			printf("map share memory wrong!\n");
			exit(0);
		}
	ppid = getppid();
	//printf("ppid:%d\n",ppid);
	signal(SIGUSR1,detection);
	while(1)
	{
	  pause();
	}
	return 0;
}

