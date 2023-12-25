/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "listaReproduccion.h"
#define CANT 104
using namespace std;

void construirPlaylist(ListaReproduccionAlbumes &Lista){
    Lista.cabeza=NULL;
    Lista.longitud=0;
}

bool esListaVacia( ListaReproduccionAlbumes Lista ){
    return Lista.longitud==0;
}

Album* crearAlbum( Album *a, Album e, Album *s ){
    Album *p;
    p=new Album;
    p->anterior=a;
    p->siguiente=s;
    p->nombre=e.nombre;
    p->artista=e.artista;
    p->cantidadCanciones=e.cantidadCanciones;
    for(int i=0;i<e.cantidadCanciones;i++){
        p->canciones[i].titulo=e.canciones[i].titulo;
        strcpy(p->canciones[i].duracion,e.canciones[i].duracion);
    }
    return p;
}

Album* ubicarUltimo( ListaReproduccionAlbumes Ld ){
    Album *pU;
    int i;
    if( esListaVacia(Ld) )
        return NULL;
    else
    {
        pU = Ld.cabeza;
        for(i=1; i<=Ld.longitud-1; i++)
            pU = pU->siguiente;
        return pU; // devuelve la direccion el ultimo nodo
    }
}

void agregarAlbum(ListaReproduccionAlbumes &Lista,Album e){
    Album *p, *pU;
    p = crearAlbum( NULL , e , NULL);
    pU = ubicarUltimo( Lista );
    if ( pU != NULL )
    {
        pU->siguiente = p;
        p->anterior = pU;
    }
    else
        Lista.cabeza = p;
    Lista.longitud++;
}

void eliminar( ListaReproduccionAlbumes &Ld, const char *nombreAlbum){
    Album *p, *q, *a;
    if ( esListaVacia(Ld) )
        cout << "No es posible eliminar en una lista vacia" << endl;
    else
    {
        p = ubicarAlbum( Ld, nombreAlbum );
        if ( p == NULL ) // el dato no esta
            cout << "No es posible eliminar un dato inexistente" << endl;
        else
        {
            if ( p->anterior == NULL ) // es el primer nodo
            {
                Ld.cabeza = p->siguiente;
                if ( p->siguiente != NULL )
                {
                    q = p->siguiente;
                    q->anterior = NULL;
                }
            }
            else // no es el primer nodo
            {
                a = p->anterior;
                if ( p->siguiente != NULL ) // no es el ultimo
                {
                    q = p->siguiente;
                    a->siguiente = p->siguiente;
                    q->anterior = p->anterior;
                }
                else // es el ultimo nodo
                    a->siguiente = NULL;
            }
            delete p;
            Ld.longitud--;
            cout<<"Album eliminado: "<<nombreAlbum<<endl;
        }
    }
}

Album* ubicarAlbum( ListaReproduccionAlbumes Ld, const char *nombreAlbum ){
    Album *p;
    int i;
    if ( esListaVacia(Ld) )
        return NULL;
    else
    {
        p = Ld.cabeza;
        for(i=1;i<=Ld.longitud;i++)
            if ( strcmp(p->nombre,nombreAlbum)==0 )
                return p;
            else
                p = p->siguiente;
        return NULL;        
    }
}

Album* ubicarCancion( ListaReproduccionAlbumes Ld, const char *cancion ){
    Album *p;
    int i;
    if ( esListaVacia(Ld) )
        return NULL;
    else
    {
        p = Ld.cabeza;
        for(i=1;i<=Ld.longitud;i++)
            if ( strcmp(p->nombre,cancion)==0 )
                return p;
            else
                p = p->siguiente;
        return NULL;        
    }
}

char *leerCadenaExacta(ifstream &arch,char delimitador){
    char buff[500],*pt;
    arch.getline(buff,500,delimitador);
    if(arch.eof())return nullptr;
    pt=new char[strlen(buff)+1];
    strcpy(pt,buff);
    return pt;
}

