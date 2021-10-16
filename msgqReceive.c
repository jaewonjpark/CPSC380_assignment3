#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#define MAX_LINE 80 /* 80 chars per line, per command */

struct msgbuf {
    long mtype;
    char mtext[MAX_LINE];
} message;
  
int main(int argc, char *argv[])
{
    key_t key; /* message queue key */ 
    int mId;
    int should_run = 1;
  
    // ftok generates unique key
    key = ftok(argv[1], 'q');
  
    // creates a message queue and returns identifier
    mId = msgget(key, 0666 | IPC_CREAT);

    while (should_run) {

        // msgrcv receives message
        msgrcv(mId, &message, sizeof(message), 1, 0);
    
        printf("Messages Received : %s \n", message.mtext);

        // exit program if quit or exit inputted
        if(strncmp(message.mtext,"quit",3) == 0 || strncmp(message.mtext,"exit",3) == 0){
            should_run = 0;
        }
    
    }

    // destroy the message queue
    msgctl(mId, IPC_RMID, NULL);
  
    return 0;
}


