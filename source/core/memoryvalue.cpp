#include "memoryvalue.hpp"

MemoryValue::MemoryValue(int width):data{std::vector<bool>()}{
    for(int i=width;i-- >0;)data.push_back(false);
}

MemoryValue::MemoryValue(const std::vector<bool> data):data{data}{}

std::vector<bool>::reference MemoryValue::at(const int index){
    return data.at(index);
}

std::vector<bool>::const_reference MemoryValue::at(const int index)const{
    return data.at(index);
}

std::vector<bool>::reference MemoryValue::operator[](const int index){
    return data[index];
}

std::vector<bool>::const_reference MemoryValue::operator[](const int index)const{
    return data[index];
}

void MemoryValue::flip(){
    data.flip();
}
