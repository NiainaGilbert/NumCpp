#pragma once

#include <numeric>

namespace np
{
    //setter
    template <typename T>
    void Ndarrays<T>::setData(std::vector<T> donnees)
    {
        data = donnees;
    }

    template <typename T>
    void Ndarrays<T>::setDimensions(std::vector<size_t> donnees)
    {
        dimensions = donnees;
    }

    template <typename T>
    void Ndarrays<T>::setStrides(std::vector<size_t> donnees)
    {
        strides = donnees;
    }

    //getter
    template <typename T>
    std::vector<T> Ndarrays<T>::getData()
    {
        return (data);
    }

    template <typename T>
    std::vector<size_t> Ndarrays<T>::getDimensions()
    {
        return (dimensions);
    }

    template <typename T>
    std::vector<size_t> Ndarrays<T>::getStrides()
    {
        return (strides);
    }

    // Calcule la taille totale et valide les dimensions
    template <typename T>
    size_t Ndarrays<T>::compute_total_size(const std::vector<size_t>& dim) 
    {
        size_t totalSize = dim.empty() ? 1 : 1;
        for (size_t i : dim) 
        {
            if (i == 0) 
            {
                throw std::invalid_argument("Dimensions must be positive");
            }
            totalSize *= i;
        }
        return totalSize;
    }

    // Initialise data
    template <typename T>
    void Ndarrays<T>::initialize_data(T* buffer, size_t totalSize) 
    {
        data.resize(totalSize);
        if (buffer) 
        {
            std::copy(buffer, buffer + totalSize, data.begin());
        }
    }

    // Initialise strides
    template <typename T>
    void Ndarrays<T>::initialize_strides(const std::vector<size_t>& forStrides) 
    {
        if (forStrides.size() == dimensions.size()) 
        {
            strides = forStrides;
        } 
        else 
        {
            if (order == 'C') 
                computeStrides();

            else 
                computeStridesFortran();

        }
    }

    // Constructeur 1 : dim, [forOrder]
    template <typename T>
    Ndarrays<T>::Ndarrays(std::vector<size_t> dim, char forOrder)
        : dimensions(dim), order(forOrder)
    {
        if (forOrder != 'C' && forOrder != 'F') 
        {
            throw std::invalid_argument("Order must be 'C' or 'F'");
        }
        size_t totalSize = compute_total_size(dim);
        initialize_data(nullptr, totalSize);
        initialize_strides({});
    }

    // Constructeur 2 : dim, forStrides, [forOrder]
    template <typename T>
    Ndarrays<T>::Ndarrays(std::vector<size_t> dim, std::vector<size_t> forStrides, char forOrder)
        : dimensions(dim), order(forOrder)
    {
        if (forOrder != 'C' && forOrder != 'F') 
        {
            throw std::invalid_argument("Order must be 'C' or 'F'");
        }
        size_t totalSize = compute_total_size(dim);
        initialize_data(nullptr, totalSize);
        initialize_strides(forStrides);
    }

    // Constructeur 3 : dim, forBuffer, [forOrder]
    template <typename T>
    Ndarrays<T>::Ndarrays(std::vector<size_t> dim, T* forBuffer, char forOrder)
        : dimensions(dim), order(forOrder)
    {
        if (forOrder != 'C' && forOrder != 'F') 
        {
            throw std::invalid_argument("Order must be 'C' or 'F'");
        }
        size_t totalSize = compute_total_size(dim);
        initialize_data(forBuffer, totalSize);
        initialize_strides({});
    }

    // Constructeur 4 : dim, forBuffer, forStrides, [forOrder]
    template <typename T>
    Ndarrays<T>::Ndarrays(std::vector<size_t> dim, T* forBuffer, std::vector<size_t> forStrides, char forOrder)
        : dimensions(dim), order(forOrder)
    {
        if (forOrder != 'C' && forOrder != 'F') 
        {
            throw std::invalid_argument("Order must be 'C' or 'F'");
        }
        size_t totalSize = compute_total_size(dim);
        initialize_data(forBuffer, totalSize);
        initialize_strides(forStrides);
    }

