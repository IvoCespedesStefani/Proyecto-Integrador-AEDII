#include <stdio.h>
#include "libContactos.h"
#include "libArchivos.h"

int main() {
    
    tContacto *lista = cargarLista();  
   	/*tContacto *nuevo = crearContacto();
    nuevo->siguiente = lista;
    lista = nuevo;
    grabarLista(lista);*/
    
    eliminarContacto("123");
    mostrarContactos();
    /*tContacto *contactoEditar = editarContacto("123");
    printf("Debug\n\n\n");
    mostrarContactoEspecifico("123");*/
    
    return 0;
}
