#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "omp.h"
#include <bits/stdc++.h>

using namespace std;

void participante();

vector<int> obtenerPuntajes(std::string linea);

double encontrarMediana(std::vector<int>, int size);

double encontrarPromedio(std::vector<int>, int size);

int encontrarModa(std::vector<int>, int size);

double calcularDesvEstandar(double promedio, std::vector<int>, int size);

void mostrar(double promedio, int moda, double mediana, double DesvEstandar, std::string variable);

int main(int argc, char** argv){
 if(argc>1){
  std::string ruta(argv[1]);
  std::ifstream entrada(ruta);
  std::vector<int> dnem;
  std::vector<int> dranking;
  std::vector<int> dmatematicas;
  std::vector<int> dlenguaje;
  std::vector<int> dciencias;
  std::vector<int> dhistoria;
  if(entrada){
#pragma omp parallel
    {
#pragma omp single
     {
      for(std::string linea; getline(entrada, linea);){
#pragma omp task
       {
        vector<int> puntajes = obtenerPuntajes(linea);
        if(puntajes.size() >=6){
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
#pragma omp taskwait
   }
#pragma omp parallel
  {
#pragma omp single
   {
#pragma omp task
    {   
     std::sort(dnem.begin(), dnem.end());
     double pnem=encontrarPromedio(dnem, 5015750);
     mostrar(pnem, encontrarModa(dnem, 5015750), encontrarMediana(dnem, 5015750), calcularDesvEstandar(pnem, dnem, 5015750), "nem");
     dnem.clear();
    }
#pragma omp task
    {
     std::sort(dranking.begin(), dranking.end());
     double pranking=encontrarPromedio(dranking, 5015750);
     mostrar(pranking, encontrarModa(dranking, 5015750), encontrarMediana(dranking, 5015750), calcularDesvEstandar(pranking, dranking, 5015750), "ranking");
     dranking.clear();
    }
#pragma omp task
    {
     std::sort(dmatematicas.begin(), dmatematicas.end());
     double pmatematicas=encontrarPromedio(dmatematicas, 5015750);
     mostrar(pmatematicas, encontrarModa(dmatematicas, 5015750), encontrarMediana(dmatematicas, 5015750), calcularDesvEstandar(pmatematicas, dmatematicas, 5015750), "matematicas");
     dmatematicas.clear();
    }
#pragma omp task
    {
     std::sort(dlenguaje.begin(), dlenguaje.end());
     double plenguaje=encontrarPromedio(dlenguaje, 5015750);
     mostrar(plenguaje, encontrarModa(dlenguaje, 5015750), encontrarMediana(dlenguaje, 5015750), calcularDesvEstandar(plenguaje, dlenguaje, 5015750), "lenguaje");
     dlenguaje.clear();
    }
#pragma omp task
    {
     std::sort(dciencias.begin(), dciencias.end());
     double pciencias=encontrarPromedio(dciencias, 5015750);
     mostrar(pciencias, encontrarModa(dciencias, 5015750), encontrarMediana(dciencias, 5015750), calcularDesvEstandar(pciencias, dciencias, 5015750), "ciencias");
     dciencias.clear();
    }
#pragma omp task
    {
     std::sort(dhistoria.begin(), dhistoria.end());
     double phistoria=encontrarPromedio(dhistoria, 5015750);
     mostrar(phistoria, encontrarModa(dhistoria, 5015750), encontrarMediana(dhistoria, 5015750), calcularDesvEstandar(phistoria, dhistoria, 5015750), "historia");
     dhistoria.clear();
    }
#pragma taskwait
   }
  }
     //std::cout << "Mediana: "<< encontrarMediana(dnem, 5015750) << std::endl; 
 } else {
    participante();
 }
 return EXIT_SUCCESS;
}

void participante() {
 std::cout << std::endl << "===Tarea===" << std::endl;
 std::cout << std::endl << "Rodrigo Carmona" << std::endl;
 std::cout << std::endl << "Daniel Cajas" << std::endl;
 std::cout << std::endl << "Ricardo Aliste" << std::endl;
}

double encontrarMediana(std::vector<int> arreglo, int size){
 if(size%2!=0){
  return (double)arreglo.at(size/2);
  }
 return (double) (arreglo.at((size-1)/2) + arreglo.at(size/2))/2.0;
}

double encontrarPromedio(std::vector<int> arreglo, int size){
 long suma = 0;
 for(int i=0; i<size; i++){
  suma+=arreglo.at(i);
 }
 return (double)(suma/(double)size);
}

int encontrarModa(std::vector<int> arreglo, int size){
 std::unordered_map<int, int> hash;
 for(int i=0; i<size; i++){
  hash[arreglo.at(i)]++;
 }
 int max=0, moda = arreglo.at(0);
 for(auto i : hash){
  if(max<i.second){
   moda=i.first;
   max=i.second;
  }
 }
 return moda;
}

double calcularDesvEstandar(double promedio, std::vector<int> arreglo, int size){
 double varianza;
 for(int i=0; i<size; i++){
  varianza += (arreglo.at(i) - promedio)*(arreglo.at(i) - promedio);
 }
 varianza = varianza/(double)size;
 return sqrt(varianza);
}

void mostrar(double promedio, int moda, double mediana, double desvEstandar, std::string dato){
 cout<<"==========================================="<<std::endl;
 cout<<"Variable: "<<dato<<std::endl;
 cout<<"Promedio: "<<promedio<<std::endl;
 cout<<"Moda: "<<moda<<std::endl;
 cout<<"Mediana: "<<mediana<<std::endl;
 cout<<"Desviacion Estandar: "<<desvEstandar<<std::endl;
}

vector<int> obtenerPuntajes(std::string linea) {
 vector<int> arreglo;
 std::stringstream ss(linea);
 std::string item;
 while(std::getline(ss, item, ';')) {
  int valor = atoi(item.c_str());
  arreglo.push_back(valor);
 }
 return arreglo;
}
