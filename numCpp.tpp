template <typename T>
void ndarrays<T>::computeStrides() {
    size_t stride = 1;  // Changé int en size_t pour cohérence
    strides.resize(dimensions.size());
    for (int i = dimensions.size() - 1; i >= 0; --i) 
    {
        strides[i] = stride;
        stride *= dimensions[i];
    }
}

template <typename T>
ndarrays<T>::ndarrays(std::vector<size_t> dim) {
    size_t totalSize = 1; 
    dimensions = dim;
    for (auto i : dim) {
        totalSize *= i;
    }
    data.resize(totalSize, 0);
    computeStrides();
}

template <typename T>
T& ndarrays<T>::operator()(std::vector<size_t>& index) 
{
    size_t flatIndex = 0;
    if (index.size() != dimensions.size()) {  // Corrigé "dim" en "index"
        throw std::out_of_range("Incorrect number of indices");
    }
    for (size_t i = 0; i < index.size(); ++i) {  // Changé int en size_t
        if (index[i] >= dimensions[i]) {  // Simplifié : size_t est non signé
            throw std::out_of_range("Index out of range");
        }
        flatIndex += index[i] * strides[i];
    }
    return data[flatIndex];  // Retourne une référence (parenthèses inutiles)
}
template <typename T>
std::vector<size_t> ndarrays<T>::shape()
{
    return (dimensions);
}
template <typename T>
void ndarrays<T>::reshape(std::vector<size_t> dim)
{
    size_t totalSize(1);
    for(auto i : dim)
    {
        totalSize*=i;
    }
    if(totalSize!=data.size())
    {
        std::cerr << "ValueError: cannot reshape array\n"; //of size "<< dimensions << " into shape " << dim << std::endl;
    }
    else
    {
        dimensions=dim;
        computeStrides();
    }
}
template <typename T>
void ndarrays<T>::resize(std::vector<size_t> dim)
{
    size_t totalSize(1);
    dimensions.resize(dim.size());
    for (size_t i = 0; i < dim.size(); i++)
    {
        dimensions[i]=dim[i];
        totalSize*=dim[i];
    }
    computeStrides();
    data.resize(totalSize, 0);
    
}
template <typename T>
void ndarrays<T>::printDim()
{
    for(auto i : dimensions)
    {
        std::cout << i << std::endl; 
    }
}
template <typename T>
void ndarrays<T>::printData()
{
    for(auto i : data)
    {
        std::cout << i << " "; 
    }
    std::cout << std::endl;
}