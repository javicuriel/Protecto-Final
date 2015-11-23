#include "lectorarchivos.h"

LectorArchivos::LectorArchivos()
{

}

LectorArchivos::~LectorArchivos()
{
    myfile.close();
}

std::vector<int> LectorArchivos::leer(std::string archivo)
{
    std::string line;
    myfile.open(archivo, std::ios::out);


    while ( getline (myfile,line) ){
        int num = std::stoi(line);
        datos.push_back(num);
    }

    return datos;

}