void leerDatos(ListaReproduccionAlbumes &Ld,const char *archTXT){
    ifstream archDatos(archTXT,ios::in);
    if(not archDatos.is_open()){
        cout<<"ERROR al abrir el archivo de albumes"<<endl;
        exit(1);
    }
    Album album;
    char *nomAlbum,*artista,*cancion;
    char duracion[5];
    int cantidad;
    while(true){
        nomAlbum=leerCadenaExacta(archDatos,'\n');
        if(archDatos.eof())break;
        artista=leerCadenaExacta(archDatos,'\n');
        album.nombre=nomAlbum;
        album.artista=artista;
        album.cantidadCanciones=0;
        cantidad=album.cantidadCanciones;
        while(true){
            archDatos>>duracion;
            if(strcmp(duracion,"0:00")==0){
                archDatos.get();
                break;
            }
            cancion=leerCadenaExacta(archDatos,'\n');
            strcpy(album.canciones[cantidad].duracion,duracion);
            album.canciones[cantidad].titulo=cancion;
            cantidad++;
        }
        album.cantidadCanciones=cantidad;
        agregarAlbum(Ld,album);
    }
}

void cantidadTotalCanciones(ListaReproduccionAlbumes Ld){
    Album *p;
    p=Ld.cabeza;
    int contador=0;
    for(int i=0;i<Ld.longitud;i++){
        contador+=p->cantidadCanciones;
        p=p->siguiente;
    }
    cout<<"Cantidad total de canciones -> "<<contador<<endl;
    cout<<endl;
}

int cantidadTotal(ListaReproduccionAlbumes Ld){
    Album *p;
    p=Ld.cabeza;
    int contador=0;
    for(int i=0;i<Ld.longitud;i++){
        contador+=p->cantidadCanciones;
        p=p->siguiente;
    }
    return contador;
}

void cantidadCancionesAlbum(ListaReproduccionAlbumes Ld, const char *album){
    Album *p;
    int cantidad;
    p = Ld.cabeza;
    bool valido=false;
    for(int i=1;i<=Ld.longitud;i++){
        if ( strcmp(p->nombre,album)==0 ){
            cantidad=p->cantidadCanciones;
            valido=true;
            break;
        }else{
            p = p->siguiente;
        }
    }
    if(valido){
        cout<<"El album "<<album<<" cuenta con "<<cantidad<<" canciones"<<endl;
    }else{
        cout<<"No ha ingresado correctamente el nombre o no existe en la playlist"<<endl;
    }
    cout<<endl;
}

void cambiarGuion(char *nombre){
    for(int i=0;nombre[i];i++){
        if(nombre[i]=='_')nombre[i]=' ';
    }
}

void reportePlaylist(ListaReproduccionAlbumes Ld){
    Album *p;
    if ( esListaVacia(Ld) )
        cout << "La lista esta vacia" << endl;
    else
    {
        ofstream reporte("Playlist22.txt",ios::out);
        int i;
        p = Ld.cabeza;
        reporte<<setw(38)<<" "<<"Reporte de playlist de álbumes"<<endl;
        separador(reporte,CANT,'=');
        reporte<<setw(32)<<" "<<"MB's Playlist -> "<<cantidadTotal(Ld)<<" canciones, 6h 28 min"<<endl;
        separador(reporte,CANT,'-');
        reporte<<"Dedicatoria: Cada línea de este proyecto está dedicado a Maria Belen, la mujer que me enseñó que todo es"<<endl;
        reporte<<"más bonito cuando lo hacemos juntos. Asimismo, quiero conmemorar nuestro primer año juntos y estaré a la"<<endl;
        reporte<<"espera que lleguen muchos años más para seguir demostrando lo mucho que la amo."<<endl;
        separador(reporte,CANT,'-');
        reporte<<"Descripcion: Esta playlist contiene, en principio, 22 álbumes haciendo referencia a mi fecha con"<<endl;
        reporte<<"Maria Belen. Se escogieron las canciones en base a mis sentimientos hacia ella, por lo que estos"<<endl;
        reporte<<"álbumes no tienen todas sus canciones. Se pueden modificar los álbumes ya creados, agregar otros"<<endl;
        reporte<<"más incluyendo sus canciones y otras funciones que están detallados en el main."<<endl;
        separador(reporte,CANT,'=');
        reporte<<setw(3)<<" "<<"Álbum"<<setw(45)<<" "<<"Artista"<<setw(31)<<" "<<"Duración"<<endl;
        separador(reporte,CANT,'=');
        for (i=0;i<Ld.longitud;i++ )
        {
            reporte<<i+1<<") "<<p->nombre<<endl;
            for(int k=0;k<p->cantidadCanciones;k++){
                reporte<<right<<setw(3)<<" "<<k+1<<"."<<left<<setw(48)<<p->canciones[k].titulo<<setw(38);
                if(strcmp(p->artista,"Cigarettes After Sex and Artic Monkeys")==0){
                    if(k==0)reporte<<"Cigarettes After Sex"<<p->canciones[k].duracion<<endl;
                    else if(k==1)reporte<<"Cigarettes After Sex"<<p->canciones[k].duracion<<endl;
                    else reporte<<"Artic Monkeys"<<p->canciones[k].duracion<<endl;
                }else{
                    reporte<<p->artista<<p->canciones[k].duracion<<endl;
                }
            }
            p = p->siguiente;
            separador(reporte,CANT,'-');
        }
    }
}

