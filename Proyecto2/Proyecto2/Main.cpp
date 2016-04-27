#include <iostream>
#include<conio.h>
using namespace std;
float a[4][4];
float b[4][4];
float c[4][4];	
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
float pDivision(float numA, float numB) {
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
void imprimirMatriz(float matriz[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "|" << matriz[i][j] << "|";
		}
		cout << endl;
	}
}
float obtenerDato(int i, int j) {
	float numero = 0;
	cout << "Ingrese el dato " << i << " , " << j << endl;
	cin >> numero;
	return numero;
	
}
void iniciarMatriz(char letra, float matriz[4][4]) {
	cout << "Matriz " << letra << ":" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matriz[i][j] = obtenerDato(i, j);
		}
	}
}
void imprimirMenu() {
	cout << "Ingrese la operacion a ejecutar entre la matriz a y la matriz b" << endl;
	cout << "Luego de eso se va a imprimir el resultado, excepto para la opcion salida" << endl;
	cout << "1. Suma" << endl;
	cout << "2. Resta" << endl;
	cout << "3. Multiplicacion" << endl;
	//TODO
}
int main() {
	iniciarMatriz('a', a);
	iniciarMatriz('b', b);
	imprimirMatriz(a);
	imprimirMatriz(b);
	//cout  << endl<< "Suma de 1 y 2" << suma(1, 2) << endl;
	cout << pDivision(4.3,8) << endl;
	_getch();
	return 0;
}