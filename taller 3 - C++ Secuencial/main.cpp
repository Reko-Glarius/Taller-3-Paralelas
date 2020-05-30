#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

int mid(int matriz[3][5])
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

int mayor(int matriz[3][5])
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

void preparar(int matriz[3][5])
{
    int n=450;
    for(int i=0; i<5; i++)
    {
        matriz[0][i]=n;
        matriz[1][i]=n+59;
        matriz[2][i]=0;
        n+=60;
    }
}

void posicionar(int matriz[3][5], int numero)
{
    if(matriz[1][0]>=numero && numero>=matriz[0][0])
    {
        matriz[2][0]=matriz[2][0]+1;
    }
    if(matriz[1][1]>=numero && numero>=matriz[0][1])
    {
        matriz[2][1]=matriz[2][1]+1;
    }
    if(matriz[1][2]>=numero && numero>=matriz[0][2])
    {
        matriz[2][2]=matriz[2][2]+1;
    }
    if(matriz[1][3]>=numero && numero>=matriz[0][3])
    {
        matriz[2][3]=matriz[2][3]+1;
    }
    if(750>=numero && numero>=matriz[0][4])
    {
        matriz[2][4]=matriz[2][4]+1;
    }
}

int promedio(int matriz[3][5])
{
    int sumatoria=0;
    int x, f;
    for(int i=0; i<5; i++)
    {
        x=matriz[0][i]+30;
        f=matriz[2][i];
        sumatoria+=((x*f)/5015752);
    }
    return sumatoria;
}

int moda(int matriz[3][5])
{
    int posicion=mayor(matriz);
    int A=60, numero_resultante=0;
    int f0,f1,f2,L;
    if(posicion==0)
    {
        f0=0;
        f1=matriz[2][0];
        f2=matriz[2][1];
        L=matriz[0][0];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==1)
    {
        f0=matriz[2][0];
        f1=matriz[2][1];
        f2=matriz[2][2];
        L=matriz[0][1];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==2)
    {
        f0=matriz[2][1];
        f1=matriz[2][2];
        f2=matriz[2][3];
        L=matriz[0][2];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==3)
    {
        f0=matriz[2][2];
        f1=matriz[2][3];
        f2=matriz[2][4];
        L=matriz[0][3];
        numero_resultante=((f1-f0)/((f1-f0)+(f1-f2)))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==4)
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
    int posicion=mid(matriz);
    int A=60, numero_resultante=0, n=5015752/2;
    int F,f,L;
    if(posicion==0)
    {
        F=0;
        f=matriz[2][0];
        L=matriz[0][0];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==1)
    {
        F=matriz[2][0];
        f=matriz[2][1];
        L=matriz[0][1];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==2)
    {
        F=matriz[2][1]+matriz[2][0];
        f=matriz[2][2];
        L=matriz[0][2];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==3)
    {
        F=matriz[2][2]+matriz[2][1]+matriz[2][0];
        f=matriz[2][3];
        L=matriz[0][3];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
    if(posicion==4)
    {
        F=matriz[2][3]+matriz[2][2]+matriz[2][1]+matriz[2][0];;
        f=matriz[2][4];
        L=matriz[0][4];
        numero_resultante=((n-F)/(f))*A;
        numero_resultante=numero_resultante+L;
        return numero_resultante;
    }
}

int desviacion(int matriz[3][5], int promedio)
{
    int sumatoria=0, numero;
    int f, n;
    sumatoria=0;
    for(int i=0; i<5; i++)
    {
        f=matriz[2][i];
        n=(matriz[0][i])+30;
        numero=pow(n-promedio, 2);
        sumatoria+=((f*numero)/5015751);
    }
    printf("\n");
    numero=sqrt(sumatoria);
    return numero;
}

void mostrar(int promedio, int moda, int mediana, int desviacion_estandar, string columna)
{
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"Columna: "<<columna<<endl;
    cout<<"Promedio: "<<promedio<<endl;
    cout<<"Moda: "<<moda<<endl;
    cout<<"Mediana: "<<mediana<<endl;
    cout<<"Desv. Estandar: "<<desviacion_estandar<<endl;
}

int main(int argc, char *argv[])
{
    std::string rut,nem,ranking,matematicas,lenguaje,ciencias,historia; ///Variable tipo string; son utilizadas para guardar datos
    int nemn,rankingn,matematicasn,lenguajen,cienciasn,historian; ///Variables tipo int; son para almacenar los datos unas vez pasados a entero
    int pnem=0,pranking=0, pmatematicas=0, plenguaje=0, pciencias=0, phistoria=0, i=1;  //Promedio
    int monem,moranking,momatematicas,molenguaje,mociencias,mohistoria;  //Moda
    int desnem,desranking,desmatematicas,deslenguaje,desciencias,deshistoria; //Desviacion estandar
    int mnem,mranking,mmatematicas,mlenguaje,mciencias,mhistoria; ///Medianas

    int dnem[3][5];
    preparar(dnem);

    int dranking[3][5];
    preparar(dranking);

    int dlenguaje[3][5];
    preparar(dlenguaje);

    int dmatematicas[3][5];
    preparar(dmatematicas);

    int dciencias[3][5];
    preparar(dciencias);

    int dhistoria[3][5];
    preparar(dhistoria);

    if(argc==1) //If que verifica que se envio almenos un argumento; en caso de que no se enviase ningun, cierra el programa
    {
        cout<<"Error. Direccion del archivo no enviada\n\nCerrando APP por motivos de seguridad"<<endl;
        exit(1); ///Funcion interna de C/C++; permite cerrar el programa si recibe un entero 1
    }

    ifstream archivo(argv[1]); ///Funcion para abrir el archivo de texto, en funcion de la direccion enviada por argumento
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

        posicionar(dnem, nemn);
        posicionar(dranking, rankingn);
        posicionar(dlenguaje, lenguajen);
        posicionar(dmatematicas, matematicasn);
        posicionar(dciencias, cienciasn);
        posicionar(dhistoria, historian);

    }

    pnem=promedio(dnem);
    pranking=promedio(dranking);
    plenguaje=promedio(dlenguaje);
    pmatematicas=promedio(dmatematicas);
    pciencias=promedio(dciencias);
    phistoria=promedio(dhistoria);

    monem=moda(dnem);
    desnem=desviacion(dnem, pnem);
    mnem=mediana(dnem);

    moranking=moda(dranking);
    desranking=desviacion(dranking, pranking);
    mranking=mediana(dranking);

    molenguaje=moda(dlenguaje);
    deslenguaje=desviacion(dlenguaje, plenguaje);
    mlenguaje=mediana(dlenguaje);

    momatematicas=moda(dmatematicas);
    desmatematicas=desviacion(dmatematicas, pmatematicas);
    mmatematicas=mediana(dmatematicas);

    mociencias=moda(dciencias);
    desciencias=desviacion(dciencias, pciencias);
    mciencias=mediana(dciencias);

    mohistoria=moda(dhistoria);
    deshistoria=desviacion(dhistoria, phistoria);
    mhistoria=mediana(dhistoria);

    mostrar(pnem,monem,mnem,desnem,"NEM");
    mostrar(pranking,moranking,mranking,desranking,"RANKING");
    mostrar(plenguaje,molenguaje,mlenguaje,deslenguaje,"LENGUAJE");
    mostrar(pmatematicas,momatematicas,mmatematicas,desmatematicas,"MATEMATICAS");
    mostrar(pciencias,mociencias,mciencias,desciencias,"CIENCIAS");
    mostrar(phistoria,mohistoria,mhistoria,deshistoria,"HISTORIA");

    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"Integrantes"<<endl;
    cout<<"Ricardo Aliste"<<endl;
    cout<<"Daniel Cajas"<<endl;
    cout<<"Rodrigo Carmona"<<endl;
}
