#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

#define MAX_PHONE_LENGTH 20

int valid_check(char phone[10])
{
    int ret = strncmp(phone, "090", 3) == 0 || strncmp(phone, "093", 3) == 0 || strncmp(phone, "094", 3) == 0;
    return ret;
}

typedef struct User {
    char name[20];
    int age;
    char phone[MAX_PHONE_LENGTH];
    char filename[48];
} User;

User user;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;

void *thread1(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("Enter name: ");
        scanf("%s", user.name);
        printf("Enter age: ");
        scanf("%d", &user.age);
        printf("Enter phone number: ");
        scanf("%s", user.phone);
        printf("Enter filename: ");
        scanf("%s", user.filename);

        ready = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);


        sleep(1);
    }
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    
    char buffer[16];
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!ready) {
            
            pthread_cond_wait(&cond, &mutex);
        }

        if (strlen(user.phone) == 10 && valid_check(user.phone)) {
            printf("Valid phone number: %s\n", user.phone);
            int imagefile = open(user.filename, O_RDONLY);
            if (imagefile < 0) {
                printf("Error opening file: %s\n", user.filename);
            } else {
                read(imagefile, buffer, 16);
                printf("First 16 bytes of image: %s\n", buffer);
                close(imagefile);
            }
        } else {
            printf("Invalid phone number: %s\n", user.phone);
        }


        ready = 0;
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1_id, t2_id;

    pthread_create(&t1_id, NULL, &thread1, NULL);
    pthread_create(&t2_id, NULL, &thread2, NULL);

    pthread_join(t1_id, NULL);
    pthread_join(t2_id, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}