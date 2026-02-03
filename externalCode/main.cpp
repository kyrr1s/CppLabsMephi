#include "dialog.h"

int main() {
    std::cout << "Let's start!" << std::endl << std::endl;
    try {
        menu();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "That is all! End..." << std::endl;
    return 0;
}
