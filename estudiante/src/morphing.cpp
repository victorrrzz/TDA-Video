#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
#include <vector>

const int n_puntos = 10;
/**
    * @brief Estructura que representa un punto de dos dimensiones
    */
struct Punto2D
{
    float x,y;
};
/**
    * @brief Interpola entre dos puntos de dos dimensiones
    * @param inicio Referencia constante al punto de inicio de la interpolacion
    * @param fin Referencia constante al punto final de la interpolacion
    * @param t El factor de interpolacion
    * @pre t debe de ser mayor o igual que 0 y menos o igual que 1
    * @return Punto2D interpolado
*/
Punto2D InterpolarPunto(const Punto2D &inicio, const Punto2D &fin, float t)
{
    // Punto intermedio
    Punto2D i;
    i.x = (1 - t) * inicio.x + t * fin.x;
    i.y = (1 - t) * inicio.x + t * fin.y;
    
    return i;

}
/**
    * @brief Genera un vector de puntos 2D aleatorios
    * @param n Numero de puntos a generar
    * @param fil Numero de filas para el espacio de coordenadas
    * @param col Numero de columnas para el espacio de coordenadas
    * @return Vector de puntos 2D aleatoriamente generados dentro de los parametros especificados
*/
vector<Punto2D> GenPuntos(int n, int fil, int col)
{
    vector<Punto2D> out(n);
    for (int i = 0; i < n; i++)
    {
        out[i].x = rand() % col;
        out[i].y = rand() % fil;
    }
    
    return out;
}

/**
    * @brief Crea un video de transformacion entre dos imagenes
    * @param I1 Referencia constante a la imagen de inicio de la transformacion
    * @param I2 Referencia constante a la imagen final de la transformacion
    * @param nframes Numero de frames a generar en el video de la transformacion
    * @return Video de la transformacion
*/
Video Morphing(const Image &I1,const Image &I2,int nframes){
    Video aux;
    if(I1.get_cols()==I2.get_cols() && I1.get_rows()==I2.get_rows())
    {
        int row = I1.get_rows();
        int col = I1.get_cols();

        vector<Punto2D> p_origen = GenPuntos(n_puntos, row, col);
        vector<Punto2D> p_destino = GenPuntos(n_puntos, row, col);

        for(int i=0; i<nframes; i++)
        {
            float t = (i/ (float)nframes);
            Image Iaux(row, col);

            for(int j = 0; j < row; j++)
            {
                for (int k = 0; k < col; k++)
                {
                    int index = k + j * col;
                    pixel morphed_pixel = I1.get_pixel(index) * (1 - t) + I2.get_pixel(index) * t;
                    Iaux.set_pixel(j, k, morphed_pixel);
                }
            }

            for (int p = 0; p < n_puntos; p++)
            {
                Punto2D i = InterpolarPunto(p_origen[p], p_destino[p], t);
                int x = (int) i.x;
                int y = (int) i.y;

                if (x >= 0 && x < col && y >= 0 && y < row)
                {
                    int index = x + y * col;
                    pixel morphed_pixel = I1.get_pixel(index) * (1 - t) + I2.get_pixel(index) * t;
                    Iaux.set_pixel(y, x, morphed_pixel);

                }
            }
            aux.Insertar(i,Iaux);
        }
        return aux;
    } else{
        exit(1);
    }
}
/**
    * @brief Funcion principal que ejecuta el morphing entre dos imagenes y guarda el video resultado
    * @note El programa debe de recibir el fichero donde se encuentra la imagen inicial, el fichero donde se encuentra la imagen final, el directorio donde se debe de almacenar el video creado, y un numero de pasos para realizar la transformacion
    * @param argc Numero de argumentos dados a la funcion
    * @param argv array de argumentos dados a la funcion
    * @pre argc debe de ser 5
    * @return 0 si exito, 1 si falla
*/
int main(int argc, char * argv[]){

    if(argc != 5){
        cerr << "Uso: <fich_orig> <fich_rdo> <dir_salida> <n_fotogramas> ";
        return 1;
    }

    char* fich_orig = argv[1];
    char* fich_rdo = argv[2];
    char* directorio_salida = argv[3];
    int num_fotogramas =stoi(argv[4]);

    Image I1,I2;
    if(!I1.Load(fich_orig) || !I2.Load(fich_rdo)){
        cerr << "Error en la lectura de las imagenes";
        return 1;
    }

    Video aux = Morphing(I1, I2, num_fotogramas);

    for(int i=0; i<num_fotogramas; i++)
    {
        ostringstream out;
        out << string(directorio_salida)  << "/fotograma_" << setw(3)  << setfill('0') << i << ".pgm";
        std::string nombre_fotograma = out.str();
        const char* nombre_fotograma_cstr = nombre_fotograma.c_str();

        if(!aux[i].Save(nombre_fotograma_cstr)){
            cerr << "Error guardando el fotograma" << i;
            return 1;
        }
    }

}
