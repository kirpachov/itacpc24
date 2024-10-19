#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> cf;
    size_t argc;
    std::cin >> argc;
    std::vector<int> sizes;

    for (size_t i = 0; i < argc; i++) {
        std::string arg;
        std::cin >> arg;
        cf.push_back(arg);

        if (arg == std::string{"espresso"} || arg == std::string{"cappuccino"}) {
          sizes.push_back(1);
        } else if (arg == std::string{"espresso-doppio"} || arg == std::string{"affogato"} || arg == std::string{"irish-coffee"}) {
          sizes.push_back(2);
        } else if (arg == std::string{"dead-eye"}) {
          sizes.push_back(3);
        } else {
          std::cout << "Invalid drink \"" << arg << "\"" << std::endl;
          return 1;
        }
    }

    // for (int i = 0; i < cf.size(); i++) {
    //     std::cout << "i:" << i << " (" << sizes[i] << ") " << cf[i] << std::endl;
    // }

    size_t sum = 0;
    for (size_t i = 0; i < sizes.size(); i++) {
        sum += sizes[i];
    }

    std::cout << ((sum % 2) + sum / 2) << std::endl;

    return 0;
}