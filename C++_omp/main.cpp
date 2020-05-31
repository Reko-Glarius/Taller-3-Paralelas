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
    if (argc == 1)
    {
        cout << "No se ha entregado la dirección del archivo. Se cerrará el programa." << std::endl;
        return EXIT_FAILURE;
    }
    if (argc > 1)
    {
        std::string ruta(argv[1]);
        std::ifstream entrada(ruta);
        if (!entrada.good())
        {
            cout << "Dirección de archivo incorrecta. Se cerrará el programa" << std::endl;
            return EXIT_FAILURE;
        }
        std::vector<int> dnem;
        std::vector<int> dranking;
        std::vector<int> dmatematicas;
        std::vector<int> dlenguaje;
        std::vector<int> dciencias;
        std::vector<int> dhistoria;
        if (entrada)
        { 
            {
                for (std::string linea; getline(entrada, linea);)
                {
                    {
                        vector<int> puntajes = obtenerPuntajes(linea);
                        if (puntajes.size() >= 6)
                        {
                            dnem.push_back(puntajes.at(1));
                            dranking.push_back(puntajes.at(2));
                            dmatematicas.push_back(puntajes.at(3));
                            dlenguaje.push_back(puntajes.at(4));
                            dciencias.push_back(puntajes.at(5));
                            dhistoria.push_back(puntajes.at(6));
                        }
                        puntajes.clear();
                    }
                }
            }
        }
#pragma omp parallel
        {
#pragma omp single
            {
#pragma omp task
                {
                    std::sort(dnem.begin(), dnem.end());
                    double pnem = encontrarPromedio(dnem, limite);
                    mostrarResultados(pnem, encontrarModa(dnem, limite), encontrarMediana(dnem, limite), calcularDesvEstandar(pnem, dnem, limite), "nem");
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
    else
    {
        mostrarParticipantes();
    }
    return EXIT_SUCCESS;
}

void mostrarParticipantes()
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
    if (size % 2 != 0)
    {
        return (double)arreglo.at(size / 2);
    }
    return (double)(arreglo.at((size - 1) / 2) + arreglo.at(size / 2)) / 2.0;
}

double encontrarPromedio(std::vector<int> arreglo, int size)
{
    long suma = 0;
    for (int i = 0; i < size; i++)
    {
        suma += arreglo.at(i);
    }
    return (double)(suma / (double)size);
}

int encontrarModa(std::vector<int> arreglo, int size)
{
    std::unordered_map<int, int> hash;
    for (int i = 0; i < size; i++)
    {
        hash[arreglo.at(i)]++;
    }
    int max = 0, moda = arreglo.at(0);
    for (auto i : hash)
    {
        if (max < i.second)
        {
            moda = i.first;
            max = i.second;
        }
    }
    return moda;
}

double calcularDesvEstandar(double promedio, std::vector<int> arreglo, int size)
{
    double varianza;
    for (int i = 0; i < size; i++)
    {
        varianza += (arreglo.at(i) - promedio) * (arreglo.at(i) - promedio);
    }
    varianza = varianza / (double)size;
    return sqrt(varianza);
}

void mostrarResultados(double promedio, int moda, double mediana, double desvEstandar, std::string nombre)
{
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
