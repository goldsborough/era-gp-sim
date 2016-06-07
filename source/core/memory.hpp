#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

//#include "memoryvalue.h"
typedef std::vector<bool> MemoryValue;

enum class endian{little,big};

class Memory
{
public:
    Memory(int,int,endian);
    Memory(int,endian);

    MemoryValue get(const int, const int=1)const;
    void set(const int,const MemoryValue&);
};

#endif // MEMORY_H
