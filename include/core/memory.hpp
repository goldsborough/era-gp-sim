#ifndef ERAGPSIM_CORE_MEMORY_H
#define ERAGPSIM_CORE_MEMORY_H

#include <vector>

#include "memoryvalue.hpp"
#include "memoryarray.hpp"
//typedef std::vector<bool> MemoryValue;//This WILL create bugs

enum class endian{kLittleEndian,kBigEndian};

//the simulated RAM
class Memory{
public:
  //Creates a new virtual memory object with 'length' memory cells of width
  //'width' with endianness 'endianness'
  Memory(int length, int width, endian endianness);
  //Creates a new virtual memory object with 'length' memory cells of width
  //8 with endianness 'endianness'
  Memory(int length, endian endianness);
  //destructor
  ~Memory()=default;

  //Return the value of the 'length' memory cells after the memory cell at
  //'adress'
  MemoryValue get(const int adress, const int length=1)const;
  //Sets the value of the memory cells after the memory cell at 'adress' to
  //'value'
  void put(const int adress,const MemoryValue& value);
  //Sets the value of the memory cells after the memory cell at 'adress' to
  //'value' and returns its previous value
  MemoryValue set(const int adress,const MemoryValue& value);
private:
  const endian _endianness;
  const int _length;
  const int _width;
  const int _byteLength;
  MemoryArray _memoryArray;
};

#endif // ERAGPSIM_CORE_MEMORY_H
