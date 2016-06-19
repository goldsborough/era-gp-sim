#ifndef ERAGPSIM_CORE_TESTMEMORY_INC
#define ERAGPSIM_CORE_TESTMEMORY_INC

#include "gtest/gtest.h"

TEST(TestMemory,InOutSingleCell){
  for(int i=1;i<=32;++i){
    Memory instance{32,i,endian::kLittleEndian};
    MemoryValue instance1{i};
    MemoryValue instance2{i};
    for(int j=0;j<32;++j){
      int coprime{1};//TODO
      instance1.at((j*coprime)%i)=!instance1.at((j*coprime)%i);
      instance.put(j,instance1);
      instance2=instance.get(j);
      ASSERT_EQ(instance1,instance2);
    }
  }
}

TEST(TestMemory,InOutMultipleCell){
  for(int i=1;i<32;++i){
    for(int j=1;j<=32;++j){
      Memory instance{32+i,j,endian::kLittleEndian};
      MemoryValue instance1{j*i};
      MemoryValue instance2{j*i};
      for(int l=0;l<32;++l){
        int coprime{1};//TODO
        instance1.at((l*coprime)%(j*i))=!instance1.at((l*coprime)%(j*i));
        instance.put(l,instance1);
        instance2=instance.get(l,i);
        ASSERT_EQ(instance1,instance2);
      }
    }
  }
}


#endif // ERAGPSIM_CORE_TESTMEMORY_INC
