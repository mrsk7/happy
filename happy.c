#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void logEntry(const char *func) {
	printf("Entry: %s\n",func);
}	

void logExit(const char *func) {
	printf("Exit: %s\n",func);
}	

int ipow(int base, int exp) {
    int result = 1;
	 while (exp)	{
		if (exp & 1) result *= base;
		 exp >>= 1;
		 base *= base;
	}
 	return result;
}

int getNumOfDigits(int x) {
	int i=10;
	int ret=0;
	while (x>=1) {
		x/=10;
		ret++;
	}
	return ret;
}

bool isHappy(int x) {
	if (x==1) return true;
	else if (x==4) return false;
	else {
		if (x<10) return isHappy(ipow(x,2));
		else if (x<100) return isHappy(ipow(x/10,2)+ipow(x%10,2));
		else return isHappy(ipow(x/100,2)+ipow((x%100)/10,2)+ipow(x%10,2));
	}
}

computeAllHappy(bool *array, int size) {
	int i;
	for (i=1;i<=size;i++) {
		if (isHappy(i)) array[i] = true;
		else array[i] = false;
	}
}
    
int main (int argc, char *argv[]) {
    char *input = argv[1] ;
	FILE *file;
    if (argc<2) {
        printf("Wrong execution. Try %s input_file\n",argv[0]);
        exit(1);
    }
    file = fopen(input,"r");
	int A,B,dummy,i;
    if ((dummy = fscanf(file,"%d%d",&A,&B)) == 0) {
		printf("Error reading A,B\n");
		exit(1);
	}
	int pwr=getNumOfDigits(B);
	int max = pwr*81;			//Maximum sum of squares that can be found is pwr*81 where pwr is the number of digits of digits
	bool *happy = (bool *) malloc(max*sizeof(bool)+1);	//Allocation of array with size max
	if (happy==NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	computeAllHappy(happy,max);		//Compute all happy numbers up to max. Maximum for max is 732=9*81
	free(happy);
	fclose(file);
	return 0;
}
