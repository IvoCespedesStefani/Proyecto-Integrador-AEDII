#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *abrirArchivoLectura() {
	
    FILE *archivo = fopen("db.dat", "rb"); 
    
    if (archivo == NULL) { 
    	printf("Creando base de datos...\n");
        archivo = fopen("db.dat", "wb");
        if (archivo != NULL) {
            fclose(archivo);
            archivo = fopen("db.dat", "rb"); 
            printf("Conexion establecida con Base de Datos\n");
        } else {
            perror("Error al crear el archivo");
        }
    } else {
        printf("Conexion establecida con Base de Datos\n");
    }
    
    return archivo;
}

FILE *abrirArchivoEscritura(){
	
    FILE *archivo = fopen("db.dat", "ab");
    
    if (archivo == NULL) { 
        printf("Creando base de datos...\n");
        archivo = fopen("db.dat", "wb");
        if (archivo != NULL) {
            fclose(archivo);
            archivo = fopen("db.dat", "ab"); 
            printf("Conexion establecida con Base de Datos\n");
        } else {
            perror("Error al crear el archivo");
        }
    } else {
        printf("Conexion establecida con Base de Datos\n");
    }
    
    return archivo;
}

void cerrarArchivo(FILE* archivo){
	fclose(archivo);
}

void grabarContacto(tContacto *contacto){
	
	FILE *archivo = abrirArchivoEscritura();
	
	fwrite(contacto, sizeof(tContacto), 1, archivo);
	
	cerrarArchivo(archivo);
}

int getUltimaId(){
	
	tContacto contacto;
	int id = -1;
	
	FILE *archivo = abrirArchivoLectura();
	fread(&contacto, sizeof(tContacto), 1, archivo);
	
	while (fread(&contacto, sizeof(tContacto), 1, archivo) == 1) {
        id = contacto.id;  
    }
	
	cerrarArchivo(archivo);
	
	return id;
}
