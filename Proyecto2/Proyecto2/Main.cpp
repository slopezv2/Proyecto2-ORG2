#include <iostream>
#include<conio.h>
using namespace std;
float pSuma(float numA, float numB) {
	float resultado = 0;
	_asm {
		FLD DWORD PTR[numA] 
		FLD DWORD PTR[numB]
		FADD
		FSTP DWORD PTR[resultado] 
	}
	return resultado;
}
float pResta(float numA, float numB) {
	float resultado = 0;
	_asm {
		FLD DWORD PTR[numA]
		FLD DWORD PTR[numB]
		FSUB
		FSTP DWORD PTR[resultado]
	}
	return resultado;
}
float pMultiplicacion(float numA, float numB) {
	float resultado = 0;
	_asm {
		FLD DWORD PTR[numA]
		FLD DWORD PTR[numB]
		FMUL
		FSTP DWORD PTR[resultado]
	}
	return resultado;
}
float pDivision() {
	float resultado = 0;
	_asm {
		FLD DWORD PTR[numA]
		FLD DWORD PTR[numB]
		FDIV
		FSTP DWORD PTR[resultado]
	}
	return resultado;
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
	cout << pMultiplicacion(4.3,8) << endl;
	_getch();
	return 0;
}