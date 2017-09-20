//Lorna Xiao and Vyshnavee Reddlapalli
//Sep 19 2017
//lab 2 SLUSH

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define string_size 256 

int main(int argc, char* argv[])
{
        char userstring[string_size];
	char* input;
        char* str;//token

        while (1)
        {
                printf("slush( ");
		//get entire user input
                input = fgets(userstring,string_size,stdin);
		//remove \n at the end
                string[(strlen(userstring)-1)]=0; 
		
		str = strtok(input, " ( ");
                while (str != NULL)
                {
			//separate rest of tokens, subsequential calls
                	//printf("token: %s\n",str);
                        str = strtok(NULL," ( ");

                }
                
        }
        return 0;
}
