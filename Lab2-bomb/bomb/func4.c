#include <stdio.h>
int func4(int a1,int a2,int a3){
	int ax = 0;
	int cx = 0;
	if (a3>=a2){
		ax = (a3 - a2) >> 1;
	}else{
		ax = (a3 - a2 + 1) >> 1;
	}
	cx = ax + a2;

	if (cx = a1){
		return 0;
	}else if (cx > a1){
		a3 = cx - 1;
		return 2*func4(a1,a2,a3);
	}else if (cx < a1){
		a2 = cx + 1;
		return 2*func4(a1,a2,a3)+1;
	}
}
int main(){
	int in = 0;
	printf("Input a1 for func4:");
	if (scanf("%d",&in)<1){
		return 1;
	};
	printf("func4 return : %d\n",func4(in,0,14));
}
