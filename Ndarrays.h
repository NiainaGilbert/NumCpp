#ifndef NDARRAYS_H
#define NDARRAYS_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <initializer_list>

namespace np
{
    // Trait mcheck oe conatainer sa tsia
    template <typename T, typename = void>
    struct is_container : std::false_type {};

    template <typename T>
    struct is_container<T, std::void_t<
        typename T::value_type,
        decltype(std::declval<T>().size()),
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
    >> : std::true_type {};

    template <typename T>
    struct is_container<std::initializer_list<T>> : std::true_type {};

    // Trait to get the base type of a nested container
    template <typename T>
    struct base_type 
    {
        using type = T;
    };

    template <typename T>
    struct base_type<std::vector<T>> 
    {
        using type = typename base_type<T>::type;
    };

    template <typename T>
    struct base_type<std::initializer_list<T>> 
    {
        using type = typename base_type<T>::type;
    };

    template <typename T>
    using base_type_t = typename base_type<T>::type;

    // fonctions arrays
    template <typename U>
    void get_shape(const U& nested, std::vector<size_t>& shape);

    template <typename T, typename U>
    void flatten_recursive(const U& nested, std::vector<T>& flat_data, const std::vector<size_t>& dims, size_t depth = 0);

    template <typename T>
    class Ndarrays
    {
    private:
        std::vector<size_t> strides;
        std::vector<T> data;
        std::vector<size_t> dimensions;
        char order;

        // Fonctions privées pour centraliser l'initialisation
        size_t compute_total_size(const std::vector<size_t>& dim);
        void initialize_data(T* buffer, size_t totalSize);
        void initialize_strides(const std::vector<size_t>& forStrides);

    public:
        //setter
        void setData(std::vector<T> donnees);
        void setDimensions(std::vector<size_t> donnees);
        void setStrides(std::vector<size_t> donnees);

        //getter
        std::vector<T> getData();
        std::vector<size_t> getDimensions();
        std::vector<size_t> getStrides();

        // Constructeurs
        Ndarrays(std::vector<size_t> dim, char forOrder = 'C'); // dim, [forOrder]
        Ndarrays(std::vector<size_t> dim, std::vector<size_t> forStrides, char forOrder = 'C'); // dim, forStrides, [forOrder]
        Ndarrays(std::vector<size_t> dim, T* forBuffer, char forOrder = 'C'); // dim, forBuffer, [forOrder]
        Ndarrays(std::vector<size_t> dim, T* forBuffer, std::vector<size_t> forStrides, char forOrder = 'C'); // dim, forBuffer, forStrides, [forOrder]
        Ndarrays(std::vector<size_t> dim, T* forBuffer, size_t forOffset, char forOrder = 'C'); // dim, forBuffer, forOffset, [forOrder]
        Ndarrays(std::vector<size_t> dim, T* forBuffer, size_t forOffset, std::vector<size_t> forStrides, char forOrder = 'C'); // dim, forBuffer, forOffset, forStrides, [forOrder]

        void computeStrides();
        void computeStridesFortran();
        std::vector<size_t> shape();
        std::vector<T> ravel();
        void reshape(std::vector<size_t> dim);
        void resize(std::vector<size_t> dim);
        size_t size();
        T min();
        T max();
        bool empty();
        void fill(T value);
        void clear();
        auto begin();
        auto end();
        Ndarrays<T> copy();
        bool operator!=(Ndarrays<T> &other);
        bool operator==(Ndarrays<T> &other);
        T sum();
        float mean(); 
        T front();
        T back();
        size_t count(T value);
        void printDim();
        void printData();
        T& operator()(std::vector<size_t>& index);
        std::vector<T> flatten();
        void print(int indent, const std::string& prefix);
    };

//Surcharge anle initializer_list mba itovitovy @le numpy
    template <typename T>
    Ndarrays<T> array(std::initializer_list<T> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<T>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<T>>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>>>> init_list);

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>>>>> init_list);

    // array rah conteneurs le paramètre
    template <typename U, typename T = base_type_t<U>>
    std::enable_if_t<is_container<U>::value, Ndarrays<T>> array(const U& nested);

    // rah nombre tsotra
    template <typename T, typename U>
    std::enable_if_t<!is_container<U>::value && std::is_convertible_v<U, T>, Ndarrays<T>> array(const U& scalar);

    //fonctions fanampiny
    template <typename T>
    Ndarrays<T> empty(std::vector<size_t> dim, char ordre = 'C');
    template <typename T>
    Ndarrays<T> zeros(std::vector<size_t> dim, char ordre = 'C');
    template <typename T>
    Ndarrays<T> ones(std::vector<size_t> dim, char ordre = 'C');

    template <typename T>
    Ndarrays<T> add(Ndarrays<T>& a, Ndarrays<T>& b);
    template <typename T>
    Ndarrays<T> substract(Ndarrays<T>& a, Ndarrays<T>& b);

}

#include "Ndarrays.tpp"
#endif