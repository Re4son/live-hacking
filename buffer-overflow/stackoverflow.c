/* Name: stackoverflow.c
   Author: Re4son <re3son [at] whitedome.com.au>
   Purpose: Demonstration of a buffer overflow exlpoit.
	    The function "vuln" contains a buffer overflow
	    vulnerability that, when exploited, allows an
	    attacker to execute function "exploit".
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
    if (deb == 1)
        printf("Stack before vulnerable instrucion:\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\n"); /*Dump the relevant part of the stack on screen */

    strcpy(buf, input); /* Our bo vulnerability */


    if (strcmp(buf, PASSWORD) == 0)
        secret();
    else {
        printf("Copying %s onto the stack\n\n", buf);
        if (deb == 1)
            printf("Stack after exploit:\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n\n"); /*Dump the relevant part of the stack on screen */
        hacked = 1;
    }

}

void secret( void )
{
    printf("The secret:\n\nAdministrator password = BeHappy.1.2.3\n\n");
    if (hacked == 1){
        printf("ARGH, I've been hacked!\n\n"); 
        exit(0);
    }
}

int main( int argc, char *argv[] )
{
    printf("\nAddress of function \"secret\": %p\n", secret);

    if (argc < 2){
        printf("Usage %s <string>\n", argv[0]);
        return -1;
    } else if (argc == 3){
        deb = 1;
    }
    vuln(argv[1]);
    return 0;
}
