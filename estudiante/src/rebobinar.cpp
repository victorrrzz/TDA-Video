#include "image.h"
#include "video.h"
#include <iostream>

Video Rebobinar(const Video &V){
    Video aux;
    for(int i=V.size()-1; i>=0; i--)
    {
        cout << "Insertando imagen: " << i << endl; 
        aux.Insertar(V.size()-i-1,V[i]);
    }
    return aux;
}

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