void mostrarLista(ListaReproduccionAlbumes Ld){
    Album *p;
    if ( esListaVacia(Ld) )
        cout << "La lista esta vacia" << endl;
    else
    {
        int i;
        p = Ld.cabeza;
        cout<<"================Reporte de Lista de Reproduccion de Albumes================"<<endl;
        for (i=0;i<Ld.longitud;i++ )
        {
            cout<<i+1<<".Album: "<<p->nombre<<" - Artista: "<<p->artista<<endl;
            for(int k=0;k<p->cantidadCanciones;k++){
                cout<<"  -"<<p->canciones[k].titulo<<" ("<<p->canciones[k].duracion<<")"<<endl;
            }
            p = p->siguiente;
            cout<<endl;
        }
        cout << endl;
    }
}

void mostrarCanciones(ListaReproduccionAlbumes Ld,const char *album){
    Album *p;
    p=ubicarAlbum(Ld,album);
    if(p==NULL){
        cout<<"El album no esta escrito correctamente o no existe en la playlista"<<endl;
    }else{
        cout<<"El album "<<album<<" contiene las siguientes canciones: "<<endl;
        for(int i=0;i<p->cantidadCanciones;i++){
            cout<<i+1<<")"<<p->canciones[i].titulo<<endl;
        }
        cout<<endl;
    }
}

void separador(ofstream &reporte,int cant,char c){
    for(int i=0;i<cant;i++)reporte<<c;
    reporte<<endl;
}

void cancionAleatoria(ListaReproduccionAlbumes Ld){
    Album *p;
    int num_aleatorio=rand()%Ld.longitud;
    p=Ld.cabeza;
    for(int i=0;i<num_aleatorio-1;i++)p=p->siguiente;
    //cout<<num_aleatorio<<endl;
    //cout<<"Album seleccionado: "<<p->nombre<<endl;
    int cancion_aleatoria=rand()%p->cantidadCanciones;
    //cout<<cancion_aleatoria<<endl;
    cout<<"Cancion seleccionada: "<<p->canciones[cancion_aleatoria-1].titulo<<endl;
    cout<<endl;
}

void albumAleatorio(ListaReproduccionAlbumes Ld){
    Album *p;
    int num_aleatorio=rand()%Ld.longitud;
    p=Ld.cabeza;
    for(int i=0;i<num_aleatorio-1;i++)p=p->siguiente;
    //cout<<num_aleatorio<<endl;
    cout<<"Album seleccionado: "<<p->nombre<<endl;
    cout<<endl;
}

void cargarListaReproduccionAlbumes(ReproductorAlbumes &reproductor, ListaReproduccionAlbumes lista){
    if(esListaVacia(lista)){
        cout<<"La lista de reproduccion esta vacia"<<endl;
    }else{
        reproductor.lista=lista;
        reproductor.reproduciendo=reproductor.lista.cabeza;
    }
}

void iniciarReproduccion(ReproductorAlbumes &reproductor){
    reproductor.reproduciendo=reproductor.lista.cabeza;
    cout<<endl<<"Inicia la playlist desde el primer álbum"<<endl;
}

void iniciarFinalReproduccion(ReproductorAlbumes &reproductor){
    Album *p;
    p=ubicarUltimo(reproductor.lista);
    reproductor.reproduciendo=p;
    cout<<"Inicia la playlist desde el último álbum"<<endl;
}

void reproducirSiguiente(ReproductorAlbumes &reproductor){
    if(reproductor.reproduciendo->siguiente==NULL){
        cout<<"Se encuentra en el último álbum; por lo tanto, no hay siguiente"<<endl;
    }
    reproductor.reproduciendo=reproductor.reproduciendo->siguiente;
    cout<<"Siguiente album..."<<endl;
}

void reproducirAnterior(ReproductorAlbumes &reproductor){
    if(reproductor.reproduciendo->anterior==NULL){
        cout<<"Se llegó al primer album; por lo tanto, no hay anterior"<<endl;
    }
    reproductor.reproduciendo=reproductor.reproduciendo->anterior;
    cout<<"Anterior album..."<<endl;
}

