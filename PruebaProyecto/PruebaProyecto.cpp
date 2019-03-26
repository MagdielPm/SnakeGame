/**
* @file SnakeGame.cpp
* @version 2
* @date 17/05/2018
* @author Equipo 4
* @title Juego de Snake
* @brief Software donde se juega Snake
*/
 
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Mmsystem.h>
#include <string.h>

#pragma comment (lib, "winmm.lib")
using namespace std;

/*
Constantes reservadas para los movimientos y caracteres especiales
*/
#define arriba 72
#define abajo 80
#define izquierda 75 
#define derecha  77
#define enter  13
#define escape  27
#define ESD 187
#define ESI 201
#define EID 188
#define EII 200
#define HOR 205
#define VER 186
#define lleno 219
#define vacio 32




/*Seccion de pantalla de carga*/
void pantallaDeCarga();
void SetCursorPosition(int, int);
void splashDeCarga();
void textColor(char);
void bordes(int, int, int, int);
void titulo(int x, int y);
void titleSnake(int, int);
void titleGame(int, int);
void ocultarCursor();

/*Seccion de menu principal*/
void menuPrincipal();
int opcionesMenu();

/*Seccion del Juego*/
void jugar();
void movimientoSerpiente(int *, int *, int *);
void movimientoKinect(int *, int *, int *);
void guardarPosicion(int, int, int[][2], int *, int);
void dibujarCuerpo(int[][2], int);
void borrarCuerpo(int[][2], int);
void generarFruta(int *, int *, int *);
void validarColisiones(int *, int *, int *, int *, int[][2]);
void colisionFruta(int *, int*, int*, int*, int *, int *, int *);
void recuadroDePuntaje();
void levelAndScore(int *, int*, int *);

/*Seccion de ver puntaje*/
void verPuntuaciones();
void top_5(int, int);
void generarPuntuaciones(int, int);
void puntajes(int, char[10]);
void convertirEstructura(struct puntos[5]);

/*Estructura para manejar el puntaje*/
struct puntos {
	int puntuacion;
	char name[10];
};

/*Sonidos del juego*/
void procesoComida();




/*
Colores del texto y la consola:

Name        | Value
|
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15

*/

