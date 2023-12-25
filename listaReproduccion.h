/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   listaReproduccion.h
 * Author: josep
 *
 * Created on 15 de octubre de 2023, 11:49 PM
 */

#ifndef LISTAREPRODUCCION_H
#define LISTAREPRODUCCION_H
#include <fstream>
using namespace std;

typedef struct cancion{
    char *titulo;
    char duracion[5];
}Cancion;

typedef struct nodo{
    char *nombre;
    char *artista;
    struct cancion canciones[15];
    nodo *siguiente;
    nodo *anterior;
    int cantidadCanciones;
}Album;

typedef struct{
    Album *cabeza;
    int longitud;
}ListaReproduccionAlbumes;

typedef struct{
    ListaReproduccionAlbumes lista;
    Album *reproduciendo;
}ReproductorAlbumes;

void construirPlaylist(ListaReproduccionAlbumes &Lista);
bool esListaVacia( ListaReproduccionAlbumes Ld );
Album* crearAlbum( Album *a, Album e, Album *s );
void agregarAlbum(ListaReproduccionAlbumes &Lista,Album e);
Album* ubicarUltimo( ListaReproduccionAlbumes Ld );
void eliminar( ListaReproduccionAlbumes &Ld, const char *nombreAlbum);
Album* ubicarAlbum( ListaReproduccionAlbumes Ld, const char *nombreAlbum );
char *leerCadenaExacta(ifstream &archDatos,char delimitador);
void leerDatos(ListaReproduccionAlbumes &Ld,const char *archTXT);
void mostrarCanciones(ListaReproduccionAlbumes Ld,const char *album);
void cambiarGuion(char *nombre);
void reportePlaylist(ListaReproduccionAlbumes Ld);
void mostrarLista(ListaReproduccionAlbumes Ld);
void mostrarCanciones(ListaReproduccionAlbumes Ld,const char *album);
void separador(ofstream &reporte,int cant,char c);
void cantidadTotalCanciones(ListaReproduccionAlbumes Ld);
int cantidadTotal(ListaReproduccionAlbumes Ld);
void cantidadCancionesAlbum(ListaReproduccionAlbumes Ld, const char *album);
void cancionAleatoria(ListaReproduccionAlbumes Ld);
void albumAleatorio(ListaReproduccionAlbumes Ld);
void cargarListaReproduccionAlbumes(ReproductorAlbumes &reproductor, ListaReproduccionAlbumes lista);
void iniciarReproduccion(ReproductorAlbumes &reproductor);
void iniciarFinalReproduccion(ReproductorAlbumes &reproductor);
void reproducirSiguiente(ReproductorAlbumes &reproductor);
void reproducirAnterior(ReproductorAlbumes &reproductor);
void detenerReproduccion(ReproductorAlbumes &reproductor);
void mostrarReproduciendoActualmente(ReproductorAlbumes reproductor);


//////////COLAAAAAAAAAAA/////////////
typedef struct nodoC
{
    char *nombre;
    char *artista;
    struct cancion canciones[15];
    int cantidadCanciones;
    struct nodoC *sig;  // sig es la direcciÃ³n del siguiente nodo
} NodoC;

typedef struct
{
    NodoC *frente; // frente almacena la direccion del primer nodo de la cola
    NodoC *final; // final almacena la direccion del ultimo nodo de la colaa
    int longitud; // cantidad de nodos de la cola
} ColaReproduccion;

void construir( ColaReproduccion &C );
bool esColaVacia( ColaReproduccion C );
int obtenerLongitud( ColaReproduccion C );
NodoC* crearNodoCola( Album *pAlbum,int num1,int num2, NodoC *s );
void encolar( ColaReproduccion &C, Album *pAlbum,int num1,int num2 );
void colaAlbumes(ColaReproduccion &C,ListaReproduccionAlbumes Ld,const char *album,int num1,int num2);
void mostrar( ColaReproduccion C );
void desencolar( ColaReproduccion &C );
void destruir( ColaReproduccion &C );


#endif /* LISTAREPRODUCCION_H */

