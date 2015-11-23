#ifndef LECTORARCHIVOS_H
#define LECTORARCHIVOS_H

#include <fstream>
#include <iostream>
#include <vector>

class LectorArchivos
{
private:
    std::ifstream myfile;
    std::vector<int> datos;
public:
    LectorArchivos();
    ~LectorArchivos();
    std::vector<int> leer(std::string archivo);
};

#endif // LECTORARCHIVOS_H
