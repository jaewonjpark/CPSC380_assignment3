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
    int should_run = 1;
    int mId;
  
    // system call ftok()
    // ftok generates unique key
    key = ftok(argv[1], 'q');

    // error handling mId = -1
    if(mId == -1)
    {
        perror("Error printed by perror");
        exit(-1);
    }
  
    // system call msgget()
    // creates a message queue and returns identifier
    mId = msgget(key, 0666 | IPC_CREAT);
    message.mtype = 1;

    while (should_run) {

        printf("msgq>");
        fgets(message.mtext,MAX_LINE,stdin);

        //system call msgsnd()
        // msgsnd sends send message
        msgsnd(mId, &message, sizeof(message), 0);

        // exit program if quit or exit inputted
        if(strncmp(message.mtext,"quit",3) == 0 || strncmp(message.mtext,"exit",3) == 0){
            should_run = 0;
        }
    }

    printf("Message Sent. \n");
  
    return 0;
}