#include <stdio.h>

void change3(int *value){
	*value = 3;
}

void change2(int *value){
	*value = 1;
	change3(value);
}

void change( int *value ){
	*value = 0;
	change2(value);
}

int main(){
	int slices = 20;
	int *p = &slices;
	
	change(&slices);

	int* pk = NULL;

	printf("Pk adress: %d\n", *pk);

	printf("Slices: %d\n", slices);
	printf("Slices (through ponter): %d\n", *p);

	slices = 21;

	printf("Slices: %d\n", slices);
	printf("Slices (through ponter): %d\n", *p);

	*p = 25;

	printf("Slices: %d\n", slices);
	printf("Slices (through ponter): %d\n", *p);	

	return 0;
}