    // Constructeur 5 : dim, forBuffer, forOffset, [forOrder]
    template <typename T>
    Ndarrays<T>::Ndarrays(std::vector<size_t> dim, T* forBuffer, size_t forOffset, char forOrder)
        : dimensions(dim), order(forOrder)
    {
        if (forOrder != 'C' && forOrder != 'F') 
        {
            throw std::invalid_argument("Order must be 'C' or 'F'");
        }
        size_t totalSize = compute_total_size(dim);
        if (forOffset >= totalSize) 
        {
            throw std::invalid_argument("Offset exceeds total size");
        }
        initialize_data(forBuffer ? forBuffer + forOffset : nullptr, totalSize);
        initialize_strides({});
    }

    // Constructeur 6 : dim, forBuffer, forOffset, forStrides, [forOrder]
    // Exemple : Ndarrays<int>({2, 2}, buffer, 1, {2, 1}) -> forOrder = 'C'
    template <typename T>
    Ndarrays<T>::Ndarrays(std::vector<size_t> dim, T* forBuffer, size_t forOffset, std::vector<size_t> forStrides, char forOrder)
        : dimensions(dim), order(forOrder)
    {
        if (forOrder != 'C' && forOrder != 'F') 
        {
            throw std::invalid_argument("Order must be 'C' or 'F'");
        }
        size_t totalSize = compute_total_size(dim);
        if (forOffset >= totalSize) 
        {
            throw std::invalid_argument("Offset exceeds total size");
        }
        initialize_data(forBuffer ? forBuffer + forOffset : nullptr, totalSize);
        initialize_strides(forStrides);
    }

    template <typename T>
    void Ndarrays<T>::computeStrides() 
    {
        if (dimensions.empty()) 
        {
            strides = {};
            return;
        }
        size_t stride = 1;
        strides.resize(dimensions.size());
        for (int i = dimensions.size() - 1; i >= 0; --i) {
            strides[i] = stride;
            stride *= dimensions[i];
        }
    }

    template <typename T>
    void Ndarrays<T>::computeStridesFortran() 
    {
        if (dimensions.empty()) 
        {
            strides = {};
            return;
        }
        size_t stride = 1;
        strides.resize(dimensions.size());
        for (size_t i = 0; i < dimensions.size(); ++i) 
        {
            strides[i] = stride;
            stride *= dimensions[i];
        }
    }

    template <typename T>
    T& Ndarrays<T>::operator()(std::vector<size_t>& index) 
    {
        if (index.size() != dimensions.size()) 
        {
            throw std::out_of_range("Incorrect number of indices");
        }
        size_t flatIndex = 0;
        for (size_t i = 0; i < index.size(); ++i) 
        {
            if (index[i] >= dimensions[i]) 
            {
                throw std::out_of_range("Index out of range");
            }
            flatIndex += index[i] * strides[i];
        }
        return data[flatIndex];
    }

    template <typename T>
    std::vector<size_t> Ndarrays<T>::shape() 
    {
        return dimensions;
    }

    template <typename T>
    void Ndarrays<T>::reshape(std::vector<size_t> dim) 
    {
        size_t totalSize = compute_total_size(dim);
        if (totalSize != data.size()) 
        {
            throw std::invalid_argument("Cannot reshape array to different size");
        }
        dimensions = dim;
        computeStrides();
    }

    template <typename T>
    void Ndarrays<T>::resize(std::vector<size_t> dim) 
    {
        size_t totalSize = compute_total_size(dim);
        dimensions = dim;
        data.resize(totalSize);
        computeStrides();
    }

    template <typename T>
    void Ndarrays<T>::printDim() 
    {
        std::cout << "Dim: (";
        for (size_t i = 0; i < dimensions.size(); ++i) 
        {
            std::cout << dimensions[i];
            if (i < dimensions.size() - 1) std::cout << ", ";
        }
        std::cout << ")" << std::endl;
    }

    template <typename T>
    void Ndarrays<T>::printData() 
    {
        std::cout << "Data: [ ";
        for (const auto& i : data) 
        {
            std::cout << i << " ";
        }
        std::cout << "]" << std::endl;
    }

    template <typename T>
    size_t Ndarrays<T>::size() 
    {
        return data.size();
    }

    template <typename T>
    bool Ndarrays<T>::empty() 
    {
        return data.empty();
    }

