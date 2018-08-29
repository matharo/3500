#include <stdio.h>
#include <rpc/des_crypt.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define bufferSize 4096

int main ( int argc, char* argv[]){
        char buffer [bufferSize];
        if(argc != 5){
                fprintf(stdout, "Encrypt takes exactly 4 arguments\n");
                exit(-1);
        }
        char*key = argv[1];
        if (strlen(key) != 8) {
        	fprintf(stdout, "The key must be 8 characters long\n");
                exit(-1);
        }
        int mode = strtol(argv[4], NULL, 10);
        if (mode != 1 && mode != 0) {
                fprintf (stdout, "The mode must be 0 or 1\n");
                exit(-1);
        }
        char* readFile = argv[2];
        char* writeFile = argv[3];
        int readReadFile;
        int openReadFile;
        int openWriteFile;

        openReadFile = open(readFile, O_RDWR);
        if (openReadFile == -1) {
                perror("There was an error opening the read file\n");
                exit(-1);
        }
        readReadFile = read(openReadFile, buffer, bufferSize);
        if (readReadFile == -1){
                perror("There was an error opening the write file\n");
                exit(-1);
        }
        openWriteFile = open(writeFile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
        if (openWriteFile == -1) {
                perror("There was an error opening the write file\n");
                exit(-1);
        }
        des_setparity(key);

		while(readReadFile != 0){
                while((readReadFile % 8) != 0) {
                        buffer[readReadFile] = ' ';
                        readReadFile++;
                }

                if (mode == 1){
                        ecb_crypt(key, buffer, bufferSize, DES_DECRYPT);
                }
                if (mode == 0){
                        ecb_crypt(key, buffer, bufferSize, DES_ENCRYPT);
                }

                write(openWriteFile, buffer, readReadFile);
                if(readReadFile == 0) {
                	break;
                }
                if(readReadFile == -1) {
                        perror("There was an error reading the file\n");}

                readReadFile = read(openReadFile, buffer, bufferSize);
                }

        close(openReadFile);
        close(openWriteFile);
}
        
        
        
        
        
        
