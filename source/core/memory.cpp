#include "memory.hpp"

#include <iostream>

Memory::Memory(int length,int width,endian endianness){
    std::cout<<length << "; " << width << "; " << std::endl;
}

Memory::Memory(int length,endian endianness):Memory(length,8,endianness){}

MemoryValue Memory::get(const int adress, const int length)const{
    return MemoryValue{};
}

void Memory::set(const int adress,const MemoryValue& value){
}
