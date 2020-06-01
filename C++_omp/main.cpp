#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "omp.h"
#include <bits/stdc++.h>

using namespace std;

//Límite superior de un arreglo que contiene 5015751 valores. Esta cifra corresponde a la cantidad de lineas que produce el programa promediador.
const int limite = 5015750;

/**
 * Función que muestra los participantes del grupo
 */
void mostrarParticipantes();

/**
 * 
 * @param linea Línea leída desde un archivo
 * @return el arreglo con los puntajes
 */
vector<int> obtenerPuntajes(std::string linea);

/**
 * 
 * @param arreglo Vector al que se realiza un recorrido
 * @param size Límite superior del vector/tamaño del vector
 * @return Mediana de los valores del vector
 */
double encontrarMediana(std::vector<int> arreglo, int size);

/**
 * 
 * @param arreglo Vector al que se realiza un recorrido
 * @param size Límite superior del vector/tamaño del vector
 * @return Promedio de los valores del vector
 */
double encontrarPromedio(std::vector<int> arreglo, int size);

/**
 * 
 * @param arreglo Vector al que se realiza un recorrido
 * @param size Límite superior del vector/tamaño del vector
 * @return Moda de los valores del vector
 */
int encontrarModa(std::vector<int> arreglo, int size);

/**
 * 
 * @param promedio Promedio de los valores del vector 'arreglo'
 * @param arreglo Vector al que se realiza un recorrido
 * @param size Límite superior del vector/tamaño del vector
 * @return Desviación estandar de los valores del vector
 */
double calcularDesvEstandar(double promedio, std::vector<int> arreglo, int size);

/**
 * Función que muestra los resultados por pantalla
 * @param promedio Promedio de los valores de 'nombre' en el archivo 'puntajes.csv'
 * @param moda Moda de los valores de 'nombre' en el archivo 'puntajes.csv'
 * @param mediana Mediana de los valores de 'nombre' en el archivo 'puntajes.csv'
 * @param DesvEstandar Desviación estandar de los valores de 'nombre' en el archivo 'puntajes.csv'
 * @param nombre Nombre de la columna de datos correspondiente del archivo puntajes.csv
 */
void mostrarResultados(double promedio, int moda, double mediana, double DesvEstandar, std::string nombre);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */

int main(int argc, char **argv)
{
    if (argc == 1) //Se verifica si la cantidad de argumentos del programa es igual a 1, en cuyo caso no se ha recibido una dirección del archivo.
    {
        cout << "No se ha entregado la dirección del archivo. Se cerrará el programa." << std::endl;
        return EXIT_FAILURE;
    }
    if (argc > 1)
    {
        std::string ruta(argv[1]); //Se guarda la dirección del archivo en un string.
        std::ifstream entrada(ruta); //Se abre el archivo desde la ruta dada.
        if (!entrada.good()) //Se verifica que el archivo ha sido abierto correctamente.
        {
            cout << "Dirección de archivo incorrecta. Se cerrará el programa" << std::endl;
            return EXIT_FAILURE;
        }
        //Inicialización de vectores de datos.
        std::vector<int> dnem;
        std::vector<int> dranking;
        std::vector<int> dmatematicas;
        std::vector<int> dlenguaje;
        std::vector<int> dciencias;
        std::vector<int> dhistoria;
        if (entrada) //Se verifica que el archivo no esté vacio. 
        { 
            {
                for (std::string linea; getline(entrada, linea);) //Se recorre cada linea del archivo.
                {
                    {
                        vector<int> puntajes = obtenerPuntajes(linea); //Los valores de cada linea se guardan en un vector de enteros.
                        if (puntajes.size() >= 6)
                        {
                            //El valor de cada columna se guarda en un vector correspondiente.
                            dnem.push_back(puntajes.at(1));
                            dranking.push_back(puntajes.at(2));
                            dmatematicas.push_back(puntajes.at(3));
                            dlenguaje.push_back(puntajes.at(4));
                            dciencias.push_back(puntajes.at(5));
                            dhistoria.push_back(puntajes.at(6));
                        }
                        puntajes.clear(); //Se borra el vector puntajes luego de que termine su función.
                    }
                }
            }
        }
#pragma omp parallel //Indica al programa que esta sección se trabajará en paralelo
        {
#pragma omp single //Una cpu inicializará las tareas, las demás las realizarán.
            {
//Se realizan tareas para cada uno de los vectores que guardan los valores del archivo origen.
#pragma omp task
                {
                    //Se usa la función sort para ordenar cada vector. Esto permite utilizar funciones sobre éstos de manera eficiente.
                    std::sort(dnem.begin(), dnem.end());
                    //Los promedios de cada vector se guardan en una variable de tipo double para ser utilizados en el cálculo de la desviación estandar.
                    double pnem = encontrarPromedio(dnem, limite);
                    //Se muestran los resultados dados según los datos obtenidos.
                    mostrarResultados(pnem, encontrarModa(dnem, limite), encontrarMediana(dnem, limite), calcularDesvEstandar(pnem, dnem, limite), "nem");
                    //Se borra el vector cuando no se necesite más.
                    dnem.clear();
                }
#pragma omp task
                {
                    std::sort(dranking.begin(), dranking.end());
                    double pranking = encontrarPromedio(dranking, limite);
                    mostrarResultados(pranking, encontrarModa(dranking, limite), encontrarMediana(dranking, limite), calcularDesvEstandar(pranking, dranking, limite), "ranking");
                    dranking.clear();
                }
#pragma omp task
                {
                    std::sort(dmatematicas.begin(), dmatematicas.end());
                    double pmatematicas = encontrarPromedio(dmatematicas, limite);
                    mostrarResultados(pmatematicas, encontrarModa(dmatematicas, limite), encontrarMediana(dmatematicas, limite), calcularDesvEstandar(pmatematicas, dmatematicas, limite), "matematicas");
                    dmatematicas.clear();
                }
#pragma omp task
                {
                    std::sort(dlenguaje.begin(), dlenguaje.end());
                    double plenguaje = encontrarPromedio(dlenguaje, limite);
                    mostrarResultados(plenguaje, encontrarModa(dlenguaje, limite), encontrarMediana(dlenguaje, limite), calcularDesvEstandar(plenguaje, dlenguaje, limite), "lenguaje");
                    dlenguaje.clear();
                }
#pragma omp task
                {
                    std::sort(dciencias.begin(), dciencias.end());
                    double pciencias = encontrarPromedio(dciencias, limite);
                    mostrarResultados(pciencias, encontrarModa(dciencias, limite), encontrarMediana(dciencias, limite), calcularDesvEstandar(pciencias, dciencias, limite), "ciencias");
                    dciencias.clear();
                }
#pragma omp task
                {
                    std::sort(dhistoria.begin(), dhistoria.end());
                    double phistoria = encontrarPromedio(dhistoria, limite);
                    mostrarResultados(phistoria, encontrarModa(dhistoria, limite), encontrarMediana(dhistoria, limite), calcularDesvEstandar(phistoria, dhistoria, limite), "historia");
                    dhistoria.clear();
                }
#pragma taskwait
            }
        }
    }
    else  //No existen argumentos que procesar, por lo que se llega al fin esperado del programa.
    {
        //Muestra los integrantes del grupo de trabajo.
        mostrarParticipantes();
    }
    return EXIT_SUCCESS;
}

void mostrarParticipantes() //Imprime los integrantes del grupo de trabajo por pantalla
{
    std::cout << std::endl
              << "===Tarea===" << std::endl;
    std::cout << std::endl
              << "Rodrigo Carmona" << std::endl;
    std::cout << std::endl
              << "Daniel Cajas" << std::endl;
    std::cout << std::endl
              << "Ricardo Aliste" << std::endl;
}

double encontrarMediana(std::vector<int> arreglo, int size)
{
    if (size % 2 != 0) //Verifica si el numero de datos es impar o no para determinar que fórmula usar.
    {
        return (double)arreglo.at(size / 2);
    }
    return (double)(arreglo.at((size - 1) / 2) + arreglo.at(size / 2)) / 2.0;
}

double encontrarPromedio(std::vector<int> arreglo, int size)
{
    long suma = 0; //La variable 'suma' debe ser de tipo long para acaparar la cantidad de datos del archivo puntajes.csv
    for (int i = 0; i < size; i++) //Se recorre el vector.
    {
        suma += arreglo.at(i); //Se suma cada dato del vector.
    }
    return (double)(suma / (double)size); //Se divide el total por la cantidad de datos, obteniendo el promedio.
    //El uso del casteo (doble) es para que el valor retornado tenga mayor precisión en los decimales.
}

int encontrarModa(std::vector<int> arreglo, int size)
{
    std::unordered_map<int, int> hash; //Se inicializa un hash table.
    for (int i = 0; i < size; i++) //Se recorre el vector.
    {
        hash[arreglo.at(i)]++; //Se agrega cada dato del vector al hash table.
    }
    int max = 0, moda = arreglo.at(0); 
    //Se inicializa una variable para guardar la cantidad máxima de valores coincidentes y otra para guardar el valor que coincide la mayor cantidad de veces.
    for (auto i : hash) //Se recorre cada rama del hash, con divisiones first (izquierda) y second (derecha).
    {
        if (max < i.second) //Si coinciden más valores para una rama determinada.
        {
            moda = i.first; //Se guarda el valor en la variable 'moda'.
            max = i.second; //Se guarda el número de coincidencias en la variable 'max'.
        }
    }
    return moda; //Se retorna el valor que coincide más veces en el vector entregado.
}

double calcularDesvEstandar(double promedio, std::vector<int> arreglo, int size)
{
    double varianza; //Esta variable guarda la variable y se utiliza para el cálculo siguiente.
    for (int i = 0; i < size; i++) //Se recorre el arreglo
    {
        varianza += (arreglo.at(i) - promedio) * (arreglo.at(i) - promedio); //Se suma cada cuadrado de diferencia entre cada dato y el promedio del vector.
    }
    varianza = varianza / (double)size; //Se obtiene la varianza dividiendo la suma obtenida por el número de datos.
    return sqrt(varianza); //Se retorna la raíz cuadrada de la varianza.
}

void mostrarResultados(double promedio, int moda, double mediana, double desvEstandar, std::string nombre)
{
    //Se imprimen los valores correspondientes por pantalla.
    cout << "===========================================" << std::endl;
    cout << "Nombre de dato: " << nombre << std::endl;
    cout << "Promedio: " << promedio << std::endl;
    cout << "Moda: " << moda << std::endl;
    cout << "Mediana: " << mediana << std::endl;
    cout << "Desviacion Estandar: " << desvEstandar << std::endl;
}

vector<int> obtenerPuntajes(std::string linea)
{
    vector<int> arreglo;
    std::stringstream ss(linea);
    std::string item;
    while (std::getline(ss, item, ';'))
    {
        int valor = atoi(item.c_str());
        arreglo.push_back(valor);
    }
    return arreglo;
}
