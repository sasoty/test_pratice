#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>

#define MSQ_NAME "/msg_name"

typedef struct User {
    char name[20];
    int age;
    char phone[20];
    char filename[48];
} User;

void *thread1(void *arg) {
    mqd_t mq = *((mqd_t *)arg);
    struct mq_attr attr;
    mq_getattr(mq, &attr);

    User user;

    while (1) {
        printf("Enter name: ");
        scanf("%s", user.name);
        printf("Enter age: ");
        scanf("%d", &user.age);
        printf("Enter phone number: ");
        scanf("%s", user.phone);
        printf("Enter filename: ");
        scanf("%s", user.filename);

        mq_send(mq, (char *)&user, sizeof(User), 0);
    }

    pthread_exit(NULL);
}

void *thread2(void *arg) {
    mqd_t mq = *((mqd_t *)arg);
    struct mq_attr attr;
    mq_getattr(mq, &attr);

    User user;
    char buffer[16];

    while (1) {
        mq_receive(mq, (char *)&user, sizeof(User), NULL);

        // Check if phone number is valid
        if (strlen(user.phone) == 10 && strncmp(user.phone, "555", 3) == 0) {
            printf("Valid phone number: %s\n", user.phone);

            // Open the image file
            int imagefile = open(user.filename, O_RDONLY);
            if (imagefile < 0) {
                printf("Error opening file: %s\n", user.filename);
            } else {
                // Read the first 16 bytes of the image file into buffer
                read(imagefile, buffer, 16);
                printf("First 16 bytes of image: %s\n", buffer);
                close(imagefile);
            }
        } else {
            printf("Invalid phone number: %s\n", user.phone);
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t t1_id, t2_id;
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(User);

    mq_unlink(MSQ_NAME); // Remove any existing message queue with the same name
    mq = mq_open(MSQ_NAME, O_RDWR | O_CREAT, 0666, &attr);

    pthread_create(&t1_id, NULL, &thread1, (void *)&mq);
    pthread_create(&t2_id, NULL, &thread2, (void *)&mq);

    pthread_join(t1_id, NULL);
    pthread_join(t2_id, NULL);

    mq_close(mq);
    mq_unlink(MSQ_NAME); 

    return 0;
}