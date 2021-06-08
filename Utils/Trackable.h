// #pragma once

// #include <string>
// #include <cxxabi.h>

// class Trackable {
// public:
//     std:: string className(){
//         int status;
//         std::string demangled = abi::__cxa_demangle(typeid(A).name(),0,0,&status);
//         std::cout<<demangled<<"\t"<< quote(A) <<"\n";
//         free(demangled);
//         return 0;
//     }
// }