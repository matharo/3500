#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <rpc/des_crypt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char* key;
    int msglen;
    int nbytes;
    int mode;
    int fd;
    int ofd;
    int error = 0;
    
    if(strlen(argv[1])!= 8) {
        printf("Key should have 8 characters. \n");
        error = 1;
    }
    if ((fd = open(argv[2],O_RDONLY) ) == -1) {
        printf("Error. File can't be opened. \n");
        error = 1;
    }

    if((ofd = open(argv[3],O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        printf("Error. Output file can't be created. \n");
        error = 1;
    }
    mode = atoi(argv[4]);
    if (!(mode == 0||mode == 1)) {
        printf ("Mode should be 0 to encrypt or 1 to decrypt. \n");
        error = 1;
    }
    if(error != 0) {
        close(fd);
        close(ofd);
        exit(error);
    }

    fd = open(argv[2],O_RDONLY);
    struct stat buf;
    fstat(fd,&buf);
    msglen = buf.st_size;
    
    char msg[msglen];
    nbytes = read(fd, msg, msglen);
    key = argv[1];
    des_setparity(key);
    if (mode == 0) {
        ecb_crypt(key, msg, nbytes-1, DES_ENCRYPT); //nbytes-1 to get divisible by 8
    }
    if (mode == 1) {
        ecb_crypt(key, msg, nbytes-1,  DES_DECRYPT);
    }
    write(ofd, msg, nbytes);
    close(ofd);
    close(fd);
    printf("%d\n", msglen);
    printf("%d\n", nbytes);
    return 0;
}
