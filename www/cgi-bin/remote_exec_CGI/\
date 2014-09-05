#CROSS_COMPILE=arm-xilinx-linux-gnueabi-
INSTALL_PATH=../
all:
	$(CROSS_COMPILE)gcc -c error.c
	$(CROSS_COMPILE)gcc -c remote_lib.c error.o
	$(CROSS_COMPILE)gcc -o ./post_handler.cgi ./remote_lib.o ./post_handler.c error.o
install: all
	cp -a ./*.cgi $(INSTALL_PATH) 
clean:
	rm ./*.cgi ./*.o
