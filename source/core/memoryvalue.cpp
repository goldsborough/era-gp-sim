#include "memoryvalue.hpp"

MemoryValue::MemoryValue(int width):_data{std::vector<bool>(width,false)}{}

MemoryValue::MemoryValue(const std::vector<bool> data):_data{data}{}

std::vector<bool>::reference MemoryValue::at(const int index){
  return _data.at(index);
}

std::vector<bool>::const_reference MemoryValue::at(const int index)const{
  return _data.at(index);
}

std::vector<bool>::reference MemoryValue::operator[](const int index){
  return _data[index];
}

std::vector<bool>::const_reference MemoryValue::operator[](const int index)const
{
  return _data[index];
}

void MemoryValue::flip(){
  _data.flip();
}

bool MemoryValue::operator==(const MemoryValue& second)const{
  return _data==second._data;
}

std::ostream& operator<<(std::ostream& stream, const MemoryValue& value){
  for(bool b:value._data)if(b)stream<<'1';else stream<<'0';
  return stream;
}

int MemoryValue::size()const{
  return _data.size();
}
