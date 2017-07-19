#include <iostream>
#include <memory>
#include <array>
int main()
{
    std::array<char,128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen("cat 'rubikcubeidkimbad;-;'.cpp", "r"), pclose);
    if (!pipe) return 1;
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr){
            result=buffer.data();
        }
    }
    std::cout<<result;
}