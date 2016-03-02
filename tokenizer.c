#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *GetToken(char *str) 
{
	
	static char *str2;
	if (str != NULL) {  // as long as the address of str doesn not point to NULL (which is outside the stack)
		str2 = str;
	}

	char *ptr = str2;
	if(*str2 == '\0'){
		return NULL;
	}
	while((*str2) != ' '){
		if(*str2 == '\0'){
			return ptr;
		}
		str2++;
	}	
	*str2 = '\0';
	str2++;
	return ptr;
	
// Search for first space in str
// Change space to '\0'
// Change str so that it points to the next
// Return address of previous token
// Return NULL if string is empty 

	// do some print statements and see where it crashes 
}

int main() {
char abc[] = "apple bee cars dogs eggs figs goodies"; 
// abc is a pointer??
char *token = GetToken(abc);
while (token !=NULL){
	printf("%s\n",token);
	token = GetToken(NULL);
}
return 0;
}
