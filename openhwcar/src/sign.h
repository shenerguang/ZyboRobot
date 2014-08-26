#ifndef SIGNREG_HEADER
#define SIGNREG_HEADER
#include <cv.h>
#include <highgui.h>
enum SIGN{STOP,TURN_RIGHT,TURN_LEFT,GO_AHEAD,NONE};
void reg_sign();
void split_sign();
void sign_init();
void sign_clean();
extern enum SIGN cur_sign;
extern enum SIGN last_sign;
extern int sign_flag;
extern CvRect sign_rect;
#endif
