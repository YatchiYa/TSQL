#include <iostream>
#include <string>
#include <istream>  // ofstream for writing in file


#include "../dataH/test2.h"

#include <boost/filesystem.hpp>


void test2(){

    std::string const file("dataBase/dataMemory.txt");
    // boost::filesystem::path path1("C:\\memory.txt"); // our file
    std::ifstream flux(file.c_str());

    if(flux){
        std::cout << "file is open !!" << std::endl;
    }
    else{
        std::cout << "file is not open, an error occured while opening the file " << std::endl;
    }

}
