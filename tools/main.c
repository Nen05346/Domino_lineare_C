#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include "domino.h"

// ------------------------------------------ MAIN ---------------------------------------------------------

int main(){
	/// random seeds based on the time
	srand(time(NULL));
	/// the function menu contains all the process for the program
	menu(); 
	return 0;
}
