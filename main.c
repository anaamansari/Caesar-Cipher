/*
 * caesarcipher.c
 *
 *  Created on: Apr 10, 2015
 *      Author: aansari
 */



#include <stdio.h>
#include "tistdtypes.h"
#include <string.h>
#include <stdlib.h>

/* Function for encrypting and decrypting.
For encryption we use a positive key and for decrypting we use the same key but negative
*/
char *CipherText (char *src, int k)
{
	int len =strlen(src)-1;
	int i;
	int ch;

	for(i=0; i<len; i++)
	{	ch=(int)src[i];
		if(ch==(int)"\n"||ch==(int)" ")
			src[i]=src[i];
		else if (ch>='A' && ch<='Z')      // If the number is upper case, between A to Z add the key
			{
			ch+=k;
			if(ch>'Z') ch-=26;			// If there is overflow i.e ch>Z then subtract 26
			if(ch<'A') ch+=26;			// If there is underflow i.e ch<A then add 26
			}
		else if (ch>='a' && ch<='z')    // If the number is lower case, between a to z add the key
			{
			ch+=k;
			if(ch>'z') ch-=26;			// If there is overflow i.e ch>z then subtract 26
			if(ch<'a') ch+=26;			// If there is underflow i.e ch<a then add 26
			}

		src[i]=(char)ch;				// store the modified char
	}
}

int main (void)
 {

	char *txt, *src;
	FILE *fp1;                        		    // File pointers
	int size, k, q,d;									// Variable to contain the size of the file
	fp1 = fopen("..\\filetext.txt", "rb");		// Open input file

	// Determine the size of the file
	if(fp1==NULL)
		perror( "Error opening file");
	else
		{
		fseek (fp1,0,SEEK_END);					// Move the stream position indicator at the end
		size=ftell(fp1);						// Determine position indicator
		}

		fseek (fp1,0,SEEK_SET);					// Move the stream position indicator at the beginning
		//size=size/sizeof(Uint8);
	txt=(char*)malloc(size);txt[0]=0;			// Allocate size number of bytes for a char pointer array
	fread(txt,sizeof(Uint8) ,size, fp1);		// Read the file stream fp1 and store in txt
			txt[size]=0;						// Mark the end of file with a null
	printf("\n Text to Encrypt \n \n%s", txt);
	// User Interface for entering the parameters
	printf("\n \n Starting the Caesar Cipher program");
	printf("\n \n  Enter key between 1 - 25\n");
	scanf("%d",&k);								// Store the response for key in k
	while (k<1 || k>25)
	{
		printf("\n \n  Invalid number, Enter a number between 1 and 25\n");
		scanf("%d",&k);
	}

	printf ("\n \n  Enter 1 for encrypt and 2 for Decrypt\n");
	scanf ("%d",&q);							// Store the response for encryption and decryption in q
	while(!(q==1||q==2))
	{
		printf("\n \n Invalid response, Enter 1 for encrypt and 2 for Decrypt\n \n %s", txt);
		scanf ("%d",&q);
	}
	if (q==1)
		{
		CipherText(txt,k);						// Encrypt
		printf("\n \n Encrypted Text \n \n%s", txt);
		}

		else if (q==2)
			{
			CipherText(txt,-k);					// Decrypt with a - k
			printf("\n \n Decrypted Text \n \n %s", txt);
			}


	printf("\n \n  Decrypt Back? y=1/n=2 ");
	scanf("%d",&d);
	if (d==1)
		{
		src= txt;								// Decrypting the encrypted result
		CipherText(src,-k);
		printf("\n \n  Decrypted Text \n \n %s", src);
		}

	else
		printf("\n \n You're done \n");

	fclose(fp1);
}





