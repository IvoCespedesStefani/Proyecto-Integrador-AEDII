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
<<<<<<< HEAD
tContacto* getContactoNum(tString);
=======
tContacto getContactoNum(tString);
>>>>>>> main
void mostrarContactos();

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


void cerrarArchivo(FILE* archivo){
	fclose(archivo);
}

void grabarLista(tContacto *lista) {
    if (lista == NULL) {
        printf("No hay contactos para guardar.\n");
        return;
    }

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

void mostrarContactos() {
    FILE *archivo = abrirArchivoLectura();
    tContacto contacto;
    int encontrado = 0;
	
	printf("\n");
    printf("Lista de contactos:\n");
    printf("====================================\n");

    while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1) {
        printf("ID: %d\n", contacto.id);
        printf("Nombre: %s\n", contacto.nombre);
        printf("Apellido: %s\n", contacto.apellido);
        printf("Numero: %s\n", contacto.numero);
        printf("------------------------------------\n");
        encontrado = 1;
    }

    if (!encontrado) {
        printf("No hay contactos almacenados.\n");
    }

    cerrarArchivo(archivo);
}

void mostrarContactoEspecifico(tString numero){
<<<<<<< HEAD
    FILE *archivo = abrirArchivoLectura();

    tContacto contacto;
    int encontrado = 0;
    
    while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1) {
        // Comprobar si el número del contacto coincide
        if (strcmp(contacto.numero, numero) == 0) {
            printf("Nombre: %s\n", contacto.nombre);
            printf("Apellido: %s\n", contacto.apellido);
            printf("Numero: %s\n", contacto.numero);
            printf("Nota: %s\n", contacto.nota);
            encontrado = 1;
            break; // Salir del bucle cuando se encuentra el contacto
        }
    }
    
    // Verificar si no se encontró el contacto
    if (!encontrado) {
        printf("No se encontró el contacto\n");
    }

    fclose(archivo);  // Asegúrate de cerrar el archivo después de usarlo
=======
	FILE *archivo = abrirArchivoLectura();
	tContacto contacto;
	int encontrado = 0;
	
 	while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1){
 		if(strcmp(contacto.numero, numero) == 0){
 			printf("Nombre: %s\n", contacto.nombre);
 			printf("Apellido: %s\n", contacto.apellido);
 			printf("Numero: %s\n", contacto.numero);
 			printf("Nota: %s\n", contacto.nota);
 			encontrado = 1;
		 } else {
		 	encontrado = 0;
		 }
	}
	
	if(!encontrado){
		printf("No se encontro el contacto");
	}
	
>>>>>>> main
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

tContacto getContactoId(int id){
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

<<<<<<< HEAD
tContacto* getContactoNum(tString numero) {
    tContacto* contacto = malloc(sizeof(tContacto)); 
    if (contacto == NULL) {
        return NULL; 
    }
    
    FILE *archivo = abrirArchivoLectura();
    
    while (fread(contacto, sizeof(tContacto), 1, archivo) == 1) {
        if (strcmp(contacto->numero, numero) == 0) {
            cerrarArchivo(archivo);
            return contacto;
        }
    }
    
    cerrarArchivo(archivo);
    strcpy(contacto->numero, "No se encontro el contacto"); 
=======
tContacto getContactoNum(tString numero){
	
	tContacto contacto;
	FILE *archivo = abrirArchivoLectura();
	
	while(fread(&contacto, sizeof(tContacto), 1, archivo ) == 1) {
		if (strcmp(contacto.numero, numero) == 0){
			cerrarArchivo(archivo);
			return contacto;
		}
	}
	
	cerrarArchivo(archivo);
    strcpy(contacto.numero, "No se encontro el contacto");
>>>>>>> main
    return contacto;
}



#endif // LIB_ARCHIVOS_H