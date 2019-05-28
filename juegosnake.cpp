#include <iostream>
#include <windows.h>
#include <conio.h>
#include<stdlib.h>
#include <ctime>
#include <cstdio>
#include <thread>

#define UP 72
#define IZQ 75
#define DER 77
#define DOWN 80
#define ESC 27
#define ENTER 13
#define SPACE 32

/*@author Izquierdo Moran Luis Humberto
@author Mata Franco María Fernanda
@author Rivas Guillen Axel
@author Velazquez Ruiz Maritrini
@Docente Raymundo Cornejo
*/

using namespace std;
/*Aqui declaramos las variables principales que se utilizan a lo largo del codigo.
Vemos que como son globales tienen alcance para en todo el codigo.Se almacenan en el Stack*/

int cuerpo[200][2]; /*Es el límite que tiene el cuerpo de la víbora*/
char tecla;
int n=1, tam = 3, x=10, y=12,h=1;
int dir=3, vel=120, xc=30, yc=15, score=0,ans,highscore;
void pausa();
bool stargame=false, bandera=false;;
int opc;

/*
	@param int x, sirve para posicionar la coordenada en X
	@param int y, Posición de la coordenada en Y
	 En el handle ... hCon es solo el nombre que se le puso pero se pude poner cualquier
nombre. coord es la que se encarga de colocar las variables x y y en las posiciones
deseeadas, dwPos.X es para definir las coordenadas de x despues y lo mismo con dwPos.Y
el SetConsole.. recibe los valores de x y y */

