#include "Ndarrays.h"

int main() {
 //   try {
        // 1D array using initializer_list
        auto a1 = np::array({1, 2, 3, 4});
        std::cout << "1D array (initializer_list):" << std::endl;
        std::cout << a1({1, 2});
/*
        // 2D array using initializer_list
        auto a2 = np::array({{1, 2}, {3, 4}});
        std::cout << "\n2D array (initializer_list):" << std::endl;
        a2.print(0, "");  // Dim: (2, 2)
        a2.printData(); // Data: [ 1 2 3 4 ]

        // 3D array using initializer_list
        auto a3 = np::array({{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}});
        std::cout << "\n3D array (initializer_list):" << std::endl;
        a3.printDim();  // Dim: (2, 2, 2)
        a3.printData(); // Data: [ 1 2 3 4 5 6 7 8 ]

        // 4D array using initializer_list
        auto a4 = np::array({{{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}},
                             {{{9, 10}, {11, 12}}, {{13, 14}, {15, 16}}}});
        std::cout << "\n4D array (initializer_list):" << std::endl;
        a4.printDim();  // Dim: (2, 2, 2, 2)
        a4.printData(); // Data: [ 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 ]

        // 3D array using std::vector
        std::vector<std::vector<std::vector<int>>> vec3d = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
        auto a3_vec = np::array(vec3d);
        std::cout << "\n3D array (std::vector):" << std::endl;
        a3_vec.printDim();  // Dim: (2, 2, 2)
        a3_vec.printData(); // Data: [ 1 2 3 4 5 6 7 8 ]

        // 4D array using std::vector
        std::vector<std::vector<std::vector<std::vector<int>>>> vec4d = {{{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}},
                                                                        {{{9, 10}, {11, 12}}, {{13, 14}, {15, 16}}}};
        auto a4_vec = np::array(vec4d);
        std::cout << "\n4D array (std::vector):" << std::endl;
        a4_vec.printDim();  // Dim: (2, 2, 2, 2)
        a4_vec.printData(); // Data: [ 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 ]

        // 6D array using std::vector
        std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>>> vec6d = {
            {{{{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}},
              {{{9, 10}, {11, 12}}, {{13, 14}, {15, 16}}}},
             {{{{17, 18}, {19, 20}}, {{21, 22}, {23, 24}}},
              {{{25, 26}, {27, 28}}, {{29, 30}, {31, 32}}}}},
            {{{{{33, 34}, {35, 36}}, {{37, 38}, {39, 40}}},
              {{{41, 42}, {43, 44}}, {{45, 46}, {47, 48}}}},
             {{{{49, 50}, {51, 52}}, {{53, 54}, {55, 56}}},
              {{{57, 58}, {59, 60}}, {{61, 62}, {63, 64}}}}}
        };
        auto a6_vec = np::array(vec6d);
        std::cout << "\n6D array (std::vector):" << std::endl;
        a6_vec.printDim();  // Dim: (2, 2, 2, 2, 2, 2)
        a6_vec.printData(); // Data: [ 1 2 3 4 ... 63 64 ]


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
*/
    return 0;
}