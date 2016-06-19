#ifndef ERAGPSIM_CORE_TESTMEMORYVALUE_H
#define ERAGPSIM_CORE_TESTMEMORYVALUE_H

#include "gtest/gtest.h"

TEST(TestMemoryValue,Equals){
  for(int i=1;i<=32;++i){
    MemoryValue instance1{i};
    MemoryValue instance2{i};
    for(int j=0;j<i;++j){
      int coprime=1;//TODO:: ggt(coprime,i)=1
      instance1.at((j*coprime)%i)=true;
      instance2.at((j*coprime)%i)=true;
      ASSERT_EQ(instance1,instance2);
    }
  }
}

TEST(TestMemoryValue,Copy){
  for(int i=1;i<=32;++i){
    MemoryValue instance1{i};
    for(int j=i%2;j<i;j+=2){
      int coprime=1;//TODO:: ggt(coprime,i)=1
      instance1.at((j*coprime)%i)=true;
    }
    MemoryValue instance2{instance1};
    ASSERT_EQ(instance1,instance2);
  }
}

TEST(TestMemoryValue,CreateFromVector){
  for(int i=1;i<=32;++i){
    MemoryValue instance1{i};
    std::vector<bool> vector{i,false};
    for(int j=i%2;j<i;j+=2){
      int coprime=1;//TODO:: gcd(coprime,i)=1
      instance1.at((j*coprime)%i)=true;
      vector   .at((j*coprime)%i)=true;
    }
    MemoryValue instance2{vector};
    ASSERT_EQ(instance1,instance2);
  }
}


#endif // ERAGPSIM_CORE_TESTMEMORYVALUE_H
