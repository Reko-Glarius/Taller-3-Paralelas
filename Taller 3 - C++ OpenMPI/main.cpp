#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <mpi.h>

using namespace std;

int mid(int matriz[3][5]) ///Funcion para encontrar el punto donde se encuentra la mitad de los datos (dato para calcular mediana)
{
    int n=5015752/2, numero=0;
    for(int i=0; i<5; i++)
    {
        numero+=matriz[2][i];
        if(numero>=n)
        {
            return i;
        }
    }

}

int mayor(int matriz[3][5]) ///Funcion que retorna la posicion de la tabla de datos donde se encuentran la mayor cantidad de datos
{
    int nposicion=0;
    for(int i=0; i<5; i++)
    {
        if(matriz[2][i]>nposicion)
        {
            nposicion=i;
        }
    }
    return nposicion;
}

void preparar(int matriz[3][5]) ///Funcion para inicializar la tabla de datos
{
    int n=450;
    for(int i=0; i<5; i++)
    {
        matriz[0][i]=n;    ///Limite Inferior
        matriz[1][i]=n+59; ///Limite superiro
        matriz[2][i]=0;    ///Cantidad de datos en el intervalo
        n+=60;
    }
}

void posicionar(int matriz[3][5], int numero) ///Funcion para almacenar datos segun su posicion en la tabla
{
    if(matriz[1][0]>=numero && numero>=matriz[0][0]) ///Rango 1: 450-509
    {
        matriz[2][0]=matriz[2][0]+1; ///Se almacena los datos (forma se repite en los demas rangos)
    }
    if(matriz[1][1]>=numero && numero>=matriz[0][1]) ///Rango 2: 510-569
    {
        matriz[2][1]=matriz[2][1]+1;
    }
    if(matriz[1][2]>=numero && numero>=matriz[0][2]) ///Rango 3: 570-629
    {
        matriz[2][2]=matriz[2][2]+1;
    }
    if(matriz[1][3]>=numero && numero>=matriz[0][3]) ///Rango 4: 630-689
    {
        matriz[2][3]=matriz[2][3]+1;
    }
    if(750>=numero && numero>=matriz[0][4])          ///Rango 5: 690-750
    {
        matriz[2][4]=matriz[2][4]+1;
    }
}

int promedio(int matriz[3][5]) ///Funcion que retorna el promedio de una de las tablas de datos
{
    unsigned long long sumatoria=0; ///Variable donde se iran sumando los datos
    int x, f; //Varaibles a utilizar segun formula
    for(int i=0; i<5; i++)
    {
        x=matriz[0][i]+30;  ///marca de clases (el punto medio entre limite inferior y superiror)
        f=matriz[2][i];     ///Cantidad total de elementos dentro del rango de datos
        sumatoria+=((x*f)); ///Se realiza una sumatoria del valor resultante de X*f
    }
    return (sumatoria/5015752); ///Se retorna finalmente el valor total de la sumatoria, dividido por el numero de elementos
}