int main(int argc, char *argv[]) {
	pantallaDeCarga();
	menuPrincipal();
	
	return 0;
}
/**
* @brief menuPrincipal Muestra la pantalla donde se va a interactuar
* @author Magdiel Pech
*/
void menuPrincipal()
{
	int opcion;
	ocultarCursor();
	system("cls");
	bordes(118, 29, 0, 0);
	titulo(40, 2);
	opcion = opcionesMenu();
	switch (opcion) {
	case 1:
		jugar();
		break;
	case 2:
		verPuntuaciones();
		break;
	}

}
/**
* @brief opcionesMenu Interactúa con las opciones del menú
* @author Magdiel Pech
* @return Opcion elegida
*/
int opcionesMenu()
{
	int contador = 1;
	char leerOpcion;
	textColor(10);
	bordes(74, 19, 44, 17);
	SetCursorPosition(53, 18);
	printf("Iniciar partida");
	textColor(15);
	bordes(74, 23, 44, 21);
	SetCursorPosition(53, 22);
	printf("Ver puntajes");

	bordes(74, 27, 44, 25);
	SetCursorPosition(53, 26);
	printf("Salir del juego");
	do
	{
		leerOpcion = getch();

		if (contador>1 && leerOpcion == arriba)
		{
			contador--;
		}
		if (contador < 3 && leerOpcion == abajo)
		{
			contador++;
		}

		switch (contador)
		{
		case 1:
			textColor(10);
			bordes(74, 19, 44, 17);
			SetCursorPosition(53, 18);
			printf("Iniciar partida");
			textColor(15);
			bordes(74, 23, 44, 21);
			SetCursorPosition(53, 22);
			printf("Ver puntajes");
			textColor(15);
			bordes(74, 27, 44, 25);
			SetCursorPosition(53, 26);
			printf("Salir del juego");
			break;
		case 2:
			textColor(15);
			bordes(74, 19, 44, 17);
			SetCursorPosition(53, 18);
			printf("Iniciar partida");
			textColor(10);
			bordes(74, 23, 44, 21);
			SetCursorPosition(53, 22);
			printf("Ver puntajes");
			textColor(15);
			bordes(74, 27, 44, 25);
			SetCursorPosition(53, 26);
			printf("Salir del juego");
			break;
		case 3:
			textColor(15);
			bordes(74, 19, 44, 17);
			SetCursorPosition(53, 18);
			printf("Iniciar partida");
			textColor(15);
			bordes(74, 23, 44, 21);
			SetCursorPosition(53, 22);
			printf("Ver puntajes");
			textColor(10);
			bordes(74, 27, 44, 25);
			SetCursorPosition(53, 26);
			printf("Salir del juego");

			break;
		}
	} while (leerOpcion != enter);
	PlaySound(TEXT("menus.wav"), NULL, SND_SYNC);
	return contador;
}
/**
* @brief convertirEstructura Lee los datos de un archivo de texto y los guarda en un arreglo de estructuras
* @author César González
* @param puntuacionesTop Lugar donde se van a guardar las puntuaciones
*/
void convertirEstructura(struct puntos puntuacionesTop[5]) {
	int i;
	FILE *outFile = fopen("puntajes.txt", "r");
	for (i = 0; i<5; i++) {
		fscanf(outFile, "%d", &puntuacionesTop[i].puntuacion);
		fscanf(outFile, "%s", puntuacionesTop[i].name);
	}
	fclose(outFile);
}
/**
* @brief verPuntuaciones Accede a las primeras 5 puntuaciones
* @author César González y Magdiel Pech
*/
void verPuntuaciones() {
	system("cls");
	char leerOpcion;
	int contador = 1;
	struct puntos puntuacionesTop[5];
	int x = 35, y = 12, i;
	bordes(118, 29, 0, 0);
	top_5(40, 2);
	bordes(89, 28, 29, 8);
	bordes(86, 22, 32, 9);
	SetCursorPosition(35, 10);
	printf("Posicion");
	SetCursorPosition(55, 10);
	printf("Nombre");
	SetCursorPosition(75, 10);
	printf("Puntaje");
	convertirEstructura(puntuacionesTop);
	for (i = 0; i<5; i++) {
		textColor(15 - i);
		SetCursorPosition(x, y);
		printf("%d.-", (i + 1));
		x += 20;
		SetCursorPosition(x, y);
		printf("%s", puntuacionesTop[i].name);
		x += 20;
		SetCursorPosition(x, y);
		x = 35;
		y += 2;
		printf("%d", puntuacionesTop[i].puntuacion);
	}
	textColor(15);
	SetCursorPosition(51, 23);
	printf("Elige una opcion:");
	textColor(10);
	bordes(56, 27, 34, 25);
	SetCursorPosition(39, 26);
	printf("Menu principal");
	textColor(15);
	bordes(84, 27, 62, 25);
	SetCursorPosition(67, 26);
	printf("Salir del juego");
	do
	{
		leerOpcion = getch();
		if (contador == 1 && leerOpcion == derecha)
		{
			contador++;
		}
		if (contador == 2 && leerOpcion == izquierda)
		{
			contador--;
		}

		switch (contador)
		{
		case 1:
			textColor(10);
			bordes(56, 27, 34, 25);
			SetCursorPosition(39, 26);
			printf("Menu principal");
			textColor(15);
			bordes(84, 27, 62, 25);
			SetCursorPosition(67, 26);
			printf("Salir del juego");
			break;
		case 2:
			textColor(15);
			bordes(56, 27, 34, 25);
			SetCursorPosition(39, 26);
			printf("Menu principal");
			textColor(10);
			bordes(84, 27, 62, 25);
			SetCursorPosition(67, 26);
			printf("Salir del juego");
			break;
		}

	} while (leerOpcion != enter);
	if (contador == 1)
	{
		PlaySound(TEXT("menus.wav"), NULL, SND_SYNC);
		menuPrincipal();
	}
}
/**
* @brief pantallaDeCarga Muestra una pantalla de carga
* @author Magdiel Pech
*/
void pantallaDeCarga()
{
	ocultarCursor();
	//SetConsoleTitle("Snake Game");
	titulo(40, 5);
	bordes(118, 29, 0, 0);
	splashDeCarga();
	PlaySound(TEXT("menus.wav"), NULL, SND_SYNC);
	system("cls");
}
/**
* @brief splashDeCarga Muestra una barra que simula estar cargando el juego
* @author Magdiel Pech
*/
void splashDeCarga()
{
	int x = 26, y = 25, i, D = 66;
	textColor(15);
	SetCursorPosition(x, y);
	printf("%c", ESI);
	SetCursorPosition(x, y + 1);
	printf("%c", VER);

	SetCursorPosition(x, y + 2);
	printf("%c", EII);
	SetCursorPosition(x + D, y);
	printf("%c", ESD);
	SetCursorPosition(x + D, y + 1);
	printf("%c", VER);
	SetCursorPosition(x + D, y + 2);
	printf("%c", EID);
	SetCursorPosition(50, 23);
	printf("Cultivando frutas...");

	for (i = 1; i<D; i++)
	{
		SetCursorPosition(x + i, y);
		printf("%c", HOR);
		SetCursorPosition(x + i, y + 2);
		printf("%c", HOR);
	}
	textColor(10);
	for (i = 1; i<D; i++)
	{
		Sleep(50);
		SetCursorPosition(x + i, y + 1);
		printf("%c", 219);
	}
	SetCursorPosition(50, 23);
	printf("                      ");
	SetCursorPosition(46, 23);
	printf("Pulsa enter para continuar.");
	textColor(15);
	getch();

}
/**
* @brief textColor Cambia el color de las letras que se van a ingresar
* @author Magdiel Pech
* @param color Número del color a cambiar
*/
void textColor(char color)
{
	HANDLE manipuladorDeColor;
	manipuladorDeColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(manipuladorDeColor, color);
}
/**
* @brief SetCursorPosition Posiciona el cursor en una coordenada de la pantalla
* @author Magdiel Pech
* @param x Posición x
* @param y Posición y
*/
void SetCursorPosition(int x, int y)
{
	HANDLE manipulador;
	COORD coordenadas;
	manipulador = GetStdHandle(STD_OUTPUT_HANDLE);
	coordenadas.X = x;
	coordenadas.Y = y;
	SetConsoleCursorPosition(manipulador, coordenadas);
}
/**
* @brief ocultarCursor Oculta el recuadro blanco que indica donde está el cursor
* @author Magdiel Pech
*/
void ocultarCursor()
{
	CONSOLE_CURSOR_INFO visible;
	HANDLE maniCursor;
	maniCursor = GetStdHandle(STD_OUTPUT_HANDLE);
	visible.bVisible = FALSE;
	visible.dwSize = 100;
	SetConsoleCursorInfo(maniCursor, &visible);
}
/**
* @brief bordes Imprime un cuadro de caracteres ASCII
* @author César González
* @param x Valor final de la coordenada x del cuadro
* @param y Valor final de la coordenada y del cuadro
* @param inicioX Valor donde inicia la coordenada x del cuadro
* @param inicioY Valor donde termina la coordenada y del cuadro
*/
void bordes(int x, int y, int inicioX, int inicioY) {
	int i, j;
	SetCursorPosition(inicioX, inicioY);
	printf("%c", ESI);
	SetCursorPosition(inicioX, y);
	printf("%c", EII);
	SetCursorPosition(x, inicioY);
	printf("%c", ESD);
	SetCursorPosition(x, y);
	printf("%c", EID);
	for (j = 1; j<x - inicioX; j++) {
		SetCursorPosition(inicioX + j, inicioY);
		printf("%c", HOR);
	}
	for (j = 1; j<x - inicioX; j++) {
		SetCursorPosition(inicioX + j, y);
		printf("%c", HOR);
	}
	for (i = 1; i<y - inicioY; i++) {
		SetCursorPosition(inicioX, inicioY + i);
		printf("%c", VER);
	}
	for (i = 1; i<y - inicioY; i++) {
		SetCursorPosition(x, inicioY + i);
		printf("%c", VER);
	}
}
/**
* @brief titulo Posiciona el título del juego en la pantalla
* @author César González
* @param x Coordenada inicial x del título
* @param y Coordenada inicial y del título
*/
void titulo(int x, int y) {

	textColor(15);
	titleSnake(x, y);
	titleGame(x + 2, y + 7);
}
/**
* @brief titleSnake Imprime la palabra "Snake"
* @author César González
* @param x Coordenada inicial x
* @param y coordenada inicial y
*/
void titleSnake(int x, int y) {
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD, lleno, lleno, lleno, ESD, vacio, vacio, vacio, lleno, lleno, ESD, vacio, lleno, lleno, lleno, lleno, lleno, ESD, vacio, lleno, lleno, ESD, vacio, vacio, lleno, lleno, ESD, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, lleno, lleno, ESI, HOR, HOR, HOR, HOR, EID, lleno, lleno, lleno, lleno, ESD, vacio, vacio, lleno, lleno, VER, lleno, lleno, ESI, HOR, HOR, lleno, lleno, ESD, lleno, lleno, VER, vacio, lleno, lleno, ESI, EID, lleno, lleno, ESI, HOR, HOR, HOR, HOR, EID);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD, lleno, lleno, ESI, lleno, lleno, ESD, vacio, lleno, lleno, VER, lleno, lleno, lleno, lleno, lleno, lleno, lleno, VER, lleno, lleno, lleno, lleno, lleno, ESI, EID, vacio, lleno, lleno, lleno, lleno, lleno, ESD, vacio, vacio);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, EII, HOR, HOR, HOR, HOR, lleno, lleno, VER, lleno, lleno, VER, EII, lleno, lleno, ESD, lleno, lleno, VER, lleno, lleno, ESI, HOR, HOR, lleno, lleno, VER, lleno, lleno, ESI, HOR, lleno, lleno, ESD, vacio, lleno, lleno, ESI, HOR, HOR, EID, vacio, vacio);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, lleno, lleno, lleno, lleno, lleno, lleno, lleno, VER, lleno, lleno, VER, vacio, EII, lleno, lleno, lleno, lleno, VER, lleno, lleno, VER, vacio, vacio, lleno, lleno, VER, lleno, lleno, VER, vacio, vacio, lleno, lleno, ESD, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, EII, HOR, HOR, HOR, HOR, HOR, HOR, EID, EII, HOR, EID, vacio, vacio, EII, HOR, HOR, HOR, EID, EII, HOR, EID, vacio, vacio, EII, HOR, EID, EII, HOR, EID, vacio, vacio, EII, HOR, EID, EII, HOR, HOR, HOR, HOR, HOR, HOR, EID);
}
/**
* @brief titleSnake Imprime la palabra "Game"
* @author César González
* @param x Coordenada inicial x
* @param y coordenada inicial y
*/
void titleGame(int x, int y) {
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, vacio, lleno, lleno, lleno, lleno, lleno, lleno, ESD, vacio, vacio, lleno, lleno, lleno, lleno, lleno, ESD, vacio, lleno, lleno, lleno, ESD, vacio, vacio, vacio, lleno, lleno, lleno, ESD, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, lleno, lleno, ESI, HOR, HOR, HOR, HOR, EID, vacio, lleno, lleno, ESI, HOR, HOR, lleno, lleno, ESD, lleno, lleno, lleno, lleno, ESD, vacio, lleno, lleno, lleno, lleno, VER, lleno, lleno, ESI, HOR, HOR, HOR, HOR, EID);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, lleno, lleno, VER, vacio, vacio, lleno, lleno, lleno, ESD, lleno, lleno, lleno, lleno, lleno, lleno, lleno, VER, lleno, lleno, ESI, lleno, lleno, lleno, lleno, ESI, lleno, lleno, VER, lleno, lleno, lleno, lleno, lleno, ESD, vacio, vacio);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, lleno, lleno, VER, vacio, vacio, vacio, lleno, lleno, VER, lleno, lleno, ESI, HOR, HOR, lleno, lleno, VER, lleno, lleno, VER, EII, lleno, lleno, ESI, EID, lleno, lleno, VER, lleno, lleno, ESI, HOR, HOR, EID, vacio, vacio);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, EII, lleno, lleno, lleno, lleno, lleno, lleno, ESI, EID, lleno, lleno, VER, vacio, vacio, lleno, lleno, VER, lleno, lleno, VER, vacio, EII, HOR, EID, vacio, lleno, lleno, VER, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
		, vacio, EII, HOR, HOR, HOR, HOR, HOR, EID, vacio, EII, HOR, EID, vacio, vacio, EII, HOR, EID, EII, HOR, EID, vacio, vacio, vacio, vacio, vacio, EII, HOR, EID, EII, HOR, HOR, HOR, HOR, HOR, HOR, EID);

}
/**
* @brief generarFruta Crea una fruta en un punto aleatorio del mapa
* @author Magdiel Pech
* @param xFruta Coordenada x de la fruta
* @param yFruta Coordenada y de la fruta
* @param hayFruta valida si no hay otra fruta en pantalla
*/
void generarFruta(int *xFruta, int *yFruta, int *hayFruta)
{
	if (*hayFruta == 0)
	{
		*xFruta = 1 + rand() % 79;
		*yFruta = 1 + rand() % 28;
		SetCursorPosition(*xFruta, *yFruta);
		textColor(10);
		printf("%c", 4);
		*hayFruta = 1;
	}
}
/**
* @brief colisionFruta Come una fruta y aumenta el puntaje y la longitud
* @author Magdiel Pech
* @param xFruta coordenada x de la fruta
* @param yFruta Coordenada y de la fruta
* @param x Coordenada x de la cabeza de serpiente
* @param y Coordenada y de la cabeza de serpiente
* @param hayFruta Valida si hay una fruta
* @param puntaje Puntuación del jugador
* @param longitud Tamaño de la serpiente
*/
void colisionFruta(int *xFruta, int *yFruta, int *x, int *y, int *hayFruta, int *puntaje, int *longitud)
{

	if (*xFruta == *x && *yFruta == *y)
	{
		//procesoComida();
		*hayFruta = 0;
		*puntaje += 10;
		*longitud += 1;

	}

}
/**
* @brief guardarPosicion Guarda la posicion de la cabeza
* @author Magdiel Pech
* @param x Coordenada x de la cabeza
* @param y Coordenada y de la cabeza
* @param culebrita Cuerpo de la serpiente
* @param n Posicion del cuerpo donde se encuentra la cola
* @param longitud Tamaño de la serpiente
*/
void guardarPosicion(int x, int y, int culebrita[][2], int *n, int longitud)
{
	culebrita[*n][0] = x;
	culebrita[*n][1] = y;
	*n+=1;
	if (*n == longitud)
	{
		*n = 1;
	}
}
void dibujarCuerpo(int culebrita[][2], int longitud)
{
	int i = 1;
	for (i; i<longitud; i++)
	{
		SetCursorPosition(culebrita[i][0], culebrita[i][1]);
		textColor(15);
		printf("#");
	}
}
/**
* @brief borrarCuerpo Imprime un espacio en blanco en la cola de la serpiente
* @author Magdiel Pech
* @param culebrita Cuerpo de la serpiente
* @param n Posicion del cuerpo donde se encuentra la cola
*/
void borrarCuerpo(int culebrita[][2], int n)
{
	SetCursorPosition(culebrita[n][0], culebrita[n][1]);
	printf("%c",32);
}
/**
* @brief recuadroDePuntaje Muestra en pantalla las instrucciones del juego y otros datos
* @author Magdiel Pech
*/
void recuadroDePuntaje()
{
	bordes(118, 6, 80, 0);
	bordes(118, 20, 80, 6);
	bordes(118, 29, 80, 0);
	SetCursorPosition(80, 0);
	printf("%c", 203);
	SetCursorPosition(80, 29);
	printf("%c", 202);
	SetCursorPosition(80, 6);
	printf("%c", 204);
	SetCursorPosition(80, 20);
	printf("%c", 204);
	SetCursorPosition(118, 6);
	printf("%c", 185);
	SetCursorPosition(118, 20);
	printf("%c", 185);
	textColor(10);
	SetCursorPosition(90, 2);
	printf("%c %cTHE SNAKE GAME%c %c", 176, 175, 174, 176);
	textColor(10);
	SetCursorPosition(84, 4);
	printf("Universidad Autonoma de Yucatan");
	SetCursorPosition(88, 8);
	textColor(11);
	printf("%cINSTRUCCIONES DEL JUEGO%c", 175, 174);
	SetCursorPosition(86, 10);
	textColor(11);
	printf("Accion:            tecla:");
	SetCursorPosition(82, 12);
	printf("Mov arriba      flecha arriba");
	SetCursorPosition(82, 14);
	printf("Mov abajo         flecha abajo");
	SetCursorPosition(82, 16);
	printf("Mov izquierda  flecha izquierda");
	SetCursorPosition(82, 18);
	printf("Mov derecha     flecha derecha");

	SetCursorPosition(90, 22);
	textColor(7);
	printf("Puntaje: ");

	SetCursorPosition(90, 24);
	textColor(12);
	printf("Nivel: ");


}
/**
* @brief levelAndScore Aumenta el nivel del jugador y lo imprime junto con la puntuación
* @author Magdiel Pech
* @param puntaje Puntuación del jugador
* @param nivel Velocidad actual del jugador
* @param contador Nivel del jugador
*/
void levelAndScore(int *puntaje, int *nivel, int *contador)
{

	if (*contador != 0)
	{
		if (*puntaje == *contador * 100)
		{
			*nivel = *nivel - 10;
			*contador += 1;
		}
	}


	SetCursorPosition(99, 22);
	textColor(7);
	printf("%d", *puntaje);

	SetCursorPosition(97, 24);
	textColor(12);
	printf("%d", *contador);

}
/**
* @brief jugar Muestra el juego en pantalla e interactúa con el mismo
* @author César González y Magdiel Pech
* @version 2
*/
void jugar() {

	int gameOver = 1, hayFruta = 0, velocidad = 100;
	int culebrita[200][2], n = 1, longitud = 6, contadorNivel = 1;
	int xFruta, yFruta, x = 30, y = 9, direccion = derecha, puntaje = 0;
	system("cls");
	srand(time(NULL));
	bordes(118, 29, 0, 0);
	recuadroDePuntaje();

	textColor(15);
	do {
	
		levelAndScore(&puntaje, &velocidad, &contadorNivel);
		borrarCuerpo(culebrita,n);
		guardarPosicion(x,y,culebrita,&n,longitud);
		borrarCuerpo(culebrita, n);
		dibujarCuerpo(culebrita,longitud);
		borrarCuerpo(culebrita, n);
		generarFruta(&xFruta, &yFruta, &hayFruta);
		colisionFruta(&xFruta, &yFruta, &x, &y, &hayFruta, &puntaje, &longitud);
		movimientoSerpiente(&x, &y, &direccion);
		//movimientoKinect(&x,&y,&direccion);
		validarColisiones(&x, &y, &gameOver, &longitud, culebrita);
		Sleep(velocidad);

	} while (gameOver != 0);
	system("cls");
	bordes(118, 29, 0, 0);
	recuadroDePuntaje();
	levelAndScore(&puntaje, &velocidad, &contadorNivel);
	generarPuntuaciones(puntaje, contadorNivel);


}
/**
* @brief validarColisiones Valida si la serpiente choca con los bordes o consigo misma
* @author Magdiel Pech
* @param x Coordenada x de la cabeza
* @param y Coordenada y de la cabeza
* @param gameOver Continúa o finaliza el juego
* @param longitud Tamaño de la serpiente
* @param culebrita Cuerpo de la serpiente
*/
void validarColisiones(int *x, int *y, int*gameOver, int *longitud, int culebrita[][2])
{
	int i;
	if (*x == 0 || *x == 80 || *y == 0 || *y == 29)
	{
		*gameOver = 0;
		PlaySound(TEXT("muerte.wav"), NULL, SND_SYNC);

	}
	for (i = *longitud - 1; i>0; i--)
	{
		if (culebrita[i][0] == *x && culebrita[i][1] == *y)
		{
			*gameOver = 0;
			PlaySound(TEXT("muerte.wav"), NULL, SND_SYNC);
		}
	}
}
/**
* @brief movimientoSerpiente Imprime la ruta que toma la serpiente
* @author César González
* @version 2
* @param x apuntador hacia la coordenada x de la cabeza de la serpiente
* @param y apuntador hacia la coordenada y de la cabeza de la serpiente
* @param direccion apuntador hacia la dirección que tiene la serpiente
*/
void movimientoSerpiente(int *x, int *y, int *direccion) {
	int tecla;
	if (kbhit()) {
		tecla = getch();
		switch (tecla) {
		case arriba:
			if (*direccion != abajo)
				*direccion = arriba;
			break;
		case abajo:
			if (*direccion != arriba)
				*direccion = abajo;
			break;
		case izquierda:
			if (*direccion != derecha)
				*direccion = izquierda;
			break;
		case derecha:
			if (*direccion != izquierda)
				*direccion = derecha;
			break;
		}
	}
	switch (*direccion) {
	case arriba:
		*y = *y - 1;
		break;
	case abajo:
		*y = *y + 1;
		break;
	case izquierda:
		*x = *x - 1;
		break;
	case derecha:
		*x = *x + 1;
		break;
	}
}
/**
* @brief generarPuntuaciones Abre un recuadro al perder, donde se ingresa el nombre del usuario y se selecciona la siguiente acción
* @author Magdiel Pech
* @param puntaje Puntuación del jugador
* @param nivel Variable no utilizada
*/
void generarPuntuaciones(int puntaje, int nivel)
{
	int contador = 1;
	char nombre[10], leerOpcion;
	textColor(15);
	bordes(72, 22, 15, 8);
	SetCursorPosition(40, 10);
	printf("GAME OVER");
	SetCursorPosition(30, 12);
	printf("Ingresa tu nombre de usuario: \n");
	SetCursorPosition(40, 13);
	scanf("%s", nombre);
	puntajes(puntaje, nombre);
	SetCursorPosition(34, 16);
	printf("Elige una opcion:");
	textColor(10);
	bordes(40, 20, 18, 18);
	SetCursorPosition(23, 19);
	printf("Menu principal");
	textColor(15);
	bordes(70, 20, 48, 18);
	SetCursorPosition(53, 19);
	printf("Salir del juego");
	do
	{
		leerOpcion = getch();
		if (contador == 1 && leerOpcion == derecha)
		{
			contador++;
		}
		if (contador == 2 && leerOpcion == izquierda)
		{
			contador--;
		}

		switch (contador)
		{
		case 1:
			textColor(10);
			bordes(40, 20, 18, 18);
			SetCursorPosition(23, 19);
			printf("Menu principal");
			textColor(15);
			bordes(70, 20, 48, 18);
			SetCursorPosition(53, 19);
			printf("Salir del juego");
			break;
		case 2:
			textColor(15);
			bordes(40, 20, 18, 18);
			SetCursorPosition(23, 19);
			printf("Menu principal");
			textColor(10);
			bordes(70, 20, 48, 18);
			SetCursorPosition(53, 19);
			printf("Salir del juego");
			break;
		}

	} while (leerOpcion != enter);
	if (contador == 1)
	{
		PlaySound(TEXT("menus.wav"), NULL, SND_SYNC);
		menuPrincipal();
	}
}
/**
* @brief procesoComida Reproduce un sonido al comer
* @author Magdiel Pech
*/
void procesoComida()
{
	PlaySound(TEXT("comida.wav"), NULL, SND_SYNC);
}
/**
* @brief puntajes Actualiza la lista de mejores 5 puntuaciones
* @author César González
* @param nuevaPuntuacion Puntuación del último jugador
* @param nombreJugador Nombre del último jugador
*/
void puntajes(int nuevaPuntuacion, char nombreJugador[10]) {
	FILE *outFile = fopen("puntajes.txt", "r");
	FILE *auxFile = fopen("auxfile.txt", "w");
	int i, j;
	struct puntos puntuacionesTop[6], auxiliar;
	for (i = 0; i<5; i++) {
		fscanf(outFile, "%d", &puntuacionesTop[i].puntuacion);
		fscanf(outFile, "%s", puntuacionesTop[i].name);
	}
	puntuacionesTop[5].puntuacion = nuevaPuntuacion;
	strcpy(puntuacionesTop[5].name, nombreJugador);

	for (i = 0; i<5; i++) {
		for (j = 0; j<5 - i; j++)
			if (puntuacionesTop[j + 1].puntuacion>puntuacionesTop[j].puntuacion) {
				auxiliar.puntuacion = puntuacionesTop[j].puntuacion;
				strcpy(auxiliar.name, puntuacionesTop[j].name);
				puntuacionesTop[j].puntuacion = puntuacionesTop[j + 1].puntuacion;
				strcpy(puntuacionesTop[j].name, puntuacionesTop[j + 1].name);
				puntuacionesTop[j + 1].puntuacion = auxiliar.puntuacion;
				strcpy(puntuacionesTop[j + 1].name, auxiliar.name);
			}
	}

	for (i = 0; i<5; i++) {
		fprintf(auxFile, "%d\n", puntuacionesTop[i].puntuacion);
		fprintf(auxFile, "%s\n", puntuacionesTop[i].name);
	}
	fclose(outFile);
	fclose(auxFile);

	remove("puntajes.txt");
	rename("auxfile.txt", "puntajes.txt");

}
/**
* @brief top_5 Escribe "Top 5" con caracteres ASCII
* @author César González
* @param x Coordenada x inicial
* @param y Coordenada y inicial
*/
void top_5(int x, int y) {
	textColor(15);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c\n"
		, lleno, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD, vacio, lleno, lleno, lleno, lleno, lleno, lleno, ESD, vacio, lleno, lleno, lleno, lleno, lleno, lleno, ESD, vacio, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c\n"
		, EII, HOR, HOR, lleno, lleno, ESI, HOR, HOR, EID, lleno, lleno, ESI, HOR, HOR, HOR, lleno, lleno, ESD, lleno, lleno, ESI, HOR, HOR, lleno, lleno, ESD, lleno, lleno, ESI, HOR, HOR, HOR, HOR, EID);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c\n"
		, vacio, vacio, vacio, lleno, lleno, VER, vacio, vacio, vacio, lleno, lleno, VER, vacio, vacio, vacio, lleno, lleno, VER, lleno, lleno, lleno, lleno, lleno, lleno, ESI, EID, lleno, lleno, lleno, lleno, lleno, lleno, lleno, ESD);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c\n"
		, vacio, vacio, vacio, lleno, lleno, VER, vacio, vacio, vacio, lleno, lleno, VER, vacio, vacio, vacio, lleno, lleno, VER, lleno, lleno, ESI, HOR, HOR, HOR, EID, vacio, EII, HOR, HOR, HOR, HOR, lleno, lleno, VER);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c\n"
		, vacio, vacio, vacio, lleno, lleno, VER, vacio, vacio, vacio, EII, lleno, lleno, lleno, lleno, lleno, lleno, ESI, EID, lleno, lleno, VER, vacio, vacio, vacio, vacio, vacio, lleno, lleno, lleno, lleno, lleno, lleno, lleno, VER);
	SetCursorPosition(x, y);
	y++;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c\n"
		, vacio, vacio, vacio, EII, HOR, EID, vacio, vacio, vacio, vacio, EII, HOR, HOR, HOR, HOR, HOR, EID, vacio, EII, HOR, EID, vacio, vacio, vacio, vacio, vacio, EII, HOR, HOR, HOR, HOR, HOR, HOR, EID);
}

void movimientoKinect(int *x, int *y, int *direccion)
{
	char direcAr[] = "C:\\Users\\Magdiel\\Desktop\\Materias\\Proyectos\\Proyecto Snake\\PruebaProyecto\\kinect\\movimientos.txt";
	char tecla;
	FILE *fd=NULL;
	fd = fopen(direcAr, "rt");
	fscanf(fd,"%c",&tecla);
	switch (tecla) 
	{
	case 'u':
		if (*direccion != abajo)
			*direccion = arriba;
		break;
	case 'd':
		if (*direccion != arriba)
			*direccion = abajo;
		break;
	case 'l':
		if (*direccion != derecha)
			*direccion = izquierda;
		break;
	case 'r':
		if (*direccion != izquierda)
			*direccion = derecha;
		break;
	}
	switch (*direccion) 
	{
	case arriba:
		*y = *y - 1;
		break;
	case abajo:
		*y = *y + 1;
		break;
	case izquierda:
		*x = *x - 1;
		break;
	case derecha:
		*x = *x + 1;
		break;
	}
	fclose(fd);
}

