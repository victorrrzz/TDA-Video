#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>

 /**
   * @brief Transiciona dos imágenes en un vídeo
   * @param I1 Referencia al objeto imagen original
   * @param I2 Referencia al objeto imagen destino
   * @param nframes Número de fotogramas del vídeo resultante
   * @pre nframes debe de ser mayor que 0
   * @post El video creado tiene nframes imágenes
   * @return Referencia al objeto video creado 
*/

Video Morphing(const Image &I1,const Image &I2,int nframes){
    Video aux;
    if(I1.get_cols()==I2.get_cols() && I1.get_rows()==I2.get_rows())
    {
        int row = I1.get_rows();
        int col = I1.get_cols();

        for(int i=0; i<nframes; i++)
        {
            float t = (i/ (float)nframes);
            Image Iaux(I1.get_rows(),I1.get_cols());

            for(int j=0; j < row; j++)
            {
                for(int k=0; k < col; k++)
                {
                    int index = k + j*I1.get_cols();
                    pixel morphed_pixel=I1.get_pixel(index)*(1-t)+I2.get_pixel(index)*t;

                    Iaux.set_pixel(j,k,morphed_pixel);

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
   * @brief Carga las imágenes, crea el vídeo y lo guarda en el directorio
   * @param argv Fichero de origen, fichero destino, directorio de salida, número de fotogramas
   * @pre Las imágenes deben de existir y ser .pgm, directorio de salida debe existir, nfotogramas > 0
   * @return 0 si ejecución correcta, 1 si no
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
