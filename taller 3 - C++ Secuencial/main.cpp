#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

void ordenar(int arreglo[])
{
    int j,k, l;
    for(j=0; j<5015750; j++)
    {
        for(k=0; k<5015750; k++)
        {
            if(arreglo[j]>arreglo[k])
            {
                l=arreglo[j];
                arreglo[j]=arreglo[k];
                arreglo[k]=l;
                printf("%i", l);
            }
        }
    }
}

int moda(int arreglo[])
{
    int contador=1, contadorf=0, numero=0;
    for(int i=1; i<5015750; i++)
    {
        if(arreglo[i]==arreglo[i-1])
        {
            contador++;
        }
        else
        {
            if(contador>contadorf)
            {
                contadorf=contador;
                contador=1;
                numero=arreglo[i-1];
            }
        }
    }
    return numero;
}

int desviacion(int arreglo[], int promedio)
{
    int operacion=0, sumatoria=0;
    for(int i=0; i<5015750; i++)
    {
        operacion=arreglo[i]-promedio;
        sumatoria+=(operacion*operacion);
        operacion=0;
    }
    operacion=sumatoria/5015749;
    operacion=sqrt(operacion);
    return operacion;
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
    int nemn,rankingn,matematicasn,lenguajen,cienciasn,historian,i; ///Variables tipo int; son para almacenar los datos unas vez pasados a entero
    int pnem,pranking, pmatematicas, plenguaje, pciencias, phistoria;  //Promedio
    int monem,moranking,momatematicas,molenguaje,mociencias,mohistoria;  //Moda
    int desnem,desranking,desmatematicas,deslenguaje,desciencias,deshistoria; //Desviacion estandar
    int mnem,mranking,mmatematicas,mlenguaje,mciencias,mhistoria; ///Medianas

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

    int* dnem=new int[5015750];
    int* dranking=new int[5015750];
    int* dlenguaje=new int[5015750];
    int* dmatematicas=new int[5015750];
    int* dciencias=new int[5015750];
    int* dhistoria=new int[5015750];

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

        dnem[i]=nemn;
        dranking[i]=rankingn;
        dlenguaje[i]=lenguajen;
        dmatematicas[i]=matematicasn;
        dciencias[i]=cienciasn;
        dhistoria[i]=historian;
        i++;

        pnem+=nemn;
        pranking+=rankingn;
        pmatematicas+=matematicasn;
        plenguaje+=lenguajen;
        pciencias+=cienciasn;
        phistoria+=historian;
    }
    pnem=pnem/5015750;
    pranking=pranking/5015750;
    plenguaje=plenguaje/5015750;
    pmatematicas=pmatematicas/5015750;
    pciencias=pciencias/5015750;
    phistoria=phistoria/5015750;

    ordenar(dnem);
    monem=moda(dnem);
    desnem=desviacion(dnem, pnem);
    mnem=dnem[2507874];
    delete[] dnem;

    ordenar(dranking);
    moranking=moda(dranking);
    desranking=desviacion(dranking, pranking);
    mranking=dranking[2507875];
    delete[] dranking;

    ordenar(dlenguaje);
    molenguaje=moda(dlenguaje);
    deslenguaje=desviacion(dlenguaje, plenguaje);
    mlenguaje=dlenguaje[2507875];
    delete[] dlenguaje;

    ordenar(dmatematicas);
    momatematicas=moda(dmatematicas);
    desmatematicas=desviacion(dmatematicas, pmatematicas);
    mmatematicas=dmatematicas[2507875];
    delete[] dmatematicas;

    ordenar(dciencias);
    mociencias=moda(dciencias);
    desciencias=desviacion(dciencias, pciencias);
    mciencias=dciencias[2507875];
    delete[] dciencias;

    ordenar(dhistoria);
    mohistoria=moda(dhistoria);
    deshistoria=desviacion(dhistoria, phistoria);
    mhistoria=dhistoria[2507875];
    delete[] dhistoria;

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
