#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>
#define MAX_LINE        80 /* 80 chars per line, per command */

// struct msgbuf {
//     long mtype;      
//     char mtext[MAX_LINE];
//     };
    
// int main(int argc, char *argv[])
// {
//     key_t  key;       /* message queue key */      
//     int should_run = 1;
//     int mId;
    
//     key = ftok(argv[1], ‘q’);
    
//     /* Create/attach message queue using key */      
    
//     while (should_run) {               
//         printf("msgq>");            
//         fflush(stdout);
        
//         /** read command from stdin then send command to message queue      
//         Break out of loop if user types ‘quit’ or ‘exit’ then delete 
//         the message queue and exit   program **/
//     }
//     return 0;
// }


struct my_msg{
    long int msg_type;
    char some_text[MAX_LINE];
};

int main()
{
    int running = 1;
    int msgid;
    struct my_msg some_data;
    char buffer[20];
    msgid = msgget((key_t)12345,0666|IPC_CREAT);
    if(msgid == -1)
    {
        printf("error in creating queue\n");
    }

    while(running)
    {
        printf("Enter some text\n");
        fgets(buffer,20,stdin);
        some_data.msg_type=1;
        strcpy(some_data.some_text, buffer);
        if(msgsend(msgid,(void *) &some_data, MAX_LINE,0) == -1)
        {
            printf("msg not sent\n");
        }
        if(strncmp(buffer,"end",3) == 0)
        {
            running = 0;
        }
    }
}