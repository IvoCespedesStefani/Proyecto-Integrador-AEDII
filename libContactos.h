#ifndef LIB_CONTACTOS_H
#define LIB_CONTACTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libArchivos.h"
#include "structureLib.h"

extern tContacto *agenda;

tContacto* crearContacto();
int esNumeroValido(const char*);
tContacto* editarContacto(tString num);
void eliminarContacto(const char*);
void liberarLista(tContacto*);
tContacto *copiarLista(tContacto *);
void mostrarContactos(tContacto *;
void mostrarContactoEspecifico(tContacto*, tString);

int esNumeroValido(const char* numero) {
    for (int i = 0; numero[i] != '\0'; i++) {
        if (!isdigit(numero[i])) {
            return 0; 
        }
    }
    return 1; 
}

tContacto* crearContacto() {
    tContacto* nuevoContacto = (tContacto*)malloc(sizeof(tContacto));

    if (nuevoContacto == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    while (getchar() != '\n');

    printf("Nombre: ");
    fgets(nuevoContacto->nombre, sizeof(nuevoContacto->nombre), stdin);
    nuevoContacto->nombre[strcspn(nuevoContacto->nombre, "\n")] = 0;

    printf("Apellido: ");
    fgets(nuevoContacto->apellido, sizeof(nuevoContacto->apellido), stdin);
    nuevoContacto->apellido[strcspn(nuevoContacto->apellido, "\n")] = 0;

    do {
        printf("Numero telefonico: ");
        fgets(nuevoContacto->numero, sizeof(nuevoContacto->numero), stdin);
        nuevoContacto->numero[strcspn(nuevoContacto->numero, "\n")] = 0;

        if (!esNumeroValido(nuevoContacto->numero)) {
            printf("El número ingresado contiene caracteres inválidos. Intenta nuevamente.\n");
        }
    } while (!esNumeroValido(nuevoContacto->numero)); 

    printf("Nota (Opcional): ");
    fgets(nuevoContacto->nota, sizeof(nuevoContacto->nota), stdin);
    nuevoContacto->nota[strcspn(nuevoContacto->nota, "\n")] = 0;

    if (strlen(nuevoContacto->nota) == 0) {
        strcpy(nuevoContacto->nota, "No se proporciono una nota");
        printf("No se asigno una nota a este contacto\n");
    }

    nuevoContacto->siguiente = NULL;
    return nuevoContacto;
}

tContacto* editarContacto(tString num) {
    tContacto* contactoEditar = getContactoNum(num);  
    
    if (contactoEditar == NULL || strcmp(contactoEditar->numero, "No se encontro el contacto") == 0) {
        printf("\nNo se encontro el contacto para editar.\n");
        return NULL;
    }

    printf("\nEditando el contacto %s\n\n", contactoEditar->numero);
    
    printf("Nuevo nombre: ");
    fgets(contactoEditar->nombre, sizeof(contactoEditar->nombre), stdin);
    contactoEditar->nombre[strcspn(contactoEditar->nombre, "\n")] = 0;  
    
    printf("Nuevo apellido: ");
    fgets(contactoEditar->apellido, sizeof(contactoEditar->apellido), stdin);
    contactoEditar->apellido[strcspn(contactoEditar->apellido, "\n")] = 0;
    
    printf("Nueva nota: ");
    fgets(contactoEditar->nota, sizeof(contactoEditar->nota), stdin);
    contactoEditar->nota[strcspn(contactoEditar->apellido, "\n")] = 0;
     
    if (strlen(contactoEditar->nota) == 0) {
        strcpy(contactoEditar->nota, "No se proporciono una nota");
        printf("No se asigno una nota a este contacto\n");
    }
     
    FILE* archivo = abrirArchivoEscritura();
    tContacto contacto;
    long pos = -1;  // Almacenar posicion
    
    // Buscamos el contacto y almacenamos la posición
    while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1) {
        pos = ftell(archivo) - sizeof(tContacto);  // Guardar la pos actual antes de leer el siguiente contacto
        if (strcmp(contacto.numero, num) == 0) {
            // Nos movemos a la posición del contacto en el archivo
            fseek(archivo, pos, SEEK_SET);
            // Sobrescribimos el contacto editado
            if (fwrite(contactoEditar, sizeof(tContacto), 1, archivo) != 1) {
                printf("Error al guardar el contacto editado en el archivo.\n");
                cerrarArchivo(archivo);
                return NULL;
            }
            printf("Contacto actualizado exitosamente.\n");
            break;
        }
    }
    
    cerrarArchivo(archivo);
    return contactoEditar;  
}

void eliminarContacto(const char *numero) {
    tContacto *actual = agenda;
    tContacto *anterior = NULL;
    int encontrado = 0;

    if (agenda == NULL) {
        printf("La lista está vacía.\n");
        return;
    }
    
    while (actual != NULL) {
        if (strcmp(actual->numero, numero) == 0) {
            encontrado = 1;
            if (anterior == NULL) {
                agenda = actual->siguiente; 
            } else {
                anterior->siguiente = actual->siguiente; 
            }
            printf("El contacto con número %s ha sido eliminado.\n", numero);
            free(actual); 
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("No se encontró ningún contacto con el número %s.\n", numero);
    }

    grabarLista(agenda); 
}

void liberarLista(tContacto *lista) {
    tContacto *actual;
    while (lista != NULL) {
        actual = lista;
        lista = lista->siguiente;
        free(actual);
    }
}

tContacto *copiarLista(tContacto *listaOriginal) {
    if (listaOriginal == NULL) {
        return NULL;
    }

    tContacto *copia = NULL, *ultimo = NULL;

    tContacto *actual = listaOriginal;
    while (actual != NULL) {
        tContacto *nuevoNodo = (tContacto *)malloc(sizeof(tContacto));
        if (nuevoNodo == NULL) {
            perror("No se pudo asignar memoria para la copia.");
            liberarLista(copia); 
            return NULL;
        }
        *nuevoNodo = *actual;
        nuevoNodo->siguiente = NULL;

        if (copia == NULL) {
            copia = nuevoNodo;
        } else {
            ultimo->siguiente = nuevoNodo;
        }
        ultimo = nuevoNodo;

        actual = actual->siguiente;
    }

    return copia;
}

void mostrarContactos(tContacto *lista) {
    if (lista == NULL) {
        printf("\nNo hay contactos almacenados.\n");
        return;
    }

    tContacto *copiaLista = copiarLista(lista);
    if (copiaLista == NULL) {
        printf("\nError al crear la copia de la lista.\n");
        return;
    }

    printf("\nLista de contactos:\n");
    printf("====================================\n");

    tContacto *actual = copiaLista;
    while (actual != NULL) {
        printf("Nombre: %s\n", actual->nombre);
        printf("Apellido: %s\n", actual->apellido);
        printf("Numero: %s\n", actual->numero);
        printf("------------------------------------\n");

        actual = actual->siguiente;
    }

    liberarLista(copiaLista);
}

void mostrarContactoEspecifico(tContacto *lista, tString numero) {
    if (lista == NULL) {
        printf("La lista de contactos está vacía.\n");
        return;
    }

    tContacto *copiaLista = copiarLista(lista);
    if (copiaLista == NULL) {
        printf("Error al crear la copia de la lista.\n");
        return;
    }

    tContacto *actual = copiaLista;
    int encontrado = 0;

    while (actual != NULL) {
        if (strcmp(actual->numero, numero) == 0) {
            printf("Nombre: %s\n", actual->nombre);
            printf("Apellido: %s\n", actual->apellido);
            printf("Numero: %s\n", actual->numero);
            printf("Nota: %s\n", actual->nota);
            encontrado = 1;
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("No se encontró el contacto.\n");
    }

    liberarLista(copiaLista);
}


#endif // LIB_CONTACTOS_H