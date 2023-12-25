/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: josep
 *
 * Created on 15 de octubre de 2023, 11:46 PM
 */

#include <iostream>
#include "listaReproduccion.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    ListaReproduccionAlbumes Playlist;
    construirPlaylist(Playlist);
    leerDatos(Playlist,"AlbumesYCanciones.txt");//se ingresan los albumes y sus canciones desde un archivo .txt
    
    /*muestra la playlist en la ventana OutPut(abajo)*/
    //mostrarLista(Playlist);
    
    /*imprime el reporte de la playlist en un archivo .txt*/
    reportePlaylist(Playlist);
    
    /*La funcion muestra las canciones de un album. El primer parametro siempre sera la lista.
    El segundo parametro,luego de la coma, se coloca el nombre del album que se quiere mostrar. 
    Debe ir siempre entre comillas y escrito tal cual como se muestra en el reporte*/
    mostrarCanciones(Playlist,"Take Me Home");
    
    /*Muestra la cantidad total de canciones de toda la playlist*/
    cantidadTotalCanciones(Playlist);
    
    /*Muestra la cantidad de canciones que contiene el album indicado.
     Se usa el mismo formato que la funcion mostrarCanciones.*/
    cantidadCancionesAlbum(Playlist,"Mi Sangre");
    
    /*Se escoge una cancion aleatoria de toda la playlist
     Si se quiere otra cancion aleatoria, copiar cancionAleatoria(Playlist),
     pegarla debajo de esta misma y ejecutar con la flecha verde.*/
    cancionAleatoria(Playlist);
    
    /*Se escoge un album aleatorio de toda la playlist
     Si se quiere otro album aleatorio, copiar albumAleatorio(Playlist),
     pegarlo debajo de este mismo y ejecutar con la flecha verde.*/
    albumAleatorio(Playlist);

    /*Se simula la reproduccion de la playlist por medio de los albumes
     Todas las canciones de cada album seran reproducidas*/
    ReproductorAlbumes reproductor;
    cargarListaReproduccionAlbumes(reproductor,Playlist);
    iniciarReproduccion(reproductor);//Se inicia la playlist desde el primer album
    
    /*La funcion reproducirSiguiente avanza hacia el siguiente album
      Si quieres darle al siguiente nuevamente, debes copiar y pegar la funcion debajo de esta misma*/
    reproducirSiguiente(reproductor);
//    reproducirSiguiente(reproductor);
//    reproducirSiguiente(reproductor);
//    reproducirSiguiente(reproductor);
    
    /*La funcion reproducirAnterior retrocede un album
      Si quieres retroceder nuevamente, debes copiar y pegar la funcion debajo de esta misma*/
//    reproducirAnterior(reproductor);
    
    /*La funcion muestra el album que se esta reproduciendo/*
    mostrarReproduciendoActualmente(reproductor);
    
    /*
     La cola de reproduccion simula la fila de reproduccion de spotify.
     En este caso, puedes agregar los albumes que deseas escuchar con el rango
     de las canciones que deseas añadir (las posiciones de las canciones se pueden
     observar en las funciones mostrarLista y reportePlaylist)
     */
    ColaReproduccion MB;
    construir(MB);
    /*La funcion colaAlbumes se maneja de la siguiente manera:
     *Los dos primeros parametros no se deben tocar. 
     *El tercer parametro sirve para ingresar el nombre del album que se quiera agregar a la cola de reproduccion.
      Se coloca entre comillas y de la misma manera en que aparecen en los reportes.
     *El cuarto y quinto parametro sirven para colocar el rango de las canciones a añadir.
      El cuarto parametro indica desde que posicion se quiere agregar, mientras que el 
      quinto parametro indica hasta que posicion se debe agregar.
     *Se han colocado dos ejemplos, los cuales seran mostrados luego de ejecutar el programa,
      en la ventana Output(abajo).
     */
    colaAlbumes(MB,Playlist,"Take Me Home",3,5);
    colaAlbumes(MB,Playlist,"Mi Sangre",2,4);
    colaAlbumes(MB,Playlist,"Cigarettes After Sex and Artic Monkeys Mix",1,4);
    
    //Funcion que muestra la cola de reproduccion
    mostrar(MB); 
    
    
    return 0;
}

