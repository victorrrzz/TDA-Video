#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
using namespace std;
Video Morphing(const Image &I1,const Image &I2,int nframes){
Video aux(nframes);
if ( I1.get_cols() != I2.get_cols() ||I1.get_rows() != I2.get_rows())
{
    cout << "Error: Las imágenes no tienen dimensiones iguales\n";
    exit(1);
}
 for (int i = 0; i < nframes; i++)
 {
    float t = (i / (float)nframes);
    for (int j = 0; j < I1.get_rows(); j++)
    {
        for (int k = 0; k < I1.get_cols(); k++)
        {
            int index = k + j*I1.get_cols();
            pixel morphed_pixel = I1.get_pixel(index) * (1-t) + 
                                  I2.get_pixel(index) * (t);
            aux[i].set_pixel(j, k, morphed_pixel);
        }
    }
 }

}

int main(int argc, char * argv[]){
//RELLENAR POR EL ESTUDIANTE
}
