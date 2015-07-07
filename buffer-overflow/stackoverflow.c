/* Name: stackoverflow.c
   Author: Re4son <re3son [at] whitedome.com.au>
   Purpose: Demonstration of a buffer overflow exlpoit.
	    The function "vuln" contains a buffer overflow
	    vulnerability that, when exploited, allows an
	    attacker to execute function "secret" without a valid password.
   Compile: gcc -fno-stack-protector -z execstack -o stackoverflow stackoverflow.c
   Usage: ./stackoverflow <string> [-d]
*/

#pragma check_stack(off)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *PASSWORD = "P455w0Rd";
int hacked = 0;
int deb;

void vuln( const char* );
void secret( void );


/* function vuln: print stack on screen,copy user input into buffer without bounds checking and print stack again*/
void vuln( const char* input )
{
    char buf[10];
    if (deb == 1) /*Dump the relevant part of the stack on screen */
        printf("[+] Stack before vulnerable instrucion:\n"
		"\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n"
		"\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n"
		"\t%p\n\t%p\n\t%p\n\t%p\n\n");

    strcpy(buf, input); /* Our bo vulnerability */

    if (deb == 1) /*Dump the relevant part of the stack on screen */
        printf("[+] Stack after copying %s onto the stack:\n"
               "\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n"
	       "\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n"
	       "\t%p\n\t%p\n\n", buf);


    if (strcmp(buf, PASSWORD) == 0)
        secret();
    else {
        printf("\n\tIncorrect Password.\n\n");
        hacked = 1;
    }

}

void secret( void )
{
    printf("\n[*] The secret password for the vault = \"BeHappy.1.2.3\"\n\n");
    if (hacked == 1){
        printf("[!] ARGH, I've been hacked!\n\n"); 
        exit(0);
    }
}

int main( int argc, char *argv[] )
{

    if (argc < 2){
        printf("\n\tUsage %s <password> [-d]\n\n", argv[0]);
        return -1;
    } else if (argc == 3){
        deb = 1;
	printf("\n[+] Address of function \"secret\":\t%p\n", secret);
    }
    vuln(argv[1]);
    return 0;
}
