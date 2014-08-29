#! /bin/sh -
for i in $(seq 251 255)
do
	if [ ! -d /sys/class/gpio/gpio$i ]; then
		echo $i > /sys/class/gpio/export
	fi
done

while [ 1 -eq 1 ]
do
for i in $(seq 251 255)
do
	echo in > /sys/class/gpio/gpio$i/direction
	val=`cat /sys/class/gpio/gpio$i/value`
	echo "$i is $val"
	sleep 1
done
done
