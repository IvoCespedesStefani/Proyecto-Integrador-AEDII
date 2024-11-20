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
    FILE *archivo = abrirArchivoEscritura();

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

    while (!feof(archivo)) {  
        size_t bytesLeidos = fread(&contactoTemp, sizeof(tContacto), 1, archivo);
        if (bytesLeidos != 1) {
            if (feof(archivo)) {
                break;  
            }
            perror("Error al leer el archivo");
            break;
        }

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

tContacto* getContactoNum(tString numero) {
    tContacto contacto;
    FILE *archivo = abrirArchivoLectura();
    
    while (!feof(archivo)) {  
        int bytesLeidos = fread(&contacto, sizeof(tContacto), 1, archivo);  
        if (bytesLeidos != 1) {
            if (feof(archivo)) {
                break;  
            }
            perror("Error al leer el archivo");
            break;
        }

        if (strcmp(contacto.numero, numero) == 0) {
            cerrarArchivo(archivo);
            tContacto* contactoEncontrado = (tContacto*)malloc(sizeof(tContacto));
            if (contactoEncontrado == NULL) {
                printf("Error al asignar memoria para el contacto.\n");
                exit(1);
            }
            memcpy(contactoEncontrado, &contacto, sizeof(tContacto));  
            return contactoEncontrado; 
        }
    }

    cerrarArchivo(archivo);

    tContacto* contactoNoEncontrado = (tContacto*)malloc(sizeof(tContacto));
    if (contactoNoEncontrado == NULL) {
        printf("Error al asignar memoria para el contacto.\n");
        exit(1);
    }
    strcpy(contactoNoEncontrado->numero, "No se encontro el contacto");
    return contactoNoEncontrado;
}
#endif // LIB_ARCHIVOS_H
