#include <stdio.h>
#include <stdlib.h>

int strCmp(char *str1, char *str2) // compares two strings and returns number of true comparisons
{
	int n=0;
	int i;
	for(i = 0; i < 49; i++){
		if (str1[0]==str2[i] && str1[1]==str2[i+1] && str1[2]==str2[i+2]){
			n++;
			printf("NO ");
			printf(str1, "\n");
			printf(str2, "\n");
		}

	}
	/**
	for (i=1; i%3==0 &&str2[i]!='\0';i=i+3) // making it start at 1 becus 0/3 has no remainder
	{	// make function that will 
			//take 3 chracters at a time and compare it to str1
		if (str1[0]==str2[i-3] && str1[1]==str2[i-2] && str1[2]==str2[i-1]) //in the next iteration
			// ith term will be evaluated but it will be called i-3
			n=n+1;
	}*/
		return n;
}

int main() {
//Open a FILE
FILE *fp =fopen("yourname.c","r");
//Read a string of length 49
char str[50];
int i=0;
int space=0;
//int keyword=0;
int j;
int n;

while (fgets(str,49,fp)) // fgets goes line by line so simply putting a counter is fine
{
	i=i+1; 
	for  (j=0;j<50;j++) // made up large random end point
	{
		if (str[j]==' '){
			 space=space+1; 
			}
				
				
    }
    n += strCmp("int",str);
}
printf("\n number of lines is %d \n",i);
printf("\n number of spaces is %d \n",space);
printf("\n number of int keywords is %d \n",n);
//printf("number of keywords is %d \n",keyword);
//Count number of lines
//Count number of spaces
//Count number of keyword
//close a file
fclose(fp);
return 0;
}