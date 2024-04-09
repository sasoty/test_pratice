#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>

char read_buff[16];
#define MSQ_NAME "msg_name"


typedef struct C_exercise_1
{
    char name[20];
    int age;
    char phone[20];
    char filename[48];

}user;

  
void *thread1(void *th1_id)
{
    int *id1 = (int *)th1_id;
    char msg[256];

    user User;
    user *user_ptr =&User;

    mqd_t mq;
     mq_open(MSQ_NAME,O_WRONLY);

    printf("input name");
    scanf("%s", user_ptr->name);
    printf("input age");
    scanf("%d", &user_ptr->age);
    printf("input phone number");
    scanf("%s",user_ptr->phone);
    printf("input file");
    scanf("%s",user_ptr->filename);
    
    sprintf(msg,"%s;%d;%s;%s",user_ptr->name,user_ptr->age,user_ptr->phone,user_ptr->filename);
    printf("%s",msg);
    mq_send(mq,msg,256,NULL);

    mq_close(mq);
}

void *thread2(void *th2_id)
{
    mqd_t mq;
    user User;
    user *user_ptr = &User;
    char msg[256];
    mq_open(MSQ_NAME,O_RDONLY);
    mq_receive(mq,msg,256,NULL);
    sscanf(msg,"%s;%d;%s;%s",user_ptr->name,&user_ptr->age,user_ptr->phone,user_ptr->filename);
    
    if(strlen(user_ptr->phone)==10)
    {
        int imagefile = open(user_ptr->filename, O_RDWR);
        if (imagefile<0)
        {
            printf("filename error");
        }
        else
        {
            read(imagefile, read_buff, 16);
            printf("%s",read_buff);
        }
        
    }
    else
    {
        printf("error");
    }
    mq_close(mq);
}

int main()
{
    pthread_t t1_id,t2_id;
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;


    mq_open(MSQ_NAME,O_RDWR|O_CREAT,0666,&attr);

    pthread_create(&t1_id, NULL, &thread1,NULL);  
    pthread_create(&t2_id, NULL, &thread2,NULL);
    pthread_join(t1_id,NULL);
    pthread_join(t2_id,NULL);
    printf("this is main\n");
    
    pthread_exit(NULL);
    return 0;
}
