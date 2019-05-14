#include <iostream>
#include <windows.h>
#include <conio.h>
#include<stdlib.h>

#define UP 72
#define IZQ 75
#define DER 77
#define DOWN 80
#define ESC 27

int cuerpo[200][2];

//saber pa que sirve este pedo
void goTo(int x, int y){
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X= x;
	dwPos.Y=y;
	hCon= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

void pintar(){
	//lineas horizontales
	for(int i=2; i<78;i++){
		goTo(i,3);
		printf("%c",205);
		
		
		goTo(i,16);
		printf("%c",249);
		
		goTo(i,23);
		printf("%c",205);
	}
	//lineas verticlaes
	for(int i=4; i<23;i++){
		goTo(2,i);
		printf("%c",186);
		goTo(77,i);
		printf("%c",186);
	}
	//Esquiiiiinas
		goTo(2,3);printf("%c",201);
		goTo(2,23);printf("%c",200);
		goTo(77,3);printf("%c",187);
		goTo(77,23);printf("%c",188);
}

int main(){
/*	
	for(int j=0;j<3;j++){
		for(int i=0; i<2;i++){
			cuerpo[j][i]=rand()%10;
		}
		
	}*/	
/*		
	cuerpo[0][0]=3;
	cuerpo[0][1]=5;
	
	cuerpo[1][0]=4;
	cuerpo[1][1]=5;
	
	cuerpo[2][0]=5;
	cuerpo[2][1]=5;
		
	for(int j=0;j<3;j++){
		goTo(cuerpo[j][0],cuerpo[j][1]);
		printf("%c",220);
				
	}
*/
	 
	pintar();
	system("PAUSE>NULL");
	return 0;
}