    template <typename T>
    void Ndarrays<T>::fill(T value) 
    {
        std::fill(data.begin(), data.end(), value);
    }

    template <typename T>
    void Ndarrays<T>::clear() 
    {
        data.clear();
        strides.clear();
        dimensions.clear();
    }

    template <typename T>
    bool Ndarrays<T>::operator==(Ndarrays<T> &other) 
    {
        return data == other.data && dimensions == other.dimensions;
    }

    template <typename T>
    bool Ndarrays<T>::operator!=(Ndarrays<T> &other) 
    {
        return data != other.data || dimensions != other.dimensions;
    }

    template <typename T>
    auto Ndarrays<T>::begin() 
    {
        return data.begin();
    }

    template <typename T>
    auto Ndarrays<T>::end() 
    {
        return data.end();
    }

    template <typename T>
    Ndarrays<T> Ndarrays<T>::copy() 
    {
        Ndarrays<T> other(dimensions, order);
        other.data = data;
        other.strides = strides;
        return other;
    }

    template <typename T>
    T Ndarrays<T>::min() 
    {
        if(data.empty())
        {
            throw std::out_of_range("The array is empty");
        }
        return *std::min_element(data.begin(), data.end());
    }

    template <typename T>
    T Ndarrays<T>::max() 
    {
        if(data.empty())
        {
            throw std::out_of_range("The array is empty");
        }
        return *std::max_element(data.begin(), data.end());
    }

    template <typename T>
    T Ndarrays<T>::sum() 
    {
        return std::accumulate(data.begin(), data.end(), T(0));
    }

    template <typename T>
    float Ndarrays<T>::mean() 
    {
        return (((float)sum)/(float)data.size());
    }

    template <typename T>
    T Ndarrays<T>::front() 
    {
        return data.front();
    }

    template <typename T>
    T Ndarrays<T>::back() 
    {
        return data.back();
    }

    template <typename T>
    size_t Ndarrays<T>::count(T value) 
    {
        return std::count(data.begin(), data.end(), value);
    }

    template <typename T>
    std::vector<T> Ndarrays<T>::flatten() 
    {
        return data;
    }

    template <typename U>
    void get_shape(const U& nested, std::vector<size_t>& shape) 
    {
        if constexpr (is_container<U>::value) 
        {
            size_t size = std::distance(nested.begin(), nested.end());
            if (size > 0) 
            {
                shape.push_back(size);
                get_shape(*nested.begin(), shape);
            }
        }
    }

    template <typename T, typename U>
    void flatten_recursive(const U& nested, std::vector<T>& flat_data, const std::vector<size_t>& dims, size_t depth) 
    {
        if constexpr (is_container<U>::value) 
        {
            size_t size = std::distance(nested.begin(), nested.end());
            if (depth < dims.size() && size > 0 && size != dims[depth]) 
            {
                throw std::invalid_argument("Inconsistent shape at depth " + std::to_string(depth));
            }
            for (const auto& sub : nested) 
            {
                flatten_recursive<T>(sub, flat_data, dims, depth + 1);
            }
        } 
        else 
        {
            flat_data.push_back(static_cast<T>(nested));
        }
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<T> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.setData(flat_data);
        result.setStrides(result.getStrides());
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<T>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.setData(flat_data);
        result.setStrides(result.getStrides());
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<T>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.setData(flat_data);
        result.setStrides(result.getStrides());
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.setData(flat_data);
        result.setStrides(result.getStrides());
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.data = flat_data;
        result.strides = result.strides;
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.data = flat_data;
        result.strides = result.strides;
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.data = flat_data;
        result.strides = result.strides;
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.data = flat_data;
        result.strides = result.strides;
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.data = flat_data;
        result.strides = result.strides;
        return result;
    }

