#include <stdio.h>
#include <rpc/des_crypt.h>

int main(int argc, char* argv[]){
	char key[] = "abcd1234";
	char msg[] = "dennis is great ";
	unsigned msgLength = 16; //should be multiple of 8
	
	//encrypt
	printf("Key setparity: %s\n", key);
	des_setparity(key);
	printf("Key setparity: %s\n", key);
	
	printf("Message before encrypt: %s\n",msg);
	ecb_crypt(key, msg, msgLength, DES_ENCRYPT); 	//defined in header
	printf("Message after encrypt: %s\n", msg);

	ecb_crypt(key,msg,msgLength,DES_DECRYPT); //decrypt message

	printf("Message after decrypt: %s\n", msg);

	return 0;
}
