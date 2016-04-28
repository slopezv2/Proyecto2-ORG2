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
	cout << "Luego de eso se va a pedir la entrada de las matrices, excepto para la opcion salida" << endl;
	cout << "1. Suma" << endl;
	cout << "2. Resta" << endl;
	cout << "3. Multiplicacion" << endl;
	cout << "4. Division" << endl;
	cout << "5. Salir" << endl;
}
void sumar() {
	float arrA[4][4];
	float arrB[4][4];
	float arrC[4][4];
	iniciarMatriz('a', arrA);
	iniciarMatriz('b', arrB);
	int indexI = 0, indexJ = 0;
	//imprimirMatriz(a);
	//imprimirMatriz(b);
	_asm {
		SALTO_J:
		LEA EDX, arrA
		MOV EAX,4
		IMUL EAX,indexJ
		ADD EDX,EAX
		MOV EAX,16
		IMUL EAX,indexI
		ADD EDX, EAX
		FLD DWORD PTR[EDX]
		LEA EDX, arrB
		MOV EAX, 4
		IMUL EAX, indexJ
		ADD EDX, EAX
		MOV EAX, 16
		IMUL EAX, indexI
		ADD EDX, EAX
		FLD DWORD PTR[EDX]
		FADD
		LEA EDX, arrC
		MOV EAX, 4
		IMUL EAX, indexJ
		ADD EDX, EAX
		MOV EAX, 16
		IMUL EAX, indexI
		ADD EDX, EAX
		FSTP DWORD PTR[EDX]
		INC indexJ
		CMP indexJ,3
		JLE SALTO_J
		MOV indexJ,0
		INC indexI
		CMP indexI, 3
		JLE SALTO_J
	 }
	imprimirMatriz(arrC);
}
float ejemploArr(){
	float carr[4][4];
	//float arr[3][3];
	carr[0][0] = 2;
	carr[1][0] = 5;
	float result = 0;
	float index = 1.8;
	__asm {
		lea edx, carr
		; add edx, 16
		FLD DWORD PTR[index]
		FLD DWORD PTR[EDX]
		FADD
		FSTP DWORD PTR[result]
	}
	return result;
}

int main() {
	int opcion = 0;
	//iniciarMatriz('a', a);
	//iniciarMatriz('b', b);
	//imprimirMatriz(a);
	//imprimirMatriz(b);
	imprimir: imprimirMenu();
	cin >> opcion;
	switch (opcion) {
	case 1:


		sumar();
		//ejemploArr(c);
	break;
	case 2:

	break;
	case 3:

	break;
	case 4:

	break;
	case 5:
		goto salir;
		break;
	default:
		goto imprimir;
	}
	//cout  << endl<< "Suma de 1 y 2" << suma(1, 2) << endl;
	//cout << ejemploArr(c) << endl;
	_getch();
	salir: return 0;
}