#include "video.h"
//COMPLETAR POR EL ESTUDIANTE

void read_directory(const std::string& name, vector<string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_name)
        v.push_back(dp->d_name);
        cout << "read_dir añadiendo archivo: " <<  dp->d_name << endl;

    }
    closedir(dirp);
}


Video::Video(): seq() {}

Video::Video(): seq() {}

/**************************************************/
Video::Video(int n){
    seq.resize(n);
    seq.resize(n);
}
/**************************************************/
Video::Video(const Video &V){
    seq.resize(V.size());
    for(int i=0; i<V.size(); i++)
    {
        seq[i]=V[i];
    }
    seq.resize(V.size());
    for(int i=0; i<V.size(); i++)
    {
        seq[i]=V[i];
    }

}
/**************************************************/
Video::~Video(){}
/**************************************************/
Video &Video::operator=(const Video &V){
    if(this != &V) {
        seq = V.seq;
    }
    return *this;
    if(this != &V) {
        seq = V.seq;
    }
    return *this;
}
/**************************************************/
int Video::size() const{
    return seq.size();
}
/**************************************************/
Image &Video::operator[](int foto){
    return seq[foto];
}

const Image &Video::operator[](int foto)const{
    return seq[foto];
}

void Video::Insertar(int k, const Image &I){
    seq.insert(seq.begin()+k, I);
    seq.insert(seq.begin()+k, I);

}

void Video::Borrar(int k){
    seq.erase(seq.begin()+k);
    seq.erase(seq.begin()+k);
}

bool Video::LeerVideo(const string &path){
    vector<string> Dir;
    cout << "video path: " << path << endl;
    read_directory(path, Dir);
    bool leido=true;
    cout << "Dir size" << Dir.size() << endl;

    for(int i=2; i<Dir.size()-1 && leido==true; i++)
    {
        Image aux;
        cout << "antes Load(): " << Dir[i].c_str() << endl;
        if(aux.Load(Dir[i].c_str()))
        {
            seq.push_back(aux);
        }
        else{
            cout << "Error en fichero: " << Dir[i].c_str() << endl;
            leido=false;
        }
    }
    return leido;
    return leido;
}

bool Video::EscribirVideo(const string & path, const string &prefijo)const{

    bool exito=true;
    std::filesystem::path filepath =path;
    bool filepathExists = std::filesystem::is_directory(filepath);

    if (!filepathExists){

        bool created_new_directory= std::filesystem::create_directory(filepath);
        if (!created_new_directory){
            cout<<"No se puede crear el directorio "<<path<<endl;
            return false;
        }
        else{
            cout<<" Se ha creado el directorio "<< path<<endl;
        }
    }

    for(int i=0; i<seq.size(); i++)
    {
        string out_path = path + prefijo + to_string(i);
        if(!seq[i].Save((out_path.c_str()))) {
            cout << "Error escribiendo el video" << out_path << endl;
            exito = false;
        }
        if(!seq[i].Save((out_path.c_str()))) {
            cout << "Error escribiendo el video" << out_path << endl;
            exito = false;
        }
    }
    return exito;
    return exito;
}
