#include "image.h"
#include "video.h"
#include <iostream>

/**
    * @brief Rebobina un video revirtiendo el orden de sus frames
    * @param V Referencia constante al video que se va a rebobinar
    * @return Nuevo video con los fotogramas en orden invertido
*/

Video Rebobinar(const Video &V){
    Video aux;
    for(int i=V.size()-1; i>=0; i--)
    {
        cout << "Insertando imagen: " << i << endl; 
        aux.Insertar(V.size()-i-1,V[i]);
    }
    return aux;
}
/**
    * @brief Funcion principal para rebobinar un video y almacenarlo en un directorio
    * @param argc Numero de argumentos que recibe la funcion
    * @param argv El array de argumentos que recibe la funcion
    * @pre El numero de argumentos debe de ser 3
    * @return 0 si exito, 1 si fallo
*/
int main(int argc, char * argv[]){
    if(argc!=3){
        cerr << "Numero de argumentos incorrectos. Debe introducir dos argumentos";
        return 1;
    }
    string dir_entrada = argv[1];
    string dir_salida = argv[2];

    Video v;
    cout << "- - - - - leyendo video - - - - - " << endl;
    if(!v.LeerVideo(dir_entrada)){
        cerr << "Error en la lectura del video";
        return 1;
    }
    cout << "- - - - - rebobinando video - - - - - " << endl;
    Video aux = Rebobinar(v);
    cout << "- - - - - rebobinar terminado - - - - - " << endl;

    cout << "vector size: " << v.size() << endl;
    for(int i=0; i<v.size(); i++)
    {
        cout << "Escribiendo frame: " << i << endl;
    }
       if(!aux.EscribirVideo(dir_salida, "rewind-"))
       {
           cerr << "Error escribiendo el video rebobinado" << endl;
           return 1;
       }
    cout << "Escritura completada" << endl;
}
