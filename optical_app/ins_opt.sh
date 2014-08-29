#! /bin/sh -

insmod optical.ko
val=`cat /proc/devices | grep optical | awk '{print $1}'`
mknod /dev/opt_mod c $val 0
echo ok
