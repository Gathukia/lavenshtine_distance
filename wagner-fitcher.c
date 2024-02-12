#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
  return a < b ? a : b;
}

int main(int argc, char **argv){
	int len1 = strlen(argv[1]) + 1;
	int len2 = strlen(argv[2]) + 1;

	int matrix[len1][len2];
	for (int i = 0; i <= len1; i++) {
    matrix[i][0] = i;
  
  	}
  	for (int j = 0; j <= len2; j++) {
    matrix[0][j] = j;
  	}
	for (int i = 1; i <= len1; i++) {
  		for (int j = 1; j <= len2; j++) {
    		if((argv[1][i - 1] == argv[2][j - 1])){
    			matrix[i][j] = min(matrix[i][(j - 1)],min(matrix[(i - 1)][j],matrix[(i - 1)][(j - 1)])); 
    		}else{
    			matrix[i][j] = min(matrix[i][(j - 1)],min(matrix[(i - 1)][j],matrix[(i - 1)][(j - 1)])) + 1;	
    		}
    
    	}
    }
printf("Edit distance: %d\n", matrix[len1][len2]);
return 0;
 }