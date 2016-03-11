#include <stdio.h>
#include <string.h> 
int binarySearch(int *arr, int start, int end, item)
int main() {
	int arr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}
	//Search for item
	int item = 4;
	int result = binarySearch(arr,0, (sizeof(arr)/sizeof(int))-1), item);  // instead of int you can write "int intem" 
	if (result)
		printf("%d is in the array\n", item);
	else
		prinf("%d is not in the array \n",item);
return 0;
}

int binarySearch(int *arr, int start, int end, int item) {  //  notice that even though it is here where you
	//are defining what the function does, you are always use it simulataously, all this code nees now is the equal
	// case (item == mid ) and the case where the item does not exsist 

// base   : used
	if (start==end) {
		return 1;

	}
	if (mid==item) {
		return 1;

	}
 int mid = (end - start)/2
 // split into smaler subproblems
 // search right side if item is greater than  middle number
  if (item > arr[start+mid]){
  	binarySearch(arr, start + mid + 1, end, item);
  }
  // Search left side if item is less than middle number
  else if (item < arr[start + mid]){
  	binarySearch(arr, start, start + mid - 1 , item);
  }
// Returns 1 if item is found and 0 if not
  else {
  	return 0;
  }
}

