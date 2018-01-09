#ifndef PATTERNS_STRUCTURAL_FACADE_HPP
#define PATTERNS_STRUCTURAL_FACADE_HPP
 
#include <iostream>
#include <memory>
#include <common/utils.hpp>
#include <patterns/creational/builder.hpp>

namespace structural
{

class PhysicalSynthesisFacade
{
  public:
    void place()
    {
      creational::LowEffortFlowBuilder flowBuilder;
      flowBuilder.startFlow();
      flowBuilder.buildPlacementFlow();
      flowBuilder.getFlow()->run();
    }

    void cts()
    {
      creational::LowEffortFlowBuilder flowBuilder;
      flowBuilder.startFlow();
      flowBuilder.buildCtsFlow();
      flowBuilder.getFlow()->run();
    }
    
    void route()
    {
      creational::LowEffortFlowBuilder flowBuilder;
      flowBuilder.startFlow();
      flowBuilder.buildRoutingFlow();
      flowBuilder.getFlow()->run();
    }
};

} //end of namespace structural


#endif //PATTERNS_STRUCTURAL_FACADE_HPP
