/*



                                    INTEGRANTES
                WALTER DAVID ESTUPIÑAN CASTILLO y LUIS DAVID ARIAS ISAZA
                Codigos:      1230089           y      12300022          
                                IS03D1 - 2024-1



*/

#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;

// FIFO
struct pasajero {

    //caracteristicas de los pasajeros
    int cc;
    char nombre[50];
    char apellido[50];
    long long destinoP;
    pasajero *sigP;
};

struct pasajero *cabP, *auxP, *aux2P;

// Árbol
struct nodo {


    // para definir niveles
    int altura;

    //caracyeristicas del nodo
    int precioDelViaje;
    char destino[30];
    long long matriculaEembarcacion;
    long long matriculaOriginal;
    char nombreEmbarcacion[25];
    long long identificador;
    int capacidadEmabarcacion;
    int dia;
    int mes;
    int year;
    nodo *izq;
    nodo *der;
};

nodo *raiz, *aux, aux2;

/* Rotaciones y funciones AVL */
//---------------------------------------INICIO AVL BALANCEO-------------------------------------------------


/* NOTAS A TENER EN CUENTA:

un nodo tiene un peso de 1 si el subarbol DERECHO es más alto DERECHO = 1
-1 si su subarbol IZQUIERDO es mas alto IZQUIERDO = -1
0 si ambos subarboles tienen la misma altura IGUALES = 0

el equilibrio se calcula teniendo en cuenta la altura derecha y su direfencia con la altura izquierda
(Equilibrio = AlturaDerecha - AlturaIzquierda) básicamente

si se obtiene un numero positivo el lado derecha es más alto
            numeros posibles (-1, 0, 1)
si se obtiene un numero negativo el lado izquierdo es más alto

si en alguno de los pesos de los nodos se modifica en un valor no valido
por (2 o -2) debe seguirse un esquema de rotacion

Casos de rotaciones:

RSI(Rotacion Simple Izquierda): si esta desequilibrado a la izquierda y el hijo der tiene el mismo signo (+) se hace una rotacion sencilla hacia la izquierda

RSD(Rotacion Simple Derecha): si esta desequilibrado a la derecha y el hijo izq tiene el mismo signo (-) se hace una rotacion sencilla hacia la derecha

RDI(Rotacion Doble Izquierda): se aplica cuando tienen signos diferentes en los nodos y su factor de equilibrio es menor que -1 (es decir, -2)
se hace rotacion doble izquierda-derecha es ir intercalando las rotaciones simples anteriormente definidas en el codigo

RDD(Rotacion Doble Derecha): se aplica cuando tienen signos diferentes en los nodos y su factor de equilibrio es mayor que 1 (es decir, 2)
se hace rotacion doble derecha-izquierda es ir intercalando las rotaciones simples anteriormente definidas en el codigo*/

int mayor(int a, int b){
    return (a > b) ? a : b;
}

int obtenerAltura(struct nodo *n){
    if (n == NULL) {
        return 0;
    }
    return n->altura;
}

