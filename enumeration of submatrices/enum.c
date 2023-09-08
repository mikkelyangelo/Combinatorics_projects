#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int Cods(int a , int b){
	int c=0;
	int s = (int)fmax(a,b);
	//printf("Идекс:\tYn\tYk\tXn\tXk\t:Код\n");
	for(int y_n = 0; y_n<b; y_n++){
		for(int y_k = 0; y_k<b; y_k++){
			for(int x_n = 0; x_n<a; x_n++){
				for(int x_k = 0; x_k<a; x_k++){
					if((y_n<=y_k)&&(x_n<=x_k))
						printf("%d:\t%d\n",++c, (int)(y_n*(pow(s,3)) + y_k*(pow(s,2)) + x_n*s + x_k));
						
				}	
			}	
		}	
	}
	
	return 0;
}

int Decods(int a, int b, int C){
	int s = (int)fmax(a,b);
	int C1 = C/s/s/s % s;
	int C2 = C/s/s % s;
	int C3 = C/s % s;
	int C4 = C % s;
	
	printf("%d\t%d\t%d\t%d\n", C1, C2, C3, C4);
	Paskal(C1, C2, C3, C4);
}

int check(int a, int b, int C){
	int c=0;
	int s = (int)fmax(a,b);
	for(int y_n = 0; y_n<b; y_n++){
		for(int y_k = 0; y_k<b; y_k++){
			for(int x_n = 0; x_n<a; x_n++){
				for(int x_k = 0; x_k<a; x_k++){
					if((y_n<=y_k)&&(x_n<=x_k))
						if(C == (int)(y_n*(pow(s,3)) + y_k*(pow(s,2)) + x_n*s + x_k))
							return 1;
				}	
			}	
		}	
	}
	return 0;
}

int frac(int n){
	return (n <2) ? 1 : n * frac(n-1);
}

int Cnm(int n, int m){
	return (int)(frac(n)/(frac(m)*frac(n-m)));
}

int Paskal(int yn, int yk, int xn, int xk){
	printf("Матрица:\n");
	for(int i = yn; i<=yk; i++){
		for(int j = xn; j<=xk; j++){
			if(i>=j)
				printf("%d\t", Cnm(i,j));
			else
				printf("%d\t", 0);
		}
		printf("\n");
	}
	return 0;

}

int main(int argc, char* argv[]){
	int a;
	int b;
	printf("Введите 1 число размерности матрицы: ");
	scanf("%d", &a);
	printf("Введите 2 число размерности матрицы: ");
	scanf("%d", &b);
	int C;
	printf("\n");
	Cods(a,b);
	printf("\n");
	for(int i = 0; i<5; i++){
		printf("Введите код: ");
		scanf("%d", &C);
		if(check(a, b, C)){
			printf("Координаты матрицы:");
			Decods(a, b, C);
		} else {
			printf("Неправильный код\n");
		}
		printf("\n");
		
	}
	return 0;
