#ifndef COMMON_OPTIMIZATION_HPP
#define COMMON_OPTIMIZATION_HPP

#include <iostream> 

#include "resources.hpp"

namespace common
{

class Optimization
{
  public:
    virtual void optimize() = 0;
};

class TimingOptimization : public Optimization
{
  public:
    TimingOptimization()
    { 
      std::cout << "Constructing TimingOptimization" << std::endl;
    }
  
    void optimize() override
    {
      std::cout << "Running Timing Optimization" << std::endl;
    }
};

class PowerOptimization : public Optimization
{
  public:
    PowerOptimization()
    {
      std::cout << "Constructing PowerOptimization" << std::endl;
    }

    void optimize() override
    {
      std::cout << "Running Power Optimization" << std::endl;
    }
}; 

class AreaOptimization : public Optimization
{
  public:
    AreaOptimization()
    {
      std::cout << "Constructing AreaOptimization" << std::endl;
    }

    void optimize() override
    {
      std::cout << "Running Area Optimization" << std::endl;
    }
};

} //end of namespace common

#endif //COMMON_OPTIMIZATION_HPP
