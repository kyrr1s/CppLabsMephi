#include "d_functions.h"

int main() {
    sparseMatrix::Matrix mainMatr = {0, 0, nullptr};
    const char* msgs[] = {"\n0.Quit", "1.Add", "2.Operation","3.Show", "4.Random generation"};
    const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
    int (*fptr[])(sparseMatrix::Matrix&) = {nullptr, D_Add, D_Operation, D_Show, D_Random};
    int rc;
    while (rc = dialog(msgs, NMsgs))
        if (fptr[rc](mainMatr))
            break;
    std::cout << "That is all! End..." << std::endl;
    eraseMatr(mainMatr);
    return 0;
}
