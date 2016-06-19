#include "memoryarray.hpp"

MemoryArray::MemoryArray(const int length, const int byteLength):
  _length{length},
  _byteLength{byteLength},
  _data{new char[_length*_byteLength]}
{}

std::unique_ptr<char[]> MemoryArray::get(const int address)const{
  std::unique_ptr<char[]> res{new char[_byteLength]};
  for(int i=0;i<_byteLength;++i) res.get()[i]=_data[_byteLength*address+i];//Just to please the audience
  return res;
}

void MemoryArray::reset(){
  for(int i=0;i<_byteLength*_length;++i) _data[i]=0;
}

void MemoryArray::put(const int address, const char* const value){
  for(int i=0;i<_byteLength;++i) _data[address*_byteLength+i]=value[i];
}
