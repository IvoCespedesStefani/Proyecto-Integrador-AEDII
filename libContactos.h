#ifndef LIB_CONTACTOS_H
#define LIB_CONTACTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libArchivos.h"
#include "structureLib.h"

tContacto* crearContacto() {
	
    tContacto *nuevoContacto = (tContacto*)malloc(sizeof(tContacto));
    
    if (nuevoContacto == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    int id = getUltimaId();  
    nuevoContacto->id = id + 1;  

    printf("Nombre: ");
    fgets(nuevoContacto->nombre, sizeof(nuevoContacto->nombre), stdin);
    nuevoContacto->nombre[strcspn(nuevoContacto->nombre, "\n")] = 0;

    printf("Apellido: ");
    fgets(nuevoContacto->apellido, sizeof(nuevoContacto->apellido), stdin);
    nuevoContacto->apellido[strcspn(nuevoContacto->apellido, "\n")] = 0;

    printf("Numero telefonico: ");
   	scanf("%s", &nuevoContacto->numero);
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
    tContacto* contactoEditar = getContactoNum(num);  // Llamamos a getContactoNum para obtener el puntero
    
    if (contactoEditar == NULL || strcmp(contactoEditar->numero, "No se encontro el contacto") == 0) {
        printf("\nNo se encontró el contacto para editar.\n");
        return NULL;
    }

    printf("\nEditando el contacto %s\n\n", contactoEditar->numero);
    
    // Pedir el nuevo nombre
    printf("Nuevo nombre: ");
    fgets(contactoEditar->nombre, sizeof(contactoEditar->nombre), stdin);
    contactoEditar->nombre[strcspn(contactoEditar->nombre, "\n")] = 0;  
    
    FILE* archivo = abrirArchivoEscritura();
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escritura.\n");
        return NULL;
    }
    
    tContacto contacto;
    long pos = -1;  // Variable para almacenar la posición en el archivo
    
    // Buscamos el contacto y almacenamos la posición
    while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1) {
        pos = ftell(archivo) - sizeof(tContacto);  // Guardar la pos actual antes de leer el siguiente contacto
        if (strcmp(contacto.numero, num) == 0) {
            // Moverse a pos del contacto en el archivo
            fseek(archivo, pos, SEEK_SET);
            // Sobreescribir el contacto editado
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


#endif // LIB_CONTACTOS_H