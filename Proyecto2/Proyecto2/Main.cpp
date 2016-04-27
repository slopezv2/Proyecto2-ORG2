#include <iostream>
#include<conio.h>
using namespace std;
float suma(float num1, float num2) {
	float result=0;
	_asm {
		FLD DWORD PTR[num1] 
		FLD DWORD PTR[num2]
		FADD
		FSTP DWORD PTR[result] 
	}
	return result;
}
float ejemploArr() {
	float arr[3][3];
	arr[1][2] = 2;
	arr[1][1] = 5;
	float result=0;
	float index = 1.8;
	__asm {
		lea eax,arr
		add eax,16
		FLD DWORD PTR[index]
		FLD DWORD PTR[EAX]
		FADD
		FSTP DWORD PTR[result]
	}
	return result;
}


int main() {
	//cout  << endl<< "Suma de 1 y 2" << suma(1, 2) << endl;
	cout << ejemploArr() << endl;
	_getch();
	return 0;
}