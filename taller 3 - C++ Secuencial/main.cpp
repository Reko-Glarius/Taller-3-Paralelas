#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

///Funcion para ordenar el arreglo; esto se hace para poder aplicar de mejor manera los calculos necesarios para obtener los
///valores requeridos
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
            }
        }
    }
}

///Funcion para calcular la moda de una de las columnas.
///Para esto se van contando la cantidad de veces que un numero aparece, cuando uno supera la cantidad maxima registrada, se
///procede a registrar el numero, y reiniciar el contador
int moda(int arreglo[])
{
    int contador=1, contadorf=0, numero=0;
    for(int i=1; i<5015750; i++)
    {
        if(arreglo[i]==arreglo[i-1]) ///Se revisa si sigue siendo el mismo numero
        {
            contador++; ///De ser el caso, el contador aumenta
        }
        else ///En el caso contrario
        {
            if(contador>contadorf) ///Se revisa si el contador es mas grande que el maximo registrado actualemnte, de serlo
            {
                contadorf=contador;  ///Se cambia la cantidad maxima registrado
                contador=1;          ///y el contador se reinicia
                numero=arreglo[i-1]; ///y finalmente se registra el valor mas repetido
            }
        }
    }
    return numero; ///Se retorna el valor resultante
}

///Funcion para calcular la desviacion estandar de una de las columnas.
///Esta es la sumatoria de todos los valores restandole el promedio, luego elevado al cuadrado; luego es restado por la
///cantidad todal de numeros menos 1. y a ese valor, le aplicamos unaraiz cuadrada
int desviacion(int arreglo[], int promedio)
{
    int operacion=0, sumatoria=0;
    for(int i=0; i<5015750; i++)
    {
        operacion=arreglo[i]-promedio;    ///Resta de valor y promedio
        sumatoria+=(operacion*operacion); ///al cuadrado
        operacion=0;
    }
    operacion=sumatoria/5015749; ///Resta de N-1
    operacion=sqrt(operacion);   ///Aplicacion de la raiz cuadrada
    return operacion; ///Retorno valor resultante
}

///Funcion para mostrar toda la informacion de una de las columnas
void mostrar(int promedio, int moda, int mediana, int desviacion_estandar, string columna)
{
    cout<<"------------------------------------------------------------------"<<endl; ///Separador
    cout<<"Columna: "<<columna<<endl;    //Nombre de la columna mostrada
    cout<<"Promedio: "<<promedio<<endl;  //Promedio de la columna seleccionada
    cout<<"Moda: "<<moda<<endl;          //Moda de la columna seleccionada
    cout<<"Mediana: "<<mediana<<endl;    //Mediana de la columna selecionada
    cout<<"Desv. Estandar: "<<desviacion_estandar<<endl;  ///Desviacion estandar de la columna seleccionada
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
    ///Se crean arreglos dinamicos para cada columna del archivo
    int* dnem=new int[5015750];          ///Arreglo dinamico de "NEM"
    int* dranking=new int[5015750];      ///Arreglo dinamico de "RANKING"
    int* dlenguaje=new int[5015750];     ///Arreglo dinamico de "LENGUAJE"
    int* dmatematicas=new int[5015750];  ///Arreglo dinamico de "MATEMATICAS"
    int* dciencias=new int[5015750];     ///Arreglo dinamico de "CIENCIAS"
    int* dhistoria=new int[5015750];     ///Arreglo dinamico de "HISTORIA"

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
        
        ///Se añade el respectivo valor de una de las columnas a su respectiva posicion en su respectivo arreglo
        dnem[i]=nemn;
        dranking[i]=rankingn;
        dlenguaje[i]=lenguajen;
        dmatematicas[i]=matematicasn;
        dciencias[i]=cienciasn;
        dhistoria[i]=historian;
        i++; ///Variable para ir cambiando de posicion los arreglos

        ///Se va realizando una sumatoria de cada valor de cada columna, esto para psteriormente calcular el promedio
        pnem+=nemn;
        pranking+=rankingn;
        pmatematicas+=matematicasn;
        plenguaje+=lenguajen;
        pciencias+=cienciasn;
        phistoria+=historian;
    }
    
    ///Se procede a dividir las sumatorias por el total de valores, para obtener los promedios
    pnem=pnem/5015750;
    pranking=pranking/5015750;
    plenguaje=plenguaje/5015750;
    pmatematicas=pmatematicas/5015750;
    pciencias=pciencias/5015750;
    phistoria=phistoria/5015750;

    ///Se utilia la funcion "ordenar" para ordenar de manera ascendente los vaores del cada arreglo.
    ///ya con el arreglo ordenado, es posible obtener la moda, desviacion estandar y mediana mediante las respectivas funciones
    ///En el caso de la mediana, como la cantidad de datos es par, se toman los 2 en el medio, se suman entre ellos y se divide en 2
    ordenar(dnem);
    monem=moda(dnem);
    desnem=desviacion(dnem, pnem);
    mnem=(dnem[2507874]+dnem[2507875])/2;
    delete[] dnem; ///Se elimina el arreglo para "NEM", para liberar memoria

    ordenar(dranking);
    moranking=moda(dranking);
    desranking=desviacion(dranking, pranking);
    mranking=(dranking[2507875]+dranking[2507875])/2;
    delete[] dranking; ///Se elimina el arreglo para "RANKING", para liberar memoria

    ordenar(dlenguaje);
    molenguaje=moda(dlenguaje);
    deslenguaje=desviacion(dlenguaje, plenguaje);
    mlenguaje=(dlenguaje[2507875]+dlenguaje[2507875])/2;
    delete[] dlenguaje; ///Se elimina el arreglo para "LENGUAJE", para liberar memoria

    ordenar(dmatematicas);
    momatematicas=moda(dmatematicas);
    desmatematicas=desviacion(dmatematicas, pmatematicas);
    mmatematicas=(dmatematicas[2507875]+dmatematicas[2507875])/2;
    delete[] dmatematicas; ///Se elimina el arreglo para "MATEMATICAS", para liberar memoria

    ordenar(dciencias);
    mociencias=moda(dciencias);
    desciencias=desviacion(dciencias, pciencias);
    mciencias=(dciencias[2507875]+dciencias[2507875])/2;
    delete[] dciencias; ///Se elimina el arreglo para "CIENCIAS", para liberar memoria

    ordenar(dhistoria);
    mohistoria=moda(dhistoria);
    deshistoria=desviacion(dhistoria, phistoria);
    mhistoria=(dhistoria[2507875]+dhistoria[2507875])/2;
    delete[] dhistoria; ///Se elimina el arreglo para "HISTORIA", para liberar memoria

    ///Se procede a mostrar toda la informacion de cada columna
    mostrar(pnem,monem,mnem,desnem,"NEM");
    mostrar(pranking,moranking,mranking,desranking,"RANKING");
    mostrar(plenguaje,molenguaje,mlenguaje,deslenguaje,"LENGUAJE");
    mostrar(pmatematicas,momatematicas,mmatematicas,desmatematicas,"MATEMATICAS");
    mostrar(pciencias,mociencias,mciencias,desciencias,"CIENCIAS");
    mostrar(phistoria,mohistoria,mhistoria,deshistoria,"HISTORIA");

    ///Se finaliza mostrando a los integrantes del grupo desarrollador
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"Integrantes"<<endl;
    cout<<"Ricardo Aliste"<<endl;
    cout<<"Daniel Cajas"<<endl;
    cout<<"Rodrigo Carmona"<<endl;

}
