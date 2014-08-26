#ifndef ROADCTL_HEADER
#define ROADCTL_HEADER
extern int err;
extern CvBox2D  line_box[8];
extern int line_num;
extern CvBox2D  corn_box[8];
extern int corn_num;
void plane_err();
void adjust_err();
#endif
