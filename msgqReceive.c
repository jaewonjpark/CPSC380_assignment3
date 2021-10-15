#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
// #include <errno.h> (FROM TEMPLATE)
// #define MAX_LINE        80 /* 80 chars per line, per command */   (FROM TEMPLATE)

//TEMPLATE CODE
// struct msgbuf {
//     long mtype;      
//     char mtext[MAX_LINE];
// };

// int main(int argc, char *argv[])
// {
//     key_t  key;       /* message queue key */      
//     int should_run = 1;
//     int mId;
    
//     key = ftok(argv[1], ‘q’);

//     /* Create/attach message queue using key */     
    
//     while (should_run) {   

//         /** read command from message queue then call thesystem ( )
//         function to execute the system command. Break out of loop if 
//         ‘quit’ or ‘exit’ is read from the queue then exit program **/

//         printf("Enter the text: ")

//         }
//         return 0;
// }

struct my_msg{
    long int msg_type;
    char some_text[BUFSIZ];
};

int main()
{
    int running = 1;
    int msgid;
    struct my_msg some_data;
    long int msg_to_rec = 0;
    msgid = msgget((key_t)12345,0666|IPC_CREAT);

    while(running)
    {
        msgrcv(msgid,(void *)&some_data, BUFSIZ, msg_to_rec, 0);
        printf("Data received: %s\n", some_data.some_text);
        if(strncmp(some_data.some_text, "end", 3) == 0)
        {
            running = 0;
        }
    }
    msgctl(msgid, IPC_RMID, 0);
}

