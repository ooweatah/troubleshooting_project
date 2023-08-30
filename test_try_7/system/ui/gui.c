#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_gui()
{
	char p[10] = "abc";
    FILE* babo;
    char buf[1024];
    char here[15] = "panic soon\n";
	printf("s\n",p);
    char cmd[]="echo c > /proc/sysrq-trigger" ;

    while (1) {
        babo = popen(cmd,"r");
        if(babo == NULL ){
            printf("popen() failed\n");
            continue;
        }
        while(fgets(buf,1024,babo) != NULL){
            printf("%s",buf);
        }
        pclose(babo);

        posix_sleep_ms(5000);
    }

    return 0;



}
