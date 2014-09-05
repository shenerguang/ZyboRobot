#CROSS_COMPILE=gcc
INSTALL_PATH=../
all:
	$(CROSS_COMPILE)gcc -c error.c
	$(CROSS_COMPILE)gcc -c remote_lib.c error.o
	$(CROSS_COMPILE)gcc -c cgic.c
	$(CROSS_COMPILE)gcc -o ./post_handler.cgi ./remote_lib.o ./post_handler.c error.o cgic.o
	$(CROSS_COMPILE)gcc -o ./run_handler.cgi ./remote_lib.o ./run_handler.c error.o
install: all
	cp -a ./*.cgi $(INSTALL_PATH) 
clean:
	rm ./*.cgi ./*.o
