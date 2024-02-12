#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int min(int a, int b) {
  return a < b ? a : b;
}


int lev(const char *str1, const char *str2, int len1, int len2){
	
 /*check guard clauses*/

	if(len2 == 0){
		return len1;
	}else if(len1 == 0){
		return len2;
	}else if(str1[len1 - 1] == str2[len2 - 1]){
		return (lev(str1, str2,(len1 - 1), (len2 - 1)));
	}

/*guard clauses don`t pass so an edit move is required and thus the edit distance is incremented*/

		int delete_cost = lev(str1, str2, (len1 - 1), len2) + 1;    //delete
		int insert_cost = lev(str1, str2, len1, (len2 - 1)) + 1;		//insert
		int substitute_cost = lev(str1, str2, (len1 - 1), (len2 - 1)) + 1; //substitute

  // Choose minimum cost
  return min(delete_cost, min(insert_cost, substitute_cost));
}

int main(int argc, char const *argv[])
{
	int edit = lev(argv[1], argv[2], strlen(argv[1]), strlen(argv[2]));
	printf("Edit distance: %d\n", edit);
	return 0;
}
