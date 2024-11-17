#ifndef STRUCTURE_LIB_H
#define STRUCTURE_LIB_H

typedef char tString[100];

typedef struct contacto {
    int id;
    tString nombre;
    tString apellido;
    int numero;
    tString nota;
    struct contacto *siguiente;
} tContacto;

#endif // STRUCTURE_LIB_H
