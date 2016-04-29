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
		FLD DWORD PTR[numB]
		FLD DWORD PTR[numA]
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
	if (numA == 0) {
		cout << "Error: Division por 0 detectada, retornando -1 en el arreglo"<<endl;
		resultado = -1;
		goto error_sal;
	}
	_asm {
		FLD DWORD PTR[numB]
		FLD DWORD PTR[numA]
		FDIV
		FSTP DWORD PTR[resultado]
	}
	error_sal:
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
	_asm {
		SALTO_J:
		LEA EDX, arrA
		MOV EAX,4
		IMUL EAX,indexJ
		ADD EDX,EAX
		MOV EAX,16
		IMUL EAX,indexI
		ADD EDX, EAX
		MOV EAX, DWORD PTR[EDX]
		PUSH EAX
		LEA EDX, arrB
		MOV EAX, 4
		IMUL EAX, indexJ
		ADD EDX, EAX
		MOV EAX, 16
		IMUL EAX, indexI
		ADD EDX, EAX
		MOV EAX, DWORD PTR[EDX]
		PUSH EAX
		CALL pSuma
		POP EAX
		POP EAX
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
void restar() {
	float arrA[4][4];
	float arrB[4][4];
	float arrC[4][4];
	iniciarMatriz('a', arrA);
	iniciarMatriz('b', arrB);
	int indexI = 0, indexJ = 0;
	_asm {
	SALTO_J:
		LEA EDX, arrA
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			MOV EAX, DWORD PTR[EDX]
			PUSH EAX
			LEA EDX, arrB
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			MOV EAX, DWORD PTR[EDX]
			PUSH EAX
			CALL pResta
			POP EAX
			POP EAX
			LEA EDX, arrC
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			FSTP DWORD PTR[EDX]
			INC indexJ
			CMP indexJ, 3
			JLE SALTO_J
			MOV indexJ, 0
			INC indexI
			CMP indexI, 3
			JLE SALTO_J
	}
	imprimirMatriz(arrC);
}
void multiplicar() {
	float arrA[4][4];
	float arrB[4][4];
	float arrC[4][4];
	iniciarMatriz('a', arrA);
	iniciarMatriz('b', arrB);
	int indexI = 0, indexJ = 0;
	_asm {
	SALTO_J:
		LEA EDX, arrA
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			MOV EAX, DWORD PTR[EDX]
			PUSH EAX
			LEA EDX, arrB
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			MOV EAX, DWORD PTR[EDX]
			PUSH EAX
			CALL pMultiplicacion
			POP EAX
			POP EAX
			LEA EDX, arrC
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			FSTP DWORD PTR[EDX]
			INC indexJ
			CMP indexJ, 3
			JLE SALTO_J
			MOV indexJ, 0
			INC indexI
			CMP indexI, 3
			JLE SALTO_J
	}
	imprimirMatriz(arrC);
}
void dividir() {
	float arrA[4][4];
	float arrB[4][4];
	float arrC[4][4];
	iniciarMatriz('a', arrA);
	iniciarMatriz('b', arrB);
	int indexI = 0, indexJ = 0;
	_asm {
	SALTO_J:
		LEA EDX, arrA
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			MOV EAX, DWORD PTR[EDX]
			PUSH EAX
			LEA EDX, arrB
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			MOV EAX, DWORD PTR[EDX]
			PUSH EAX
			CALL pDivision
			POP EAX
			POP EAX
			LEA EDX, arrC
			MOV EAX, 4
			IMUL EAX, indexJ
			ADD EDX, EAX
			MOV EAX, 16
			IMUL EAX, indexI
			ADD EDX, EAX
			FSTP DWORD PTR[EDX]
			INC indexJ
			CMP indexJ, 3
			JLE SALTO_J
			MOV indexJ, 0
			INC indexI
			CMP indexI, 3
			JLE SALTO_J
	}
	imprimirMatriz(arrC);
}
int main() {
	int opcion = 0;
	imprimir: imprimirMenu();
	cin >> opcion;
	switch (opcion) {
	case 1:
		sumar();
	break;
	case 2:
		restar();
	break;
	case 3:
		multiplicar();
	break;
	case 4:
		dividir();
	break;
	case 5:
		goto salir;
		break;
	default:
		goto imprimir;
	}
	//cout  << endl<< "Suma de 1 y 2" << suma(1, 2) << endl;
	//cout << ejemploArr(c) << endl;
	goto imprimir;
	salir: return 0;
}