#ifndef ERAGPSIM_CORE_MEMORYVALUE_H
#define ERAGPSIM_CORE_MEMORYVALUE_H

#include <vector>

class MemoryValue
{
public:
    //Creates a MemoryValue of width 'width' (default=8)
    MemoryValue(int=8);
    //Creates a MemoryValue with a copy of the std::vector<bool> 'data'
    MemoryValue(const std::vector<bool>);
    //copy constructor
    MemoryValue(const MemoryValue&)=default;
    //copy operator
    MemoryValue& operator=(const MemoryValue&)=default;
    //move constructor
    MemoryValue(MemoryValue&&)=default;
    //move operator
    MemoryValue& operator =(MemoryValue&&)=default;
    //destructor
    ~MemoryValue()=default;

    //Returns a reference to the element at specified location 'index', with bounds checking.
    //If 'index' is not within the range of the container, an exception of type std::out_of_range is thrown.
    std::vector<bool>::reference at(const int);
    //Returns a reference to the element at specified location 'index', with bounds checking.
    //If 'index' is not within the range of the container, an exception of type std::out_of_range is thrown.
    std::vector<bool>::const_reference at(const int)const;
    //Returns a reference to the element at specified location 'index'. No bounds checking is performed.
    std::vector<bool>::reference operator[](const int);
    //Returns a reference to the element at specified location 'index'. No bounds checking is performed.
    std::vector<bool>::const_reference operator[](const int)const;
    //Toggles each bool in the vector (replaces with its opposite value).
    void flip();
private:
    std::vector<bool> data;
};

#endif // ERAGPSIM_CORE_MEMORYVALUE_H
