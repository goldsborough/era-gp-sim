#ifndef MEMORYARRAY_H
#define MEMORYARRAY_H
#include <memory>
#include "memoryvalue.hpp"

//Array containing the memory
class MemoryArray
{
public:
  //creates a Memory Array with 'length' cells where each cell consumes
  //'byteLength' bytes
  MemoryArray(const int length, const int byteLength);
  //destructor
  ~MemoryArray()=default;
  //returns the value of the cell at 'address'
  std::unique_ptr<char[]> get(const int address)const;
  //puts 'value' into the cell at 'address'
  void put(const int address, const char* const value);
  //sets all cells to 0
  void reset();
private:
  const int _length;
  const int _byteLength;
  char* _data;
};

#endif // MEMORYARRAY_H
