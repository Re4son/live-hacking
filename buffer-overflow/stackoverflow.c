/* Name: stackoverflow.c
   Author: Re4son <re3son [at] whitedome.com.au>
   Purpose: Demonstration of a buffer overflow exlpoit.
	    The function "vuln" contains a buffer overflow
	    vulnerability that, when exploited, allows an
	    attacker to execute function "exploit".
   Compile: gcc -o stackoverflow stackoverflow.c
*/

#pragma check_stack(off)

#include <stdio.h>
#include <string.h>

/* function vuln: print stack on screen,copy user input into buffer without bounds checking and print stack again*/
void vuln( const char* input )
{
    char buf[10];

    printf("Stack before exploit:\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n\n"); /*Dump the relevant part of the stack on screen */

    strcpy(buf, input); /* Our bo vulnerability */
    printf("Copying %s onto the stack\n\n", buf);

    printf("Stack after exploit:\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n %p\n\n"); /*Dump the relevant part of the stack on screen */
}

void exploit( void )
{
    printf("Oops, I've been pwn3d!!\n");
}

int main( int argc, char *argv[] )
{
    printf("Address of function \"vuln\"   : %p\n", vuln);
    printf("Address of function \"exploit\": %p\n", exploit);
    printf("Address of function \"main\"   : %p\n", main);

    if (argc != 2){
        printf("Usage %s <string>\n", argv[0]);
        return -1;
    }
    vuln(argv[1]);
    return 0;
}
