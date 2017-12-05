#ifndef COMMON_PHYSICAL_SYNTHESIS_STEPS_HPP
#define COMMON_PHYSICAL_SYNTHESIS_STEPS_HPP

#include <iostream>

#include "optimization.hpp"

namespace common
{

class PhysicalSynthesisStep
{
  public:
    virtual void run() = 0;
};

class GlobalPlacement : public PhysicalSynthesisStep
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

    void run() override 
    {
      std::cout << "Running GlobalPlacement" << std::endl;
    }
};

class DetailedPlacement : public PhysicalSynthesisStep
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

    void run() override 
    {
      std::cout << "Running DetailedPlacement" << std::endl;
    }
};

class ClockNetworkSynthesis : public PhysicalSynthesisStep
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

    void run() override 
    {
      std::cout << "Running ClockNetworkSynthesis" << std::endl;
    }
};

class GlobalRouting : public PhysicalSynthesisStep
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

    void run() override 
    {
      std::cout << "Running GlobalRouting" << std::endl;
    }
};

class DetailedRouting : public PhysicalSynthesisStep
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

    void run() override 
    {
      std::cout << "Running DetailedRouting" << std::endl;
    }
};

class MajorPhysicalSynthesisSteps
{
  MajorPhysicalSynthesisSteps()
  {
  }

  public:
    GlobalPlacement globalPlacement;
    DetailedPlacement detailedPlacement;
    ClockNetworkSynthesis clockNetworkSynthesis;
    GlobalRouting globalRouting;
    DetailedRouting detailedRouting;

    TimingOptimization timingOptimization;
    PowerOptimization powerOptimization;
    AreaOptimization areaOptimization;

    static MajorPhysicalSynthesisSteps& getInstance()
    {
      static MajorPhysicalSynthesisSteps instance;
      return instance;
    }
};

} //end of namespace majorsteps

#endif //COMMON_PHYSICAL_SYNTHESIS_STEPS_HPP
