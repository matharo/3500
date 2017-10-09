#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <rpc/des_crypt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
   char key;
   char data[3217784];
   unsigned datalen;
   unsigned mode;
   int fd;
   int ofd;
   int error_flag=0;
   long count; 


   if(strlen(argv[1])!=8) {
       printf("Key should contain only 8 characters");
       error_flag=1;
    }
   if ((fd=open(argv[2],O_RDONLY) ) == -1) {
       printf("Error opening input file...\n");
       error_flag=2;
    }
   if((ofd=open(argv[3],O_WRONLY | O_CREAT | O_TRUNC, 0644))==-1) {
      printf("Error opening output file ...\n");
      error_flag=3;
    }
   if (strlen(argv[4])!=1 ) {
      printf("mode value should be either 0 (Encrypt) or 1 (Decrypt)\n");
      error_flag=4;
    }
   else {
      mode = atoi(argv[4]);
      if( !(mode==0||mode==1) ) {
          printf("mode value should be either 0 (Encrypt) or 1 (Decrypt)\n");
          error_flag=5;
       }
    }
   if(error_flag!=0) {
      close(fd);
      close(ofd);
      exit(error_flag);
    }

    fd = open(argv[2],O_RDONLY);
    datalen = read(fd, data, 3217784);

    key = argv[1];
    des_setparity(key);

    if (mode == 0) {
        ecb_crypt(key, data, datalen, DES_ENCRYPT);
    }
    if (mode == 1) {
        ecb_crypt(key, data, datalen,  DES_DECRYPT);
    }

    write(ofd, data,datalen);
    close(ofd);
    close(fd);

return 0;
}