void detenerReproduccion(ReproductorAlbumes &reproductor){
    reproductor.reproduciendo=NULL;
    cout<<"Reproduccion detenida"<<endl;
}

void mostrarReproduciendoActualmente(ReproductorAlbumes reproductor){
    cout<<"===============Álbum en reproducción==============="<<endl;
    cout<<"Album: "<<reproductor.reproduciendo->nombre<<" - Artista: "<<reproductor.reproduciendo->artista<<endl;
    //cout<<" - Cancion actual: "<<reproductor.reproduciendo->canciones[3].titulo<<endl;
    cout<<"==================================================="<<endl;
}

//COOOOOOOOOOOOOOOOOLAAAAAAAAAAAAAAA/////////
void construir( ColaReproduccion &C )
{
    // se crea la cola vacia
    C.frente= NULL;
    C.final = NULL;
    C.longitud = 0;
}

bool esColaVacia( ColaReproduccion C )
{
    return C.frente == NULL;
    // return C.final == NULL;
    // return C.longitud == 0;
}

int obtenerLongitud( ColaReproduccion C )
{
    return C.longitud;
}

NodoC* crearNodoCola( Album *pAlbum,int num1,int num2, NodoC *s )
{
    NodoC *p;
    p = new NodoC; // se crea un nodo y su direccion se almacena en p
    p->artista= pAlbum->artista;
    p->nombre= pAlbum->nombre;
    p->cantidadCanciones=num2-num1+1;
    p->sig = s;
    int inicio=num1-1,fin=num2-1;// 3   5  -  2  4   3
    for(int i=0;i<p->cantidadCanciones;i++){
        p->canciones[i].titulo=pAlbum->canciones[inicio+i].titulo;
        strcpy(p->canciones[i].duracion,pAlbum->canciones[inicio+i].duracion);
    }
    return p;  // retorna la direcciÃ³n del nodo creado
}

void encolar( ColaReproduccion &C, Album *pAlbum,int num1,int num2 )
{
    NodoC *p, *pU;
    p = crearNodoCola( pAlbum,num1,num2, NULL );
    if ( esColaVacia(C) )
        C.frente= p;
    else
    {
        pU = C.final;
        pU->sig = p;
    }
    C.final = p;
    C.longitud++;
}

void colaAlbumes(ColaReproduccion &C,ListaReproduccionAlbumes Ld,const char *album,int num1,int num2){
    Album *pAlbum;
    pAlbum=ubicarAlbum(Ld,album);
    if(pAlbum==NULL){
        cout<<"El album no esta escrito correctamente o no existe en la playlist"<<endl;
        return;
    }else{
       encolar(C,pAlbum,num1,num2);
    }
}

void mostrar( ColaReproduccion C )
{
    NodoC *p;
    if ( esColaVacia(C) )
        cout << "La cola esta vacia" << endl;
    else
    {
        int i=0;
        p = C.frente;
        cout<<endl<<"========================Cola de reproduccion de albumes========================"<<endl;
        cout<<"-------------------------------------------------------------------------------"<<endl;
        while ( p!= NULL )
        {
            cout<<i+1<<") "<< p->nombre <<endl;
            cout<<setw(3)<<" "<<"Canciones escogidas: "<<endl;
            for(int i=0;i<p->cantidadCanciones;i++){
                cout<<right<<setw(4)<<" -"<<left<<setw(48)<<p->canciones[i].titulo<<p->canciones[i].duracion<<endl;
            }
            i++;
            cout<<"-------------------------------------------------------------------------------"<<endl;
            p = p->sig;
        }
        cout <<"==============================================================================="<<endl;
    }
}

// esta funcion solo sera invocada previa verificacion de que la cola no esta vacia
void desencolar( ColaReproduccion &C )
{
    NodoC *p;
    p = C.frente;
    if ( p->sig == NULL ) // hay un solo nodo en la Cola
        C.final = NULL;
    C.frente = p->sig;
    C.longitud--;
    delete p;
}

void destruir( ColaReproduccion &C )
{
    int i;
    NodoC *p, *q;
    if ( !esColaVacia(C) )
    {
        p = C.frente;
        for(i=1; i<=C.longitud; i++)
        {
            q = p->sig;
            delete p;
            p = q;
        }
        C.frente = NULL;
        C.final = NULL;
        C.longitud = 0;
    }
}

