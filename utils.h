#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "libContactos.h"
#include "libArchivos.h"

void generarMenu();
void limpiarConsola();

void limpiarConsola() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
}

tContacto *agenda = NULL;
void generarMenu() {
	SetConsoleOutputCP(CP_UTF8); 
    agenda = cargarLista();  
    char seleccion;
    int opciones = -1;
    tString numero;  

    do {
    	limpiarConsola();
        printf("Seleccione una opción:\n"
               "1: Cargar nuevo contacto\n"
               "2: Editar un contacto\n"
               "3: Eliminar un contacto\n"
               "4: Ver un contacto específico\n"
               "5: Ver todos los contactos\n"
               "0: Salir del programa\n"
               "Su elección: ");
        if (scanf("%d", &opciones) != 1) {  
            printf("Entrada invalida. Por favor ingrese un numero entre 0 y 5.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (opciones) {
            case 0:
                printf("Gracias por utilizar la agenda. Saliendo del programa...\n");
                break;
            case 1: {
                int seguirGenerando = 1;
                while (seguirGenerando == 1) {
                    tContacto *nuevoContacto = crearContacto();  
                    nuevoContacto->siguiente = agenda;
                    agenda = nuevoContacto;
                    printf("Desea cargar otro contacto?\n"
                           "1: Sí\n"
                           "2: No\n"
                           "Su elección: ");
                    if (scanf("%d", &seguirGenerando) != 1 || (seguirGenerando != 1 && seguirGenerando != 2)) {
                        printf("Opción inválida. Terminando la carga de contactos.\n");
                        seguirGenerando = 2; 
                    }
                }
                grabarLista(agenda);  
                break;
            }
            case 2:
                printf("Ingrese el número de teléfono del contacto a editar.\nNúmero: ");
                while (getchar() != '\n');  
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';  
                editarContacto(numero); 
                break;
            case 3:
                printf("Ingrese el número de teléfono que desea eliminar.\nNúmero: ");
                while (getchar() != '\n');  
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';  
                eliminarContacto(numero);  
                break;
            case 4:
                printf("Ingrese el número del contacto que desea ver.\nNúmero: ");
                while (getchar() != '\n'); 
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0'; 
                mostrarContactoEspecifico(agenda, numero);  
                break;
            case 5:
                mostrarContactos(agenda);
                break;
            default:
                printf("El número ingresado está fuera de rango. Por favor ingrese un número entre 0 y 5.\n");
                break;
        }

        if (opciones != 0) {  
            printf("Desea realizar más operaciones? (y/n): ");
            do {
                while (getchar() != '\n'); 
                seleccion = getchar();

                if (seleccion != 'y' && seleccion != 'Y' && seleccion != 'n' && seleccion != 'N') {
                    printf("Opción inválida. Por favor ingrese 'y' para sí o 'n' para no: ");
                }
            } while (seleccion != 'y' && seleccion != 'Y' && seleccion != 'n' && seleccion != 'N');
        } else {
            seleccion = 'n';
        }
    } while (seleccion == 'y' || seleccion == 'Y');
}