void goTo(int x, int y){
	HANDLE hCon;
	COORD dwPos;

	dwPos.X= x;
	dwPos.Y=y;
	hCon= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

/*
@param Const Char txt, sirve para pintar el texto
Estas dos funciones son para ubicar un texto en ciertas cordenadas de la consola
una recibe los parámetros de un string y la otra recibe los parámetros de
las coordenadas de x y y en donde se quiere ubicar el texto */
void Say(const char *txt){
	printf("%s",txt);
}
/*
@param int x
@param int y
@param const char txt
Esta función sirve para pintar el texto y solo recibe un parámetro del 0- 12 */
void Say(int x,int y,const char *txt){
	goTo(x,y);printf("%s",txt);
}
/*
@param int color
Esta función va pintando el contorno del juego donde están los límites y se utilizan los caractéres
del código ascii*/
void TextColor(int color){
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*Esta Función se encarga de pintar el margen límite
donde se moverá la serpiente, mandamos llamar la función anterior, TextColor */
void pintar(){

	//lineas horizontales
	TextColor(10);
	for(int i=2; i<78;i++){
		goTo(i,3);
		printf("%c",205);

		goTo(i,23);
		printf("%c",205);
	}
	//lineas verticals
	for(int i=4; i<23;i++){
		goTo(2,i);
		printf("%c",186);
		goTo(77,i);
		printf("%c",186);
	}
	//Esquinas
		goTo(2,3);printf("%c",201);
		goTo(2,23);printf("%c",200);
		goTo(77,3);printf("%c",187);
		goTo(77,23);printf("%c",188);
}

/* Va guardando la posición de la serpiente */
void guardar(){
	cuerpo[n][0]=x;
	cuerpo[n][1]=y;
	n++;
	if (n==tam)n=1;
}

/* Pinta el cuerpo para que vaya apareciendo cada '*' conforme va creciendo y va recorriendo cada
bolita con el for y lo va ubicando con la función de goTo que es para ubicarla en las coordenadas */
void pintarpuerco(){
	for(int i=1;i<tam;i++){
		TextColor(rand()%12 + 1);
		goTo(cuerpo[i][0],cuerpo[i][1]);

		printf("*");
	}
}

/* Va borrando el cuerpo para que se cree la ilusión de que se va moviendo y lo que en realidad hace
es que cada que se va moviendo se pone un '*' enfrente y se borra el último que no sea igual al tamano
de la serpiente*/
void borrar(){
	goTo(cuerpo[n][0],cuerpo[n][1]);
	printf(" ");

}

/* Esta función es la que nos permite que la serpiente se pueda mover, con un switch y la variable tecla
ubicas que cada tecla que ya se definió arriba como las flechas para mover, y la variable dir
es para hacer que cuando se mueva hacia arriba no puedas bajar bruscamente y lo mismo con la izquierda
y la derecha */
void mover(){
	if(kbhit()){
	 	tecla=getch();
	 		switch (tecla){
	 			case UP :

	 			if(dir!=2)
	 				dir=1;
	 				break;
	 			case DOWN:

	 			if(dir!=1)
	 				dir=2;
	 				break;
	 			case DER :
	 			if (dir !=4)
	 				dir =3;
	 				break;
	 			case IZQ:
	 			if(dir!= 3)
	 				dir =4;
	 				break;

			 }
		 }
}

/* Esta función hace que la velocidad vaya aumentando para que su dificultad aumente igual, la variable
h es solo una variable que se creó para esta función que es solo para hacer mas fácil el aumento de la
velocidad asi la velocidad aumenta en 20, y el valor de la vel disminuye que entre mas lento vaya
mas rápido se mueve la snake */
void camVel(){
	/*cada vez que se alcancen los puntos limite h aumentará
	y asi aumentara cada 20 la velocidad*/
	if(score == h*20){
		vel-= 10;
		h++;
	}
}

/* @throw se lanza una excepción cuando la variable score sea igual a la misma,
esta va a entrar a catch y seguirá apareciendo la comida, lo utilizamos porque después de que el puntaje
fuera 120 la comida dejaba de aparecer.

Esta función hace que los puntos de comida aparezcan en algún lugar random del mapa y
explica que cada que la posición de la snake es la misma que la del punto pues el tamano del cuerpo
aumenta y el score también aumenta en 10, se utiliza la función goTo para ubicar la comida y se
manda a llamar la función camVel para que se vaya aumentando la velicidad conforme aumenta el score
se utiliza una excepción ya que habiamos tenido problemas al llegar a la puntuación y dejaban
de salir los puntos de comida y pusimos que cuando el score sea apareciera otro punto de comida
 y se volviera a repetir todo para que no pase eso de que dejaran de salir */
void comida(){
	if(x==xc && y== yc){
	xc=(rand()%71)+4;
	yc=(rand()%19)+4;

	tam++;
	score +=10;
	goTo(xc,yc);printf("%c",254);
	camVel();
	}
	try{
		if(score == score)
		throw (254);

	}catch(...){
		if(x==xc && y== yc){
		xc=(rand()%72)+4;
		yc=(rand()%19)+4;
		tam++;
		score +=10;
		goTo(xc,yc);printf("%c",254);
		camVel();
		}
	}
}

/* Esta función es para que el juego acabe que sería cuando chocas con las paredes del mapa y el for es
para que recora el cuerpo de la snake y si llega a chocar con ella misma se pueda contar tambien
como un game over
@delete Se implement[o para liberar la memor[ia del arreglo del cuerpo
*/
bool gameOver(){
	//dimensiones del área de juego
	if(y==3 || y==23|| x==2  || x==77 ){
		TextColor(12);
		Say(34,12,"GAME OVER");
		return false;
		exit(1);
		delete []cuerpo;

	}
	//para revisar el cuerpo de arriba hacia abajo
	for(int j=tam-1; j>0; j--){
		if(cuerpo[j][0]==x && cuerpo [j][1]==y)
			return false;

	}
	return true;

}

/* Esta función solo es para que aparezca el score en la esquina y lo este registrando */
void punto(){
	goTo (3,1);
	printf("SCORE: %d",score);
}

/*@Thread hilouno se utilizó el hilo para hacer concurrente la función de pintar el cuerpo.
Esta función es la principal de todas es para que el juego inicie y haga todo, aqui se mandan a
llamar a casi todas las funciones, primero se manda a llamar pintar para que se pinte todo el mapa
y el primer punto que vaya a aparecer, despues en el do while dice que siempre se va a estar ejecutando
mientras no se este presionando la tecla de ESC y mientras no entre al gameOver, y lo que hara es que
mandara a llamar a las funciones que hace que se muevan la snake, utilizamos hilos para que al pintar
el cuerpo de la snake se haga al mismo tiempo que aparezca la comida, despues se manda a llamar la
funcion punto que es para que aparezca el score, y el poner dos veces la funcion de mover es porque
tarda un poco en lo que entra y se realiza algun movimiento entonces no se se podian hacer movimientos
bruscos degrirar rápido y al ponerla dos veces ya se puede hacaer eso, en los if es para que cuando
se mueva en las direcciones correspondientes de arriba, abajo etc, se aumente o disminuya el valor de
x o de y y eso es que lo hace que se pueda mover la snake, el sleep es una función de c++ para que avance
lo que dice en la variable vel que sería lo que se mueve cada ciertos milisegundos */
void start(){

	pintar();
	//se pinta la primera bolita de comida
	goTo(xc,yc);printf("%c",254);

	while(tecla !=ESC  && gameOver()){
	 	borrar();
	 	guardar();
	 	std:: thread hilouno(pintarpuerco);
	 	comida();
	 	hilouno.join();

	 	punto();
	 	//se pone dos veces para mover para que se pueda mover mas fácil

		mover();
		mover();

		if(dir==1) y--;
		if(dir==2) y++;
		if(dir==3) x++;
		if(dir==4) x--;

	 	Sleep(vel);
	 }
	pintar();

}

/* El main lo intentamos dejar lo más simple y vacio posible que por eso solo se manda a llamar la
función de start que es la principal */
int main(){
	std::thread uno(start);
	uno.join();
	return 0;
}
