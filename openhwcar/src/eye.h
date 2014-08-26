#ifndef EYE_HEADER
#define EYE_HEADER
#include <cv.h>
#include <highgui.h>
void eye_open();
void eye_close();
//get image from camera
void see();
//open ,secret weapon of uchiha
void sharingan();
//save what camera see now
void blink();
void testimg(char * img);
extern IplImage * vision;
extern IplImage * reg_vision;
extern IplImage * gray_vision;
extern IplImage * sign_vision;
extern IplImage * road_vision;
#endif
