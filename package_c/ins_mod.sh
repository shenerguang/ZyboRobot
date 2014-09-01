#! /bin/sh -

insmod optical.ko
insmod pwmdriver.ko
insmod ultrasonic.ko
val=`cat /proc/devices | grep optical | awk '{print $1}'`
mknod /dev/opt_mod c $val 0
val=`cat /proc/devices | grep pwm | awk '{print $1}'`
mknod /dev/pwm_mod c $val 0
val=`cat /proc/devices | grep ultrasonic | awk '{print $1}'`
mknod /dev/ult_mod c $val 0
echo insmod ok
