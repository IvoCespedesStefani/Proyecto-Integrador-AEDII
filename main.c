#include <stdio.h>
#include "libContactos.h"
#include "libArchivos.h"

int main() {
	
    tContacto *lista = cargarLista();  
    mostrarContactoEspecifico("3624277088");
    
}
