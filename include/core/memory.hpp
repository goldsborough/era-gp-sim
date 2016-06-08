#ifndef ERAGPSIM_CORE_MEMORY_H
#define ERAGPSIM_CORE_MEMORY_H

#include <vector>

//#include "memoryvalue.hpp"
typedef std::vector<bool> MemoryValue;

enum class endian{kLittleEndian,kBigEndian};

class Memory{
public:
  //Creates a new virtual memory object with 'length' memory cells of width
  //'width' with endianness 'endianness'
  Memory(int,int,endian);
  //Creates a new virtual memory object with 'length' memory cells of width
  //8 with endianness 'endianness'
  Memory(int,endian);
  //destructor
  ~Memory()=default;

  //Return the value of the 'length' memory cells after the memory cell at
  //'adress'
  MemoryValue get(const int, const int=1)const;
  //Sets the value of the memory cells after the memory cell at 'adress' to
  //'value'
  void set(const int,const MemoryValue&);
};

#endif // ERAGPSIM_CORE_MEMORY_H
