#ifndef SMARTCARMOVE_H
#define SMARTCARMOVE_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <memory.h>
//#include "move.h"

static int fd;

#define MODE (O_WRONLY | O_TRUNC)


static char *gpio_addr[] = {
	"/sys/class/gpio/export",
	"/sys/class/gpio/gpio243/direction/","/sys/class/gpio/gpio243/value/",
	"/sys/class/gpio/gpio244/direction/","/sys/class/gpio/gpio244/value/",
	"/sys/class/gpio/gpio245/direction/","/sys/class/gpio/gpio245/value/",
	"/sys/class/gpio/gpio246/direction/","/sys/class/gpio/gpio246/value/"
};

extern void init_LED();
extern void smart_car_init();
extern void set_car_front(int speed);
extern void set_car_back(int speed);
extern void set_car_right(int speed);
extern void set_car_left(int speed);

#endif
