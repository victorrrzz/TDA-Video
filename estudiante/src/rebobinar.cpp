#include "image.h"
#include "video.h"
#include <iostream>


Video Rebobinar(const Video &V){
    Video aux;
    for(int i=V.size(); i>1; i--)
    {
        aux.Insertar(V.size()-i,V[i]);
    }
    return aux;
    Video aux;
    for(int i=V.size(); i>1; i--)
    {
        aux.Insertar(V.size()-i,V[i]);
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
    if(!v.LeerVideo(dir_entrada)){
        cerr << "Error en la lectura del video";
        return 1;
    }

    Video aux = Rebobinar(v);
    for(int i=0; i<v.size(); i++)
    {

    }
}
