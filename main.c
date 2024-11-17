#include <stdio.h>
#include "libContactos.h"
#include "libArchivos.h"

int main() {
	
<<<<<<< HEAD
    /*tContacto *lista = cargarLista();  
    tContacto *nuevoContacto = crearContacto();
    nuevoContacto->siguiente = lista;
    lista = nuevoContacto;
    grabarLista(lista);
    
    mostrarContactoEspecifico("123");*/
    
    tContacto* editar = editarContacto("123");
    
    mostrarContactoEspecifico("123");
	
	printf("debug\n\n");
	mostrarContactos();
	
	return 0;
=======
    tContacto *lista = cargarLista();  
    mostrarContactoEspecifico("3624277088");
    
>>>>>>> main
}
