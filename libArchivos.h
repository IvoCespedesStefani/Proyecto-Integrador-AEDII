#ifndef LIB_ARCHIVOS_H
#define LIB_ARCHIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structureLib.h"

FILE *abrirArchivoLectura();
FILE *abrirArchivoEscritura();
void cerrarArchivo(FILE*);
void grabarLista(tContacto*);
tContacto *cargarLista();
int getUltimaId();
tContacto getContactoId(int);
tContacto* getContactoNum(tString);

FILE *abrirArchivoLectura() {
    FILE *archivo = fopen("db.dat", "rb"); 
    
    if (archivo == NULL) { 
        printf("Creando base de datos...\n");
        archivo = fopen("db.dat", "wb");
        if (archivo != NULL) {
            fclose(archivo);
            archivo = fopen("db.dat", "rb"); 
        } else {
            perror("Error al crear el archivo");
        }
    } 
    
    return archivo;
}

FILE* abrirArchivoEscritura() {
    FILE* archivo = fopen("db.dat", "r+b");  
    
    if (archivo == NULL) {
        printf("Creando base de datos...\n");
        archivo = fopen("db.dat", "wb"); 
        if (archivo != NULL) {
            fclose(archivo);
            archivo = fopen("db.dat", "r+b");  
        } else {
            perror("Error al crear el archivo");
        }
    }
    
    return archivo;
}

void cerrarArchivo(FILE* archivo) {
    fclose(archivo);
}

void grabarLista(tContacto *lista) {
    FILE *archivo = fopen("db.dat", "wb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para escribir");
        return;
    }

    tContacto *actual = lista;
    while (actual != NULL) {
        fwrite(actual, sizeof(tContacto), 1, archivo); 
        actual = actual->siguiente;
    }

    fclose(archivo);
    printf("Contactos guardados exitosamente.\n");
}

tContacto *cargarLista() {
    FILE *archivo = abrirArchivoLectura();

    if (archivo == NULL) {
        return NULL;
    }

    tContacto *lista = NULL, *ultimo = NULL, contactoTemp;

    while (fread(&contactoTemp, sizeof(tContacto), 1, archivo) == 1) {
        tContacto *nuevoContacto = (tContacto *)malloc(sizeof(tContacto));
        if (nuevoContacto == NULL) {
            perror("No se pudo asignar memoria");
            cerrarArchivo(archivo);
            return lista;
        }

        *nuevoContacto = contactoTemp;
        nuevoContacto->siguiente = NULL;

        if (lista == NULL) {
            lista = nuevoContacto; 
        } else {
            ultimo->siguiente = nuevoContacto;
        }
        ultimo = nuevoContacto;
    }

    cerrarArchivo(archivo);
    return lista;
}

int getUltimaId() {
    FILE *archivo = abrirArchivoLectura();

    tContacto contacto;
    int ultimaId;

    while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1) {
        ultimaId = contacto.id;  
    }

    fclose(archivo); 
    return ultimaId;  
}

tContacto getContactoId(int id) {
    tContacto contacto;
    FILE *archivo = abrirArchivoLectura();
    
    while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1) {
        if (contacto.id == id) {
            cerrarArchivo(archivo);
            return contacto;
        }
    }
    
    cerrarArchivo(archivo);
    contacto.id = -1; 
    return contacto;
}

tContacto* getContactoNum(tString numero) {
    tContacto contacto;  
    FILE *archivo = abrirArchivoLectura();
    
    while(fread(&contacto, sizeof(tContacto), 1, archivo) == 1) { 
        if (strcmp(contacto.numero, numero) == 0){
            cerrarArchivo(archivo);
            tContacto* contactoEncontrado = (tContacto*)malloc(sizeof(tContacto));
            if (contactoEncontrado == NULL) {
                printf("Error al asignar memoria para el contacto.\n");
                exit(1);
            }
            memcpy(contactoEncontrado, &contacto, sizeof(tContacto));  
            return contactoEncontrado;  // Devolver una copia del contacto encontrado
        }
    }
    cerrarArchivo(archivo);
    // Si no se encuentra el contacto, devolvemos un puntero con el numero indicando que no se encontró
    tContacto* contactoNoEncontrado = (tContacto*)malloc(sizeof(tContacto));
    if (contactoNoEncontrado == NULL) {
        printf("Error al asignar memoria para el contacto.\n");
        exit(1);
    }
    strcpy(contactoNoEncontrado->numero, "No se encontro el contacto");
    return contactoNoEncontrado;
}

#endif // LIB_ARCHIVOS_H
