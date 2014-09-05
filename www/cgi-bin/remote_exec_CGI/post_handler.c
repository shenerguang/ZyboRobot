#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#define DATAFILE "./user_home/user_code.c"

static void cgiGetenv(char **s, char *var){
        *s = getenv(var);
        if (!(*s)) {
                *s = "";
        }
}
int cgiMain() {
	FILE *fd = fopen(DATAFILE,"w");
	char poststr[2000];
	char cmd_str[200] = "gcc -o ./user_home/a.out ";
	int  ret;
	char * cgiHostAddr;
    	cgiHeaderContentType("text/html");
    	fprintf(cgiOut, "<HTML><HEAD>\n");
    	fprintf(cgiOut, "<TITLE>Code Confirm Page</TITLE></HEAD>\n");
    	fprintf(cgiOut, "<BODY>");
	fprintf(cgiOut, "<h1>Welcom to Code Confirm Page</h1>");
	fprintf(cgiOut, "<P>The Code You Submit Is:</p>");
    	cgiFormString("data", poststr, 241);
    	fprintf(cgiOut, "<pre>%s</pre>",poststr);
    	fprintf(fd,poststr);
 	cgiGetenv(&cgiHostAddr, "HOST_ADDR");	
    	fprintf(cgiOut, "<p>Your Host IP = %s</p>",cgiRemoteAddr);
	printf("<hr/>");
	fprintf(cgiOut, "<form action=\"run_handler.cgi\" method=\"get\">");
        fprintf(cgiOut,"<div>");
        fprintf(cgiOut,"<input type=\"submit\" value=\"Compile and Run\">");
        fprintf(cgiOut,"</div>");
        fprintf(cgiOut,"</form>");

    	fprintf(cgiOut, "</BODY>\n");
    	fprintf(cgiOut, "</HTML>\n");
	close(fd);
    	return 0;
}
