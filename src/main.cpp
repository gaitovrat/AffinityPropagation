#include <iostream>

int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cerr << "Filename missing.\n";
        return 1;
    }

    std::cout << argv[1] << std::endl;
    std::cout << __FILE__ << std::endl;

    return 0;
}
