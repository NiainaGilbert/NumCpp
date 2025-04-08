#ifndef NUMCPP_H__  // Retiré les doubles __ (convention réservée)
#define NUMCPP_H__

#include <vector>
#include <stdexcept>  // Pour std::out_of_range
#include <iostream>

template <typename T>
class ndarrays {
private:
    std::vector<T> data;
    std::vector<size_t> strides;       // Corrigé std::std::vector
    std::vector<size_t> dimensions;    // Corrigé std::std::vector
public:
    ndarrays(std::vector<size_t> dim);  // Constructeur
    void computeStrides();
    std::vector<size_t> shape();
    void reshape(std::vector<size_t> dim);
    void resize(std::vector<size_t> dim);
    void printDim();
    void printData();
    T& operator()(std::vector<size_t>& index);  // Retourne une référence

};

#include "numCpp.tpp"  // Déplacé avant #endif

#endif