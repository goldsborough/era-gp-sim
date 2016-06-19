#include "memory.hpp"

#include <iostream>

Memory::Memory(int length,int width,endian endianness):
  _length{length},
  _width{width},
  _endianness{endianness},
  _byteLength{width/8+((width%8>0)?1:0)},
  _memoryArray{length,_byteLength}{
  _memoryArray.reset();
}

Memory::Memory(int length,endian endianness):Memory(length,8,endianness){}

MemoryValue Memory::get(const int address, const int length)const{
  MemoryValue res{_width*length};
  for(int i=0;i<length;++i){//I'm ignoring endianness for now, because I want to give everyone a chance to read this before i wreck this
    std::unique_ptr<char[]> data{_memoryArray.get(address+i)};
    for(int j=0;j<_width;j++)res[i*_width+j]=((data.get()[j/8]>>(j%8))&1)==1;
  }
  return res;
}

void Memory::put(const int address,const MemoryValue& value){
  for(int i=0;i<value.size()/_width;++i){//Yes, still ignoring any endianness, because still this is kinda not trivial
    char temp[_byteLength];
    for(int j=0;j<_byteLength;++j)temp[j]=0;
    for(int j=_width-1;j>=0;--j){//This is the poor excuse of a loop that is the alternative to the version I like to use. It is ugly!
      temp[j/8]<<=1;
      temp[j/8]+=value[i*_width+j];
    }
    _memoryArray.put(address,temp);
  }
}
MemoryValue Memory::set(const int adress, const MemoryValue& value){
  MemoryValue res{get(adress,value.size()/_width)};
  put(adress,value);
  return res;
}