    template <typename T>
    Ndarrays<T> array(std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>>>>>>> init_list) 
    {
        std::vector<size_t> dims;
        get_shape(init_list, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(init_list, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.data = flat_data;
        result.strides = result.strides;
        return result;
    }

    template <typename U, typename T>
    std::enable_if_t<is_container<U>::value, Ndarrays<T>>
    array(const U& nested) 
    {
        std::vector<size_t> dims;
        get_shape(nested, dims);
        std::vector<T> flat_data;
        flatten_recursive<T>(nested, flat_data, dims, 0);
        Ndarrays<T> result(dims);
        result.setData(flat_data);
        result.setStrides(result.getStrides());
        return result;
    }

    template <typename T, typename U>
    std::enable_if_t<!is_container<U>::value && std::is_convertible_v<U, T>, Ndarrays<T>>
    array(const U& scalar) 
    {
        std::vector<size_t> dims;
        std::vector<T> flat_data = {static_cast<T>(scalar)};
        Ndarrays<T> result(dims);
        result.data = flat_data;
        result.strides = result.strides;
        return result;
    }

    template <typename T>
    std::vector<T> Ndarrays<T>::ravel()
    {
        return (getData());
    }
    template <typename T>
    Ndarrays<T> empty(std::vector<size_t> dim, char ordre) 
    {
        return Ndarrays<T>(dim, ordre);
    }

    template <typename T>
    Ndarrays<T> zeros(std::vector<size_t> dim, char ordre) 
    {
        Ndarrays<T> result(dim, ordre);
        result.fill(0);
        return (result);
    }

    template <typename T>
    Ndarrays<T> ones(std::vector<size_t> dim, char ordre) 
    {
        Ndarrays<T> result(dim, ordre);
        result.fill(1);
        return (result);
    }

    template <typename T>
    Ndarrays<T> add(Ndarrays<T>& a, Ndarrays<T>& b) 
    {
        std::vector<T> tmp;
        if(a.getDimensions()!=b.getDimensions())
        {
            throw std::invalid_argument("a and b have different dimensions.\n");
        }
        for(int i = 0; i<a.getDimension().size(); i++)
        {
            tmp.push_back(a.getData[i]+b.getData()[i]);
        }
        auto result = array(tmp);
        return (result);
    }
    template <typename T>
    Ndarrays<T> substract(Ndarrays<T>& a, Ndarrays<T>& b) 
    {
        std::vector<T> tmp;
        if(a.getDimensions()!=b.getDimensions())
        {
            throw std::invalid_argument("a and b have different dimensions.\n");
        }
        for(int i = 0; i<a.getDimension().size(); i++)
        {
            tmp.push_back(a.getData[i]-b.getData()[i]);
        }
        auto result = array(tmp);
        return (result);
    }

///biby b
template <typename T>
void Ndarrays<T>::print(int indent, const std::string& prefix) 
{
    // Fonction auxiliaire pour afficher récursivement
    auto print_recursive = [&](const auto& self, const std::vector<T>& data, size_t data_offset,
                              const std::vector<size_t>& dims, size_t dim_idx, int current_indent) -> void {
        // Indentation
        std::string indent_str(current_indent, ' ');

        // Cas de base : dimension scalaire ou dernière dimension
        if (dim_idx == dims.size() - 1 || dims.empty()) 
        {
            std::cout << indent_str << "[";
            size_t size = dims.empty() ? 1 : dims[dim_idx];
            for (size_t i = 0; i < size; ++i) 
            {
                std::cout << data[data_offset + i * (dims.empty() ? 1 : strides[dim_idx])];
                if (i < size - 1) std::cout << ", ";
            }
            std::cout << "]";
            return;
        }

        // Dimension non terminale : afficher des sous-arrays
        std::cout << indent_str << "[";
        size_t stride = strides[dim_idx];
        for (size_t i = 0; i < dims[dim_idx]; ++i) 
        {
            if (i > 0) 
            {
                std::cout << ",";
                if (dim_idx + 1 < dims.size()) 
                {
                    std::cout << "\n" << indent_str;
                } 
                else 
                {
                    std::cout << " ";
                }
            }
            self(self, data, data_offset + i * stride, dims, dim_idx + 1, current_indent + 2);
        }
        std::cout << "]";
    };

    // Afficher le préfixe (par exemple, "array(")
    std::cout << prefix;

    // Cas spécial : array vide
    if (data.empty()) {
        std::cout << "[]";
        return;
    }

    // Appeler la fonction récursive
    print_recursive(print_recursive, data, 0, dimensions, 0, indent);

    // Ajouter une nouvelle ligne à la fin
    std::cout << std::endl;
}
}

