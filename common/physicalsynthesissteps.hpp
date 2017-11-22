#ifndef COMMON_PHYSICAL_SYNTHESIS_STEPS_HPP
#define COMMON_PHYSICAL_SYNTHESIS_STEPS_HPP

#include <iostream>

#include "optimization.hpp"

namespace common
{

class PhysicalSynthesisBase
{
  public:
    virtual void Run() = 0;
};

class GlobalPlacement : public PhysicalSynthesisBase
{
  public:
    GlobalPlacement()
    {
      std::cout << "Constructing GlobalPlacement" << std::endl;
    }

    ~GlobalPlacement()
    {
      std::cout << "Destructing GlobalPlacement" << std::endl;
    }

    void Run() override 
    {
      std::cout << "Running GlobalPlacement" << std::endl;
    }
};

class DetailedPlacement : public PhysicalSynthesisBase
{
  public:
    DetailedPlacement()
    {
      std::cout << "Constructing DetailedPlacement" << std::endl;
    }

    ~DetailedPlacement()
    {
      std::cout << "Destructing DetailedPlacement" << std::endl;
    }

    void Run() override 
    {
      std::cout << "Running DetailedPlacement" << std::endl;
    }
};

class ClockNetworkSynthesis : public PhysicalSynthesisBase
{
  public:
    ClockNetworkSynthesis()
    {
      std::cout << "Constructing ClockNetworkSynthesis" << std::endl;
    }

    ~ClockNetworkSynthesis()
    {
      std::cout << "Destructing ClockNetworkSynthesis" << std::endl;
    }

    void Run() override 
    {
      std::cout << "Running ClockNetworkSynthesis" << std::endl;
    }
};

class GlobalRouting : public PhysicalSynthesisBase
{
  public:
    GlobalRouting()
    {
      std::cout << "Constructing GlobalRouting" << std::endl;
    }

    ~GlobalRouting()
    {
      std::cout << "Destructing GlobalRouting" << std::endl;
    }

    void Run() override 
    {
      std::cout << "Running GlobalRouting" << std::endl;
    }
};

class DetailedRouting : public PhysicalSynthesisBase
{
  public:
    DetailedRouting()
    {
      std::cout << "Constructing DetailedRouting" << std::endl;
    }

    ~DetailedRouting()
    {
      std::cout << "Destructing DetailedRouting" << std::endl;
    }

    void Run() override 
    {
      std::cout << "Running DetailedRouting" << std::endl;
    }
};

class MajorPhysicalSynthesisSteps
{
  public:
    GlobalPlacement globalPlacement;
    DetailedPlacement detailedPlacement;
    ClockNetworkSynthesis clockNetworkSynthesis;
    GlobalRouting globalRouting;
    DetailedRouting detailedRouting;

    TimingOptimization timingOptimization;
    PowerOptimization powerOptimization;
    AreaOptimization areaOptimization;
};

} //end of namespace majorsteps

#endif //COMMON_PHYSICAL_SYNTHESIS_STEPS_HPP
