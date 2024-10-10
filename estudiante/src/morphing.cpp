#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
using namespace std;
Video Morphing(const Image &I1,const Image &I2,int nframes){
    Video aux(nframes);
 for(int i=0; i<nframes; i++)
 {
     aux[i]=(I1*(1-(i/nframes)))+(I2*i)/nframes;
 }

}

int main(int argc, char * argv[]){
//RELLENAR POR EL ESTUDIANTE
}
