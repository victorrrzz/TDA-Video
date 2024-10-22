
#ifndef PRACTICA2_VIDEO_H
#define PRACTICA2_VIDEO_H
#include "image.h"
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <cmath>
#include <string>
#include <filesystem>
#include <iostream>
using namespace std;

 /**
   * @brief Lee el contenido de un directorio y almacena los nombres de los archivos en un vector
   * @param name Nombre del fichero a leer
   * @param v Referencia al vector donde se almacenan los nombres de los archivos
   */
void read_directory(const std::string& name, vector<string>& v);


/**
    * @class Video
    * @brief Clase de video que representa una secuencia de imagenes, y que permite manipularla
    */
class Video {
private:
    vector<Image> seq;
public:
/**
    * @brief Constructor por defecto, inicializa un video vacio
    */
    Video();
/**
    * @brief Constructor de un video con un numero dado de imagenes vacias
    * @param n Numero de imagenes del video
    * @pre n debe de ser mayor que 0
    * @post El video creado tiene n casillas
    * @post El video creado contiene valores "basura" (no esta inicializado)
*/
    Video(int n);
/**
    * @brief Constructor de copia de video que crea una copia profunda de otro video
    * @param V Referencia al video a copiar
*/
    Video(const Video &V);
/**
    * @brief Destructor de la clase video que libera la memoria que este usando el video
    * @post El video destruido no puede volver a usarse, salvo que se vuelva a realizar sobre el otra operacion de construccion
*/
    ~Video();
/**
    * @brief Operador de asignacion que asigna el contenido de un video a otro
    * @param V Referencia al video que se quiere copiar
    * @return Referencia al actual video
*/
    Video &operator=(const Video &V);
/**
    * @brief Calcula el numero de fotogramas del video
    * @return Numero de fotogramas del video
*/
    int size() const;
/**
    * @brief Operador [] que permite consultar un fotograma del video
    * @param foto Posicion del video a la que se quiere acceder
    * @pre foto debe ser mayor o igual que 0 y menos que el tamaño del video
    * @return Referencia a la imagen asociada al fotograma foto-esimo del video
    * @note El metodo permite modificar la imagen
*/
    Image &operator[](int foto);
/**
    * @brief Operador [] que permite consultar un fotograma del video
    * @param foto Posicion del video a la que se quiere acceder
    * @pre foto debe ser mayor o igual que 0 y menos que el tamaño del video
    * @return Referencia constante a la imagen asociada al fotograma foto-esimo del video
    * @note El metodo no permite modificar la imagen
*/
    const Image &operator[](int foto)const;
/**
    * @brief Inserta en la posicion dada del video un nuevo fotograma
    * @param k Posicion del video donde inserta el fotograma
    * @param I Imagen a insertar
    * @post El video se modifica teniendo un nuevo fotograma mas
*/
    void Insertar(int k, const Image &I);
/**
    * @brief Eliminar el fotograma en una posicion
    * @param k Posicion de la imagen a eliminar
    * @pre k debe de ser una posicion valida dentro del video, debe de estar en el rango [0,V.size()-1]
    * @post El video se modifica teniendo un fotograma menos
*/
    void Borrar(int k);
/**
    * @brief Leer del disco un video
    * @param path El camino del directorio donde se encuentran los archivos a leer
    * @pre En el directorio path debe almacenarse una secuencia temporal de fotogramas
    * @return true si la lectura ha tenido exicto, False si la lectura no ha tenido exito
*/
    bool LeerVideo(const string & path);
/**
    * @brief Escribe en el disco un video
    * @param path Camino del directorio donde se guardara el video
    * @param prefijo Prefijo que se usara para los archivos de imagenes
    * @pre en el directorio path se almacenará la secuencia temporal de fotogramas. Los fotogramas tomarán como nombre <prefijo>_01.pgm .. <prefijo>_0n.pgm siendo n el numero de fotogramas.
    * @return true si la escritura ha tenido exito, false si la lectura no ha tenido exito
*/
    bool EscribirVideo(const string & path, const string &prefijo)const;

};

#endif //PRACTICA2_VIDEO_H
