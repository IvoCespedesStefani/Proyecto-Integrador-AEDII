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
    nuevoContacto->id = id;

    printf("Nombre: ");
    fgets(nuevoContacto->nombre, sizeof(nuevoContacto->nombre), stdin);
    nuevoContacto->nombre[strcspn(nuevoContacto->nombre, "\n")] = 0;

    printf("Apellido: ");
    fgets(nuevoContacto->apellido, sizeof(nuevoContacto->apellido), stdin);
    nuevoContacto->apellido[strcspn(nuevoContacto->apellido, "\n")] = 0;

    printf("Numero telefonico: ");
    scanf("%d", &nuevoContacto->numero);
    getchar(); 

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

#endif // LIB_CONTACTOS_H