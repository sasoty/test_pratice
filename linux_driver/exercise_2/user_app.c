#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int8_t write_buf[1024];
int8_t read_buf[1024];
int main()
{
        FILE* fptr;

        char option;


        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        o. Open               \n");
                printf("        w. Write               \n");
                printf("        r. Read                 \n");
                printf("        c. Close                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case 'o':
                                fptr = fopen("/dev/my_device", "r");
                                if(fptr < 0) 
                                {
                                printf("Cannot open device file...\n");
                                return 0;
                                }
                                break;
                        case 'w':
                                fptr = fopen("/dev/my_device", "r");
                                if(fptr < 0) 
                                {
                                printf("Cannot open device file...\n");
                                return 0;
                                }
                                printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);
                                printf("Data Writing ...");
                                fwrite(write_buf,1,  strlen(write_buf)+1,fptr);;
                                printf("Done!\n");
                                break;
                        case 'r':
                                fptr = fopen("/dev/my_device", "r");
                                if(fptr < 0) 
                                {
                                printf("Cannot open device file...\n");
                                return 0;
                                }
                                printf("Data Reading ...");
                                fread(read_buf, 1024,1,fptr);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case 'c':
                                fclose(fptr);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fptr);
}
