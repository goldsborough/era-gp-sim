#include "memory.hpp"

#include <iostream>

Memory::Memory(int length,int width,endian e){
    std::cout<<length << "; " << width << "; " << std::endl;
}

Memory::Memory(int length,endian e):Memory(length,8,e){}

MemoryValue Memory::get(const int adress, const int length)const{
    return MemoryValue{};
}

void Memory::set(const int adress,const MemoryValue& value){
}
