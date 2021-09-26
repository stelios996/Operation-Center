#include <stdio.h>
#include "hash.h"
							//hash function
unsigned long hashfunction(char* str){			//algorithm djb2 from:	www.cse.yorku.ca/~oz/hash.html
	unsigned long hash = 5381;
	int c;
	while(c = *str++)
		hash = ((hash<<5)+hash)+c;	
	return hash;
}
