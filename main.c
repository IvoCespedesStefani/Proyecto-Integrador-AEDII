#include <stdio.h>
#include "libContactos.h"
#include "libArchivos.h"

int main() {
    tContacto *lista = cargarLista();  

    tContacto *nuevoContacto = crearContacto();
    nuevoContacto->siguiente = lista;  
    lista = nuevoContacto;            

    grabarLista(lista);  
	mostrarContactos();

    return 0;
}
