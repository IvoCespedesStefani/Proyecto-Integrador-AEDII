#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "libContactos.h"
#include "libArchivos.h"

void generarMenu();
tContacto *agenda;

void generarMenu() {
    agenda = cargarLista();  
    char seleccion;
    int opciones = -1;
    tString numero;  

    do {
        printf("Seleccione una opcion:\n"
               "1: Cargar nuevo contacto\n"
               "2: Editar un contacto\n"
               "3: Eliminar un contacto\n"
               "4: Ver un contacto especifico\n"
               "5: Ver todos los contactos\n"
               "0: Salir del programa\n"
               "Su eleccion: ");
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
                    printf("¿Desea cargar otro contacto?\n"
                           "1: Sí\n"
                           "2: No\n"
                           "Su elección: ");
                    if (scanf("%d", &seguirGenerando) != 1 || (seguirGenerando != 1 && seguirGenerando != 2)) {
                        printf("Opción invalida. Terminando la carga de contactos.\n");
                        seguirGenerando = 2; 
                    }
                }
                grabarLista(agenda);  
                break;
            }
            case 2:
                printf("Ingrese el numero de telefono del contacto a editar.\nNumero: ");
                while (getchar() != '\n');  
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';  
                editarContacto(numero); 
                break;
            case 3:
                printf("Ingrese el numero de telefono que desea eliminar.\nNumero: ");
                while (getchar() != '\n');  
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';  
                eliminarContacto(numero);  
                break;
            case 4:
                printf("Ingrese el numero del contacto que desea ver.\nNumero: ");
                while (getchar() != '\n'); 
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0'; 
                mostrarContactoEspecifico(numero);  
                break;
            case 5:
                mostrarContactos();
                break;
            default:
                printf("El numero ingresado está fuera de rango. Por favor ingrese un numero entre 0 y 5.\n");
                break;
        }

        if (opciones != 0) {  
            printf("¿Desea realizar más operaciones? (y/n): ");
            while (getchar() != '\n');  
            scanf(" %c", &seleccion);
            while (getchar() != '\n');  
        } else {
            seleccion = 'n';
        }
    } while (seleccion == 'y' || seleccion == 'Y');
}

#endif // UTILS_H