#include <iostream>
#include<conio.h>
using namespace std;
	
float pSuma(float numA, float numB) {
	float resultado = 0;
	_asm {
		FLD DWORD PTR[numA]; Insertar parametro numA a la pila del coprocesador matematico
		FLD DWORD PTR[numB]; Insertar parametro numB a la pila del coprocesador matematico
		FADD; Sumar los numeros que estan en la pila del coprocesador
		FSTP DWORD PTR[resultado] ;Pop en pila y guardar en la variable resultado
	}
	return resultado;
}
float pResta(float numA, float numB) {
	float resultado = 0;
	_asm {
		FLD DWORD PTR[numB]
		FLD DWORD PTR[numA]
		FSUB ;Restar los numeros que estan en la pila del coprocesador
		FSTP DWORD PTR[resultado]
	}
	return resultado;
}
float pMultiplicacion(float numA, float numB) {
	float resultado = 0;
	
	_asm {
		FLD DWORD PTR[numA]
		FLD DWORD PTR[numB]
		FMUL ;Multiplicar los numeros que estan en la pila del coprocesador
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
		FDIV ;dividir los numeros que estan en la pila del coprocesador
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
		LEA EDX, arrA; Obtener direccion del arreglo A y almacenarlo en el registro EDX
		MOV EAX, 4 ; Asignar 4 al registro EAX
		IMUL EAX,indexJ ;Multiplicacion sin signo entre indice para J de la matriz y EAX 
		ADD EDX,EAX ;Agregar saltos de columna a la direccion
		MOV EAX,16 ;Cargar 16, cambio de fila
		IMUL EAX,indexI ;Multiplicacion sin signo por el indice i de la matriz y almacenado en EAX
		ADD EDX, EAX ;Agregar saltos de fila a la direccion
		MOV EAX, DWORD PTR[EDX] ;Traer elemento de la matriz y almacenarlo en EAX
		PUSH EAX ;Agregamos primer operando a la pila
		LEA EDX, arrB Obtener direccion del arreglo B y almacenarlo en el registro EDX
		MOV EAX, 4
		IMUL EAX, indexJ
		ADD EDX, EAX
		MOV EAX, 16
		IMUL EAX, indexI
		ADD EDX, EAX
		MOV EAX, DWORD PTR[EDX]
		PUSH EAX ; Agregamos Segundo operando a la pila
		CALL pSuma ; Llamar funcion en c++ pSuma (los parametros que cargamos a la pila pasan a la funcion)
		POP EAX ;Sacar Segundo operando
		POP EAX ;Sacar primer operando
		LEA EDX, arrC ;Cargar direcion del arreglo C (Primer elemento) y almacenarlo en EDX
		MOV EAX, 4
		IMUL EAX, indexJ
		ADD EDX, EAX
		MOV EAX, 16
		IMUL EAX, indexI
		ADD EDX, EAX
		FSTP DWORD PTR[EDX] ;Sacar resultado del metodo pSuma y almacenarlo en su lugar dentro del arreglo C
		INC indexJ ;Incrementar indice J
		CMP indexJ,3; Preguntar por indice J para saber si hay que pasar de fila
		JLE SALTO_J ;Si es menor o igual a 3, seguir con la siguiente columna
		MOV indexJ,0 ;Si es mayor a 3 entonces cambiamos de fila, poner indice j en 0
		INC indexI, ;Incrementar indice i, nueva fila
		CMP indexI, 3 ;Mirar si llegamos a la ultima fila
		JLE SALTO_J ; Si todavia no, volvemos a recorrer filas
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
	goto imprimir;
	salir: return 0;
	// Por: Camilo Zuluaga, Juan Manuel Mejia y Sebastian López
}