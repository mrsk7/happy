#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
	int ret=0;
	while (x>=1) {
		x/=10;
		ret++;
	}
	return ret;
}

bool isHappy(int x) {
	if (x==1) return true;
	else if (x==4 || x==0) return false;
	else {
		if (x<10) return isHappy(ipow(x,2));
		else if (x<100) return isHappy(ipow(x/10,2)+ipow(x%10,2));
		else return isHappy(ipow(x/100,2)+ipow((x%100)/10,2)+ipow(x%10,2));
	}
}

void computeAllHappy(int *array, int size) {
	int i;
	for (i=1;i<=size;i++) {
		if (isHappy(i)) array[i] = 1;
		else array[i] = 0;
	}
}

int countUpToLimit(int **p,int lim,int *happy) {
    if (lim==0) return 0;
    int digits=0;
    int row = getNumOfDigits(lim)-1; //for example if XYZ is given as limit, I will search at 2nd row([0,2*81])
    int i,j,cnt,upper;
    cnt=0;
    int divider=ipow(10,row);   //for XYZ divider is starting as 100 so that we get X first
    while (divider>1) {
        upper = (lim/divider)%10;
        for (i=0;i<upper;i++) 
            for (j=0;j<=row*81;j++) 
                    cnt+= p[row][j]*happy[j+i*i+digits];
        divider/=10;
        digits+=upper*upper;
        row--;
    }
    upper = (lim/divider)%10;
    for (i=0;i<=upper;i++) 
        if (isHappy(digits+i*i)) cnt++;
    return cnt;
}


void fillArray(int **p,int lim) {
	int n = getNumOfDigits(lim);
        int i,j,offset;
	for (i=0;i<10;i++) p[1][i*i]=1;
	for (i=2;i<=n;i++) { 
            for (j=0;j<=(i-1)*81;j++) 
                for (offset=0;offset<10;offset++) 
                    p[i][j+offset*offset]+=p[i-1][j];
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
	int A,B,dummy,i,cnt;
        if ((dummy = fscanf(file,"%d%d",&A,&B)) == 0) {
		printf("Error reading A,B\n");
		exit(1);
	}
	int *happy = (int *) malloc(9*81*sizeof(int)+1);	//Allocation of array with size max
	if (happy==NULL) {
		printf("Error allocating memory(happy)\n");
		exit(1);
	}
        computeAllHappy(happy,9*81);
	int **array = malloc(10*sizeof(int *));	//Allocation of array with size A
	if (array==NULL) {
		printf("Error allocating memory(array)\n");
		exit(1);
	}
        for (i=0;i<10;i++) {
            array[i] = malloc(9*81*sizeof(int));
            if (array[i]==NULL) {
                    printf("Error allocating memory(array[i])\n");
                    exit(1);
            }
        }
        fillArray(array,B);
	cnt = countUpToLimit(array,B,happy);
        cnt-= countUpToLimit(array,A-1,happy);
        if (B==ipow(10,9)) cnt++;      //Because 10^9 is happy but array is up to 9*81, thus 10^9-1 we just increment cnt
	printf("%d\n",cnt);
        free(array);
	free(happy);
	fclose(file);
	return 0;
}
