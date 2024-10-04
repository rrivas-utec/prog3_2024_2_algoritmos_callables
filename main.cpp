#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <fstream>
#include <iterator>

struct CSumar {
    int operator()(int a, int b) { return a + b; }
};

struct CRestar {
    int operator()(int a, int b) { return a - b; }
};

void container_de_callables() {
    CSumar s1;
    std::cout << s1(10, 20) << std::endl;

    std::vector<CSumar> v1;
};

int sumar(int a, int b) { return a + b; }
int restar(int a, int b) { return a - b; }

void punteros_a_funcion() {
    int* ptr_int = nullptr;
    int x = 10;
    ptr_int = &x;
    std::cout << x << std::endl;
    std::cout << *ptr_int << std::endl;

    int(*ptr_fun)(int, int) = nullptr;
    ptr_fun = sumar;
    std::cout << sumar(10, 20) << std::endl;
    std::cout << ptr_fun(10, 20) << std::endl;

    ptr_fun = restar;
    std::cout << restar(10, 20) << std::endl;
    std::cout << ptr_fun(10, 20) << std::endl;

    std::vector<int(*)(int, int)> v1;
    v1.emplace_back(sumar);
    v1.emplace_back(restar);

    for (const auto& ptr: v1) {
        std::cout << ptr(10, 20) << std::endl;
    }

    std::vector<std::function<int(int, int)>> v2;
    v2.emplace_back(sumar);
    v2.emplace_back(restar);

    for (const auto& ptr: v1) {
        std::cout << ptr(10, 20) << std::endl;
    }
}

// Unary/Predicate Callable
void ejemplo_find() {
    std::vector v {10, 20, 30, 40};
    auto it = std::find_if(
            std::begin(v), std::end(v),
            [](auto value) {
                return value == 20;
            });
    std::cout << *it << std::endl;
}
// Binary/Predicate Callable
void ejemplo_sort() {
    std::vector v {1, 40, 2, 3, 10, 5};
    std::sort(v.begin(), v.end(),
              [](auto a, auto b) {
                return a > b;
              });
    for (const auto& item: v) {
        std::cout << item << " ";
    }
}

// Unary/Transformer
void ejemplo_transform() {
    std::vector v {10, 20, 30, 40};
    std::vector<int> v2(v.size());

    std::transform(v.begin(), v.end(), v2.begin(),
                   [](auto a) {
                        return a/10;
                    });
    for (const auto& item: v2) {
        std::cout << item << " ";
    }
}
// Binary/Transformer
void ejemplo_transform_binary() {
    std::vector v1 {10, 20, 30, 40};
    std::vector v2 {10, 20, 30, 40};
    std::vector<int> v3(4);
    std::transform(v1.begin(), v1.end(),
                   v2.begin(),
                   v3.begin(),
                   [](auto a, auto b) {
                        return a + b;
                   });
    for (const auto& item: v3) {
        std::cout << item << " ";
    }
}
// Generator
void ejemplo_generator() {
    std::vector<int> v1(50);
    std::generate(v1.begin(), v1.end(),
                  [](){
                      std::random_device rd;
                      std::uniform_int_distribution<int> dis(1, 20);
                      return dis(rd);
                  });
    for (const auto& item: v1) {
        std::cout << item << " ";
    }
}

void ejemplo_generar_archivo_aleatorio() {
    std::ofstream file("numeros.txt");

    auto generator = []() {
        std::random_device rd;
        std::uniform_int_distribution<int> dis(1, 20);
        return std::to_string(dis(rd)) + " ";
    };

    std::generate_n(
            std::ostream_iterator<std::string>(file),
            50, generator);
}

void ejemplo_leer_archivo() {
    std::ifstream file("numeros.txt");

    std::copy(
            std::istream_iterator<int>(file), std::istream_iterator<int>(),
                std::ostream_iterator<int>(std::cout, " "));
}

void ejemplo_leer_archivo_en_vector() {
    std::ifstream file("numeros.txt");
    std::vector<int> v1;
    v1.reserve(100);
    std::copy(
            std::istream_iterator<int>(file), std::istream_iterator<int>(),
            std::back_inserter(v1));

    std::cout << v1.size() << std::endl;
    for (const auto& item: v1) {
        std::cout << item << " ";
    }
}


int main() {
//    container_de_callables();
//    punteros_a_funcion();
//    ejemplo_find();
//    ejemplo_sort();
//    ejemplo_transform();
//    ejemplo_transform_binary();
//    ejemplo_generator();
//    ejemplo_generar_archivo_aleatorio();
//    ejemplo_leer_archivo();
    ejemplo_leer_archivo_en_vector();
    return 0;
}