int obtenerBalance(struct nodo *n){
    if (n == NULL) {
        return 0;
    }
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

struct nodo* rotarDerecha(struct nodo *y){
    struct nodo *x = y->izq;
    struct nodo *T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

struct nodo* rotarIzquierda(struct nodo *x){
    struct nodo *y = x->der;
    struct nodo *T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

struct nodo* insertar(struct nodo* nodo){
    if (nodo == NULL) {
        return aux;
    }

    if (aux->identificador < nodo->identificador) {
        nodo->izq = insertar(nodo->izq);
    } else if (aux->identificador > nodo->identificador) {
        nodo->der = insertar(nodo->der);
    } else {
        return nodo;
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && aux->identificador < nodo->izq->identificador) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->identificador > nodo->der->identificador) {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && aux->identificador > nodo->izq->identificador) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->identificador < nodo->der->identificador) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

//---------------------------------------FIN AVL BALANCEO-------------------------------------------------




void registrarViaje(){
    cout<<"\tBienvenido a la seccion de registrar viaje!" << endl;
    cout<<"" << endl;
    cout<<"\t(Por favor, llene las siguientes preguntas para completar el registro)" << endl;
    cout<<"-------------------------------------------" << endl;

    aux = (struct nodo *)malloc(sizeof(struct nodo));

    cout<<"\tIngrese el destino del viaje: "<<endl;
    cout<<"\t--> "; cin>>aux->destino;

    cout<<"\tIngrese precio del viaje: "<<endl;
    cout<<"\t--> $"; cin>>aux->precioDelViaje;

    cout<<"\tIngrese nombre de la embarcacion: "<<endl;
    cout<<"\t--> "; cin>>aux->nombreEmbarcacion;

    cout<<"\tIngrese la matricula de la embarcacion: "<<endl;
    cout<<"\t--> "; cin>>aux->matriculaEembarcacion;

    cout<<"\tIngrese la capacidad maxima de la embarcacion: "<<endl;
    cout<<"\t--> "; cin>>aux->capacidadEmabarcacion;

    cout<<"\tIngrese dia del viaje: "<<endl;
    cout<<"\t--> "; cin>>aux->dia;

    cout<<"\tIngrese mes del viaje: "<<endl;
    cout<<"\t--> ";cin>>aux->mes;

    cout<<"\tIngrese year del viaje: "<<endl;
    cout<<"\t--> ";cin>>aux->year;

    aux->matriculaOriginal = aux->matriculaEembarcacion;

    while(aux->matriculaEembarcacion >= 100){
        aux->matriculaEembarcacion=aux->matriculaEembarcacion / 10;
    }

    aux->identificador = aux->matriculaEembarcacion * 100000000 + aux->year * 10000 + aux->mes * 100 + aux->dia * 1;

    cout<<"-------------------------------------------"<<endl;
    cout<<"\t¡Viaje registrado con exito!"<<endl;
    cout<<"-------------------------------------------"<<endl;

    cout<<"\tIdentificador unico del viaje es el sigueinte: #"<<aux->identificador<<endl;
    cout<<"-------------------------------------------"<<endl;

    aux->izq = NULL;
    aux->der = NULL;

    //incrementa
    aux->altura = 1;
}

void buscarViaje(){
    if(raiz==NULL){
        cout<<"-------------------------------------------"<<endl;
        cout<<"\tNo hay viajes registrados."<<endl;
        cout<<"-------------------------------------------"<<endl;
        return;
    } else {
        long long id;
        cout<<"\tIngrese el identificador del viaje a buscar: ";
        cin>>id;

        aux = raiz;

        while (aux != NULL) {
            if (aux->identificador == id) {
                cout<<"-------------------------------------------"<<endl;
                cout<<"\tDetalles del viaje:"<<endl;
                cout<<"\tDestino: "<<aux->destino<<endl;
                cout<<"\tPrecio: $" << aux->precioDelViaje<<endl;
                cout<<"\tNombre de la embarcacion: "<<aux->nombreEmbarcacion<<endl;
                cout<<"\tMatricula de la embarcacion: "<<aux->matriculaOriginal<<endl;
                cout<<"\tCapacidad de la embarcacion: "<<aux->capacidadEmabarcacion<<endl;
                cout<<"\tFecha: " << aux->dia << "/" << aux->mes << "/" << aux->year<<endl;
                cout<<"-------------------------------------------"<<endl;
                return;
            } else if (id < aux->identificador) //buscar a la izquierda
                aux = aux->izq;
            else //buscar a la derecha
                aux = aux->der;
        }
        cout << "-------------------------------------------" << endl;
        cout << "\tViaje no encontrado." << endl;  //no se encontró el nodo
    }
}
//mostrar en inorden (ATS) - busca a profundidad el subarbol izquierdo, imprime la raiz y por ultimo pasa al lado derecho
void inorden(nodo *raiz){
    if (raiz != NULL) {
        inorden(raiz->izq);//primero izquierda (menosre)
        cout<<"\tIdentificador: "<<raiz->identificador<<", Destino: "<<raiz->destino //raiz
            <<", Precio: $"<<raiz->precioDelViaje<<", Capacidad: "<<raiz->capacidadEmabarcacion<<endl;
        cout<<"-------------------------------------------"<<endl;
        inorden(raiz->der);//luego derecha (mayores)
    }
}

void listarViaje(){
    cout<<"-------------------------------------------"<<endl;
    cout<<"\tListado de todos los viajes:"<<endl;
    cout<<"-------------------------------------------"<<endl;
    if (raiz == NULL){
        cout<<"\tNo hay viajes registrados."<<endl;
    } else{
        inorden(raiz);//funcion inorden
    }
    cout<<"-------------------------------------------"<<endl;
}

nodo* eliminarNodo(nodo* raiz, int id) {
    if (raiz == NULL) return raiz;

    if (id < raiz->identificador)
        raiz->izq = eliminarNodo(raiz->izq, id);
    else if (id > raiz->identificador)
        raiz->der = eliminarNodo(raiz->der, id);
    else {
        if (raiz->izq == NULL) {
            nodo *temp = raiz->der;
            free(raiz);
            return temp;
        } else if (raiz->der == NULL) {
            nodo *temp = raiz->izq;
            free(raiz);
            return temp;
        }

        nodo* temp = raiz->der;
        while (temp->izq != NULL)
            temp = temp->izq;

        raiz->identificador = temp->identificador;
        raiz->der = eliminarNodo(raiz->der, temp->identificador);
    }

// BALANCEO
    if (raiz == NULL) return raiz;

    raiz->altura = 1 + mayor(obtenerAltura(raiz->izq), obtenerAltura(raiz->der));

    int balance = obtenerBalance(raiz);

    if (balance > 1 && obtenerBalance(raiz->izq) >= 0)
        return rotarDerecha(raiz);

    if (balance > 1 && obtenerBalance(raiz->izq) < 0) {
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }

    if (balance < -1 && obtenerBalance(raiz->der) <= 0)
        return rotarIzquierda(raiz);

    if (balance < -1 && obtenerBalance(raiz->der) > 0) {
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }

    return raiz;
}
//FINALIZA EL BALANCEO Y RETORNA A LA RAIZ

void eliminarViaje(){
    if (raiz == NULL){ //cuando la raiz esta vacia
        cout<<"-------------------------------------------"<<endl;
        cout<<"\tNo hay viajes registrados."<<endl;
    } else{
        int id;
        cout<<"\tIngrese el identificador del viaje a eliminar: ";
        cin>>id;

        raiz = eliminarNodo(raiz, id);//llama a la funciona anteriormente realizada para eliminar un viaje, con el balanceo hecho anteriormente en la funcion
        cout<<"-------------------------------------------"<<endl;
        cout<<"\tViaje eliminado exitosamente."<<endl;
    }
}

bool existeViaje(nodo *raiz, long long id){ //para verificar la existencia del viAje en el arbol por medio de la raiz
    if (raiz == NULL) return false; //falso
    if (raiz->identificador == id) return true; //si es igual retorna verdadero
    if (id < raiz->identificador) return existeViaje(raiz->izq, id); //si es menor llama a la funcion con la raiz izquierda
    return existeViaje(raiz->der, id);//si es mayor llama a la funcion con la raiz derecha
}

void registrarPasajeros(){
    if (raiz == NULL) {//el arbol esta vacio   
        cout<<"\tNo hay viajes registrados. Registre un viaje primero."<<endl;
        return;
    }

    listarViaje();//funcion para listar los viajes en inorden

    long long idViaje;
    cout<<"\tIngrese el identificador de viaje: ";
    cin>>idViaje;

    if(!existeViaje(raiz, idViaje)){ //cuqando es falso o distinto
        cout<<"\tEl identificador de viaje no existe. Intente de nuevo."<<endl;
        return;
    }

    auxP = (struct pasajero *)malloc(sizeof(struct pasajero));

    cout<<"\tIngrese su nombre: ";
    cin>>auxP->nombre;

    cout<<"\tIngrese su apellido: ";
    cin>>auxP->apellido;

    cout<<"\tIngrese su identificacion: ";
    cin>>auxP->cc;

    auxP->destinoP = idViaje;
    auxP->sigP = NULL;

//Insertar
    if(cabP == NULL){ //cuando la lista esta vacia
        cabP = auxP;//se crea un nuevo nodo
    }else{
        aux2P = cabP;//se crea un puntero auxiliar para ir recorriendo la lista
        while (aux2P->sigP != NULL) {//mientras no sea el final de la lista
            aux2P = aux2P->sigP;//se avanza en la lista
        }
        aux2P->sigP = auxP;//se agrega el nuevo nodo al final de la lista
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"\t¡Pasajero registrado exitosamente!"<<endl;
    cout<<"-------------------------------------------"<<endl;
}

void listarPasajeros(){
    if (cabP == NULL){
        cout<<"-------------------------------------------"<<endl;
        cout<<"\tNo hay pasajeros registrados."<<endl;
        cout<<"-------------------------------------------"<<endl;
        return;
    }

    listarViaje();//funcion para listar los viajes en inorden

    long long idViaje;

    cout<<"\tIngrese el identificador de viaje para listar sus pasajeros: ";
    cin>>idViaje;

    if(!existeViaje(raiz, idViaje)){ //cuando sea falso o distinto
        cout<<"\tEl identificador de viaje no existe. Intente de nuevo."<<endl;
        return;
    }

    auxP = cabP;
    bool buscar = false; //se inicializa como falso para verificar si se encontro el viaje,
    cout<<"-------------------------------------------"<<endl;
    cout<<"\tListado de pasajeros del viaje #"<<idViaje<<":"<<endl;
    while(auxP != NULL){
        if(auxP->destinoP == idViaje){
            buscar = true;
            cout<<"\tNombre: "<<auxP->nombre<<", Apellido: "<<auxP->apellido<<", ID: "<<auxP->cc<<endl;
        }
        auxP = auxP->sigP;
    }
    if(!buscar){//sigue siendo falso o vacio buscar- false
        cout<<"\tNo hay pasajeros registrados para este viaje."<<endl;
    }
    cout<<"-------------------------------------------"<<endl;
}

int main() {
    int opcion;

    //falta hacer los metodos de balance y crear las funciones necesarios para el arbol
    //hallar su altura, obtener el balance real, rotaciones (izq, der, izq-der, der-izq)
    //y poco más.

    cout<<"-------------------------------------------"<<endl;
    cout<<"            .:GESTION DE VIAJES:.              "<<endl;


    do {
        cout<<"-------------------------------------------"<<endl;
        cout<<"\t\tAplicacion de viajes"<<endl;
        cout<<"-------------------------------------------"<<endl;
        cout<<"\t\t1. Registrar Viaje"<<endl;//si
        cout<<"\t\t2. Listar Viajes"<<endl;//si en inorden (falta balancear)
        cout<<"\t\t3. Buscar Viaje"<<endl;//si por identificador
        cout<<"\t\t4. Eliminar Viaje"<<endl;//en duda 
        cout<<"\t\t5. Registrar Pasajero"<<endl;//funciona pero aun no se ha hecho que se registren los pasajers en un viaje especificvo
        cout<<"\t\t6. Listar Pasajeros"<<endl;//funciona el bucle for, en general (me falta agregarle ek viaje a elegir)
        cout<<"\t\t0. Salir"<<endl;//bueno...
        cout<<"-------------------------------------------"<<endl;
        cout<<"\t\tIngrese una opcion: ";
        cin>>opcion;
        cout<<"-------------------------------------------"<<endl;

        switch(opcion){
            case 1:
                registrarViaje();
                raiz = insertar(raiz);
                break;
            case 2:
                listarViaje();
                break;
            case 3:
                buscarViaje();
                break;
            case 4:
                eliminarViaje();
                break;
            case 5:
                registrarPasajeros();
                break;
            case 6:
                listarPasajeros();
                break;
            case 0:
                cout<<"\tSaliendo del programa..."<<endl;
                break;
            default:
                cout<<"\tOpcion invalida."<<endl;
                break;
        }
    } while(opcion != 0);

    return 0;
}
/*
Tabla dinámica para listar pasajeros de un viaje (NO IMPLEMENTADO)
    cout << " \n";
    cout << " \n";
    cout << " \n";
    cout << " \n";
    cout << "========================================================================================================================\n";
    cout << "                                          PASAJEROS DE (NVIAJE)                                                            \n";
    cout << "========================================================================================================================\n";
    cout << "  CC/TI                                Nombre                Apellido                                 Destino                           \n";
    cout << "========================================================================================================================\n";

    for (auxP = cabP; auxP != NULL; auxP = auxP->sigP)
        cout << "  " << auxP->cc << "                             " << auxP->nombre << "                      " << auxP->apellido << "                              " << auxP->destinoP << "                             \n";
    cout << "========================================================================================================================\n";
    cout << " \n";
    cout << " \n";
    cout << " \n";
    cout << " \n";
    cout << "========================================================================================================================\n";
}*/