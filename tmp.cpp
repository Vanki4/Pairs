#include <fstream>

int main() {
    std::ofstream file("data.bin",std::ios::binary);
    int x = 0;
    file.write(reinterpret_cast<char*>(&x),sizeof(x));
    file.close();
    return 0;
}