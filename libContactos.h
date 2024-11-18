#ifndef LIB_CONTACTOS_H
#define LIB_CONTACTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libArchivos.h"
#include "structureLib.h"

extern tContacto *agenda;


tContacto* crearContacto() {
    tContacto *nuevoContacto = (tContacto*)malloc(sizeof(tContacto));
    
    if (nuevoContacto == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    int id = getUltimaId();  
    nuevoContacto->id = id + 1;  
    
    while (getchar() != '\n');

    printf("Nombre: ");
    fgets(nuevoContacto->nombre, sizeof(nuevoContacto->nombre), stdin);
    nuevoContacto->nombre[strcspn(nuevoContacto->nombre, "\n")] = 0;

    printf("Apellido: ");
    fgets(nuevoContacto->apellido, sizeof(nuevoContacto->apellido), stdin);
    nuevoContacto->apellido[strcspn(nuevoContacto->apellido, "\n")] = 0;

    printf("Numero telefonico: ");
    while (getchar() != '\n'); 
    scanf(" %s", nuevoContacto->numero);
    while (getchar() != '\n'); 

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
    long pos = -1;  // Variable para almacenar la posición en el archivo
    
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
                anterior->siguiente = actual->siguiente; // Saltar el nodo actual
            }
            printf("El contacto con número %s ha sido eliminado.\n", numero);
            free(actual); // Liberar memoria del nodo eliminado
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("No se encontró ningún contacto con el número %s.\n", numero);
    }

    grabarLista(agenda); // Guardar la lista actualizada
}

#endif // LIB_CONTACTOS_H