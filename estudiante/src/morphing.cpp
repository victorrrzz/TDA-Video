#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
#include <vector>

const int n_puntos = 10;

struct Punto2D
{
    float x,y;
};

Punto2D InterpolarPunto(const Punto2D &inicio, const Punto2D &fin, float t)
{
    // Punto intermedio
    Punto2D i;
    i.x = (1 - t) * inicio.x + t * fin.x;
    i.y = (1 - t) * inicio.x + t * fin.y;
    
    return i;

}

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
