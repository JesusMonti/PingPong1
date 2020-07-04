#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
//Dimensiones del tablero(constates)
#define V 21
#define H 75

using namespace std;
void inicio(char campo[V][H],int pelX , int pelY, int inijug, int finjug, int iniia, int finia);
void borde(char campo[V][H]);
void raqjug (char campo[V][H],  int inijug,int finjug);
void raqia (char campo[V][H],  int iniia,int finia);
void pel(char campo[V][H],int pelX, int pelY);
void leerCampo(char campo[V][H]);
void gameloop(char campo[V][H],int pelX, int pelY, int inijug, int finjug, int iniia, int finia, int modX, int modY, int modia);
void draw(char campo[V][H]);
void input(char campo[V][H],int *pelX,int * pelY,int *inijug, int *finjug, int *iniia, int *finia,int *modX, int *modY, int *modia,int *gol);
void update(char campo[V][H],int pelX , int pelY, int inijug, int finjug, int iniia, int finia);
int main()
{
    // Variables de inicializacion y posicion
    int pelX,pelY;//Varibles de la pelota
    int inijug,finjug;//Donde inica la raquera 1
    int iniia,finia;//Posion computadora
    char campo[V][H];

    //Variables del movimiento
    int modX, modY,modia;

    //Ubicamos la pelota en el centro del tablero
    pelX = 37;
    pelY = 10;
    //Posicion inicial del jugador uno
    inijug = 8;
    finjug = 12;

    //Posicion inicial del PC/jugador 2
    iniia = 8;
    finia = 12;

    //Variables de modificacion
    modX = -1;
    modY = -1;
    modia = 1;
    cout << "Let's go to play... " << endl;
    inicio(campo,pelX, pelY, inijug, finjug, iniia, finia);
    gameloop(campo,pelX, pelY, inijug, finjug, iniia, finia, modX, modY, modia);
    leerCampo(campo);
    return 0;
}

void inicio(char campo[V][H],int pelX , int pelY, int inijug, int finjug, int iniia, int finia){
    borde (campo);
    raqjug (campo,inijug,finjug);
    raqia (campo,iniia,finia);
    pel(campo,pelX,pelY);
}
void borde(char campo[V][H])
{
    int i,j;
    for( i = 0; i < V; i++)
    {
        for( j = 0; j < H; j++)
        {
            if(i==0){
                campo[i][j]='v';
            }else if(i==V-1)
            {
                campo[i][j]='^';
            }else if(j==0 || j==H-1){
                campo[i][j]='|';
            }else{
                campo[i][j]=' ';
            }

        }
    }

}
void raqjug (char campo[V][H],  int inijug,int finjug)
{
    int i,j;
    for(i=inijug;i < finjug; i++)
    {
        for(j=2;j<=3; j++)
        {
            campo[i][j]='*';
        }
    }
}
void raqia (char campo[V][H],  int iniia,int finia)
{
    int i,j;
    for(i=iniia;i < finia; i++)
    {
        for(j = H -4; j<= H -3; j++)
        {
            campo[i][j]='*';
        }
    }
}

void pel(char campo[V][H],int pelX, int pelY){
    campo[pelY][pelX]='O';
}

void leerCampo(char campo[V][H]){
    int i,j;
    for(i=0;i < V; i++)
    {
        for(j=0;j <H; j++)
        {
            printf("%c",campo[i][j]);
        }
        printf("\n");
    }
}

void gameloop(char campo[V][H],int pelX, int pelY, int inijug, int finjug, int iniia, int finia, int modX, int modY, int modia)
{
    int gol=0;

    do{
        draw(campo);//Dibujar en pantalla
        // Se realiza el pasao por parametros para que se actualice en la variable del tablero
        input(campo,&pelX,&pelY,&inijug, &finjug, &iniia, &finia,&modX, &modY, &modia,&gol);//Lee las entradas
        update(campo,pelX, pelY, inijug, finjug, iniia, finia);//Actualizar la matriz campo
        Sleep(50);//detiene a la CPU, el tiempo es en ms
    }while(gol == 0 );
}
void draw(char campo[V][H])
{
    system("cls");//borra pantalla
    leerCampo(campo);
}

void input(char campo[V][H],int *pelX,int * pelY,int *inijug, int *finjug, int *iniia, int *finia,int *modX, int *modY, int *modia,int *gol)
{
    int i;
    char mov1;
    //Revisamos la ubicación de la pelota
    //Si la pelota llega a la posicion vertical 1 o V-2, la pelota rebota
    if( *pelY == 1 || *pelY == V-2)
    {
        *modY *=-1;//Se invierte la posicion de desplazamiento vertical
    }
    //Si la pelota llega a la posicion horizontal 1 o H-2, es gol
    if ( *pelX == 1 || *pelX == H-2 )
    {
        *gol=1;
    }
    if ( *pelX == 4 || *pelX == H-2 )
    {
        *gol=1;
    }
    //Revisamos si la pelota choca al jugador 1 rebota
    if (*pelX == 3)
    {
        for( i = (*inijug); i<= (*finjug); i++)
        {
            if( i == (*pelY))
            {
                *modX *= -1;
            }
        }
    }
    //Revisamos si la pelota choca al jugador 2
    if (*pelX == H-5)
    {
        for( i = (*iniia); i<= (*finia); i++)
        {
            if( i == (*pelY))
            {
                *modX *= -1;
            }
        }
    }
    //Posicion cuando el cpu llega a una orilla
    if ( *iniia == 2 || *finia == V-1)
    {
        *modia *= -1;
    }

    if( *gol == 0 ){
        //Pelota movimiento
        *pelX += (*modX);
        *pelY += (*modY);

        //Raqueta CPU
        *iniia += (*modia);
        *finia += (*modia);

        //Raqueta Jug
        if(kbhit() == 1){
            mov1 = getch();
            if (mov1 == '8'){
                if(*inijug != 1){
                    *inijug -= 1;
                    *finjug -= 1;
                }
            }
            if (mov1 == '2'){
                if(*finjug != V-2){
                    *inijug += 1;
                    *finjug += 1;
                }
            }
        }

    }
}

void update(char campo[V][H],int pelX , int pelY, int inijug, int finjug, int iniia, int finia)
{
    borde (campo);
    raqjug (campo,inijug,finjug);
    raqia (campo,iniia,finia);
    pel(campo,pelX,pelY);
}