int moda(int matriz[3][5]) ///Funcion para calcular la moda de una tabla de datos
{
    int posicion=mayor(matriz);    ///Se obtiene la posicion donde se encuentra la mayoria de los datos
    int A=60, numero_resultante=0; ///A es la amplitud del intervalo, el cual es 60
    int f0,f1,f2,L;  ///Variables a utilizar para calcular la moda
    if(posicion==0) ///Para el intervalo 1
    {
        f0=0;            ///Cantidad de datos en el rango anteriro
        f1=matriz[2][0]; ///Cantidad de datos en el rango actual
        f2=matriz[2][1]; ///Cantidad de datos en el rango Siguiente
        L=matriz[0][0];  ///Limite inferior del actual rango de datos
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A; ///Se calcula la diferencia entre la cantidad de datos y la cant. actual; luego de multiplica por la amplitud
        numero_resultante=numero_resultante+L; ///Luego del calculo anterior, se le suma el limite inferior del rango actual
        return numero_resultante;  ///Finalmente se retorna el valor resultante; estas operaciones se realizan para cada caso
    }
    if(posicion==1) ///Para el intervalo 2
    {
        f0=matriz[2][0];
        f1=matriz[2][1];
        f2=matriz[2][2];
        L=matriz[0][1];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==2) ///Para el intervalo 3
    {
        f0=matriz[2][1];
        f1=matriz[2][2];
        f2=matriz[2][3];
        L=matriz[0][2];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==3) ///Para el intervalo 4
    {
        f0=matriz[2][2];
        f1=matriz[2][3];
        f2=matriz[2][4];
        L=matriz[0][3];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==4) ///Para el intervalo 5
    {
        f0=matriz[2][3];
        f1=matriz[2][4];
        f2=0;
        L=matriz[0][4];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
}

int mediana(int matriz[3][5])
{
    int posicion=mid(matriz); ///Se obtiene la posicion en la cual se encuentra la mitad del total de datos
    int A=60, numero_resultante=0, n=5015752/2; ///A es la amplitud, n es la mitad de la cantidad total de datos
    int F,f,L; ///Variables para el calculo
    if(posicion==0) ///Para el intervalo 1
    {
        F=0;            ///Cantidad de datos en el rango anteriro
        f=matriz[2][0]; ///Cantidad de datos en el rango actual
        L=matriz[0][0]; ///Limite inferior de datos en el rango actual
        numero_resultante=((n-F)/(f))*A;       ///Luego se calcula la diferencia entre n y F; luego se divide por f; y se mult. por A
        numero_resultante=numero_resultante+L; ///Luego se le suma el limite inferior del rango actual
        return numero_resultante; ///Finalmente se retorna el valor resultante; estas operaciones se realizan para cada caso
    }
    if(posicion==1) ///Para el intervalo 2
    {
        F=matriz[2][0];
        f=matriz[2][1];
        L=matriz[0][1];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==2) ///Para el intervalo 3
    {
        F=matriz[2][1]+matriz[2][0];
        f=matriz[2][2];
        L=matriz[0][2];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==3) ///Para el intervalo 4
    {
        F=matriz[2][2]+matriz[2][1]+matriz[2][0];
        f=matriz[2][3];
        L=matriz[0][3];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==4) ///Para el intervalo 5
    {
        F=matriz[2][3]+matriz[2][2]+matriz[2][1]+matriz[2][0];;
        f=matriz[2][4];
        L=matriz[0][4];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
}

int desviacion(int matriz[3][5], int promedio) {  ///Funcion para calcular la desviacion estandar
    unsigned long long sumatoria = 0, numero = 0; ///Variables para la calculacion de la formula
    for (int i=0; i<5; i++)
    {
        int f=matriz[2][i];      ///Cantidad de datos del rango actual de datos
        int n=(matriz[0][i])+30; ///Marca de clase del rango actual de datos
        numero=(unsigned long long)pow((n-promedio), 2); ///se calcula la diferencia entre f y el promedio de la tabla de datos, y se eleva al cuadrado el resultado
        unsigned long long valor=(f*numero); ///Luego se multiplica por f
        sumatoria+=valor; ///Este valor resultante se van sumando entre si contantemente
    }
    return (int)sqrt(sumatoria/ 5015751); ///Y finalmente se regresa el resultado de aplicarle una raiz cuadrada a la division de la sumatoria con el total de datos
}

void mostrar(int promedio, int moda, int mediana, int desviacion_estandar, string columna) ///Funcion para mostrar todos los datos de cada columnda
{
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"Columna: "<<columna<<endl;   ///Nombre de la columna (ejemplo: NEM)
    cout<<"Promedio: "<<promedio<<endl; ///Promedio de la columna
    cout<<"Moda: "<<moda<<endl;         ///Moda de la columna
    cout<<"Mediana: "<<mediana<<endl;   ///Mediana de la columna
    cout<<"Desv. Estandar: "<<desviacion_estandar<<endl; ///Desviacion estandar de la columna
}

int main(int argc, char *argv[])
{
    int mi_rango; /* rango del proceso    */
    int p; /* numero de procesos   */
    int fuente; /* rango del que envia  */
    int dest; /* rango del que recibe */
    int tag = 0; /* etiqueta del mensaje */
    char mensaje[100];

    MPI_Status estado;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    std::string rut,nem,ranking,matematicas,lenguaje,ciencias,historia; ///Variable tipo string; son utilizadas para guardar datos
    int nemn,rankingn,matematicasn,lenguajen,cienciasn,historian; ///Variables tipo int; son para almacenar los datos unas vez pasados a entero
    int pnem=0,pranking=0, pmatematicas=0, plenguaje=0, pciencias=0, phistoria=0, i=1;  //Variables para almacenar los promedios
    int monem,moranking,momatematicas,molenguaje,mociencias,mohistoria;  //Variables para almacenar las moda
    int desnem,desranking,desmatematicas,deslenguaje,desciencias,deshistoria; //Variables para almacenar la desviacion estandar
    int mnem,mranking,mmatematicas,mlenguaje,mciencias,mhistoria; ///Variables para almacenar las medianas

    int dnem[3][5]; ///Tabla de datos de NEM
    preparar(dnem); ///Se inicializa la tabla de datos (esta accion se repite para cada tabla)

    int dranking[3][5]; ///Tabla de datos de Ranking
    preparar(dranking);

    int dlenguaje[3][5]; ///Tabla de datos de Lenguaje
    preparar(dlenguaje);

    int dmatematicas[3][5]; ///Tabla de datos de Matematicas
    preparar(dmatematicas);

    int dciencias[3][5]; ///Tabla de datos de Ciencias
    preparar(dciencias);

    int dhistoria[3][5]; ///Tabla de datos de Historia
    preparar(dhistoria);

    if(argc==1) //If que verifica que se envio almenos un argumento; en caso de que no se enviase ningun, cierra el programa
    {
        cout<<"Error. Direccion del archivo no enviada\n\nCerrando APP por motivos de seguridad"<<endl;
        //exit(1); ///Funcion interna de C/C++; permite cerrar el programa si recibe un entero 1
    }

    ifstream archivo("puntajes.csv"); ///Funcion para abrir el archivo de texto, en funcion de la direccion enviada por argumento
    if(!archivo.good()) ///Funcion de los archivos; permite reconocer si el archivo se abri de manera exitosa; el if es para que, en caso de no abrirse correctamente, se cierre el programa
    {
        cout<<"Archivo ingresado de manera erronea, recuerde que debe enviarse con doble '\' para reconocer la direccion"<<endl;
        exit(1);
    }

    while(!archivo.eof()) ///Ciclo while con funcion propia de los archivos; la funcion detecta si termino el archivo o no; el while permite sacar linea por linea hasta llegar al final del documento
    {
        ///Funciones para poder obtener cada fragmento de cada linea del archivo; en cada uno se guarda su respectivo dato en una variable string
        getline(archivo,rut,';');
        getline(archivo,nem,';');
        getline(archivo,ranking,';');
        getline(archivo,matematicas,';');
        getline(archivo,lenguaje,';');
        getline(archivo,ciencias,';');
        getline(archivo,historia,'\n');

        ///Funciones para poder obtener el valor como entero de un string
        std::istringstream(nem) >> nemn;
        std::istringstream(ranking) >> rankingn;
        std::istringstream(matematicas) >> matematicasn;
        std::istringstream(lenguaje) >> lenguajen;
        std::istringstream(ciencias) >> cienciasn;
        std::istringstream(historia) >> historian;

        ///Se almacena cada datos numerico en la posicion que le corresponde dentro de su respectiva tabla de datos
        posicionar(dnem, nemn);
        posicionar(dranking, rankingn);
        posicionar(dlenguaje, lenguajen);
        posicionar(dmatematicas, matematicasn);
        posicionar(dciencias, cienciasn);
        posicionar(dhistoria, historian);

    }
    int numero=0
    if (mi_rango != 0) {
        if(numero=0)
        {
            string datos="Promedio:"+to_string(promedio(dnem))+"\nModa:"+to_string(moda(dnem))+"\Mediana:"+to_string(mediana(dnem))+"\Desv. Estandar:"+to_string(desviacion(dnem, promedio(dnem)))+"\n";
        }
        if(numero=1)
        {
            string datos="Promedio:"+to_string(promedio(dranking))+"\nModa:"+to_string(moda(dranking))+"\Mediana:"+to_string(mediana(dranking))+"\Desv. Estandar:"+to_string(desviacion(dranking, promedio(dranking)))+"\n";
        }
        if(numero=2)
        {
            string datos="Promedio:"+to_string(promedio(dlenguaje))+"\nModa:"+to_string(moda(dlenguaje))+"\Mediana:"+to_string(mediana(dlenguaje))+"\Desv. Estandar:"+to_string(desviacion(dlenguaje, promedio(dlenguaje)))+"\n";
        }
        if(numero=3)
        {
            string datos="Promedio:"+to_string(promedio(dmatematicas))+"\nModa:"+to_string(moda(dmatematicas))+"\Mediana:"+to_string(mediana(dmatematicas))+"\Desv. Estandar:"+to_string(desviacion(dmatematicas, promedio(dmatematicas)))+"\n";
        }
        if(numero=4)
        {
            string datos="Promedio:"+to_string(promedio(dciencias))+"\nModa:"+to_string(moda(dciencias))+"\Mediana:"+to_string(mediana(dciencias))+"\Desv. Estandar:"+to_string(desviacion(dciencias, promedio(dciencias)))+"\n";
        }
        if(numero=5)
        {
            string datos="Promedio:"+to_string(promedio(dhistoria))+"\nModa:"+to_string(moda(dhistoria))+"\Mediana:"+to_string(mediana(dhistoria))+"\Desv. Estandar:"+to_string(desviacion(dhistoria, promedio(dhistoria)))+"\n";
        }
        MPI_Send(mensaje, strlen(mensaje) + 1, MPI_CHAR,dest, tag, MPI_COMM_WORLD);
    }
    else { /* mi_rango == 0 */
        for (fuente = 1; fuente < p; fuente++) {
            MPI_Recv(mensaje, 100, MPI_CHAR, fuente,tag, MPI_COMM_WORLD, &estado);
            printf("%s\n", mensaje);
        }
    }
    MPI_Finalize();
    cout<<"------------------------------------------------------------------"<<endl;
    ///Se procede a mostrar los nombres de los integrantes del grupo
    cout<<"Integrantes"<<endl;
    cout<<"Ricardo Aliste"<<endl;
    cout<<"Daniel Cajas"<<endl;
    cout<<"Rodrigo Carmona"<<endl;
    return EXIT_SUCCESS;
}
