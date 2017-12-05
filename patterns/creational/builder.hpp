#ifndef PATTERNS_CREATIONAL_BUILDER_HPP
#define PATTERNS_CREATIONAL_BUILDER_HPP

#include <exception>
#include <memory>

#include <common/optimization.hpp>
#include <common/physicalsynthesissteps.hpp>

namespace creational
{
  //product
  class PhysicalSynthesisFlow
  {
    private:
      using StepFunction = std::function<void()>;
      using StepsQueue = std::vector<StepFunction>;
      StepsQueue m_steps;

    public:
      PhysicalSynthesisFlow()
      {
        std::cout << "Constructing PhysicalSynthesisFlow" << std::endl;
      }

      ~PhysicalSynthesisFlow()
      {
        std::cout << "Destructing PhysicalSynthesisFlow" << std::endl;
      }

      template<typename FUNCTION>
      void addStep(FUNCTION&& func)
      {
        m_steps.emplace_back(func);
      }

      void run()
      {
        for (auto step : m_steps)
        {
          step();
        }
      }
  };

  //abstract builder
  class FlowBuilder
  {
    protected:
      common::MajorPhysicalSynthesisSteps & m_steps;
      std::unique_ptr<PhysicalSynthesisFlow> m_flow; 

    public:
      FlowBuilder() : m_steps(common::MajorPhysicalSynthesisSteps::getInstance())
      {
      }
      virtual ~FlowBuilder() {} 
      virtual void buildPlacementFlow() = 0;
      virtual void buildCtsFlow() = 0;
      virtual void buildRoutingFlow() = 0;
      
      void startFlow()
      {
        m_flow = std::make_unique<PhysicalSynthesisFlow>();
      }

      std::unique_ptr<PhysicalSynthesisFlow> getFlow()
      {
        return std::move(m_flow);
      }
  };

  class LowEffortFlowBuilder : public FlowBuilder
  {
    public:
      void buildPlacementFlow() override
      {
        //when pointing to a member function, std::bind expects an object as second argument
        m_flow->addStep(std::bind(&common::GlobalPlacement::run, &m_steps.globalPlacement)); 
        m_flow->addStep(std::bind(&common::DetailedPlacement::run, &m_steps.detailedPlacement)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization)); 
      }

      void buildCtsFlow() override
      {
        m_flow->addStep(std::bind(&common::ClockNetworkSynthesis::run, &m_steps.clockNetworkSynthesis)); 
      }
      
      void buildRoutingFlow() override
      {
        m_flow->addStep(std::bind(&common::GlobalRouting::run, &m_steps.globalRouting)); 
        m_flow->addStep(std::bind(&common::DetailedRouting::run, &m_steps.detailedRouting)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
      }
  };

  class MediumEffortFlowBuilder : public FlowBuilder
  {
    public:
      void buildPlacementFlow() override
      {
        //when pointing to a member function, std::bind expects an object as second argument
        m_flow->addStep(std::bind(&common::GlobalPlacement::run, &m_steps.globalPlacement)); 
        m_flow->addStep(std::bind(&common::DetailedPlacement::run, &m_steps.detailedPlacement)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
        m_flow->addStep(std::bind(&common::PowerOptimization::optimize, &m_steps.powerOptimization)); 
      }

      void buildCtsFlow() override
      {
        m_flow->addStep(std::bind(&common::ClockNetworkSynthesis::run, &m_steps.clockNetworkSynthesis)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
      }
      
      void buildRoutingFlow() override
      {
        m_flow->addStep(std::bind(&common::GlobalRouting::run, &m_steps.globalRouting));
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
        m_flow->addStep(std::bind(&common::DetailedRouting::run, &m_steps.detailedRouting)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
      }
  };

  class HighEffortFlowBuilder : public FlowBuilder
  {
    public:
      void buildPlacementFlow() override
      {
        //when pointing to a member function, std::bind expects an object as second argument
        m_flow->addStep(std::bind(&common::GlobalPlacement::run, &m_steps.globalPlacement)); 
        m_flow->addStep(std::bind(&common::DetailedPlacement::run, &m_steps.detailedPlacement)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
        m_flow->addStep(std::bind(&common::DetailedPlacement::run, &m_steps.detailedPlacement)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
        m_flow->addStep(std::bind(&common::DetailedPlacement::run, &m_steps.detailedPlacement)); 
        m_flow->addStep(std::bind(&common::PowerOptimization::optimize, &m_steps.powerOptimization)); 
      }

      void buildCtsFlow() override
      {
        m_flow->addStep(std::bind(&common::ClockNetworkSynthesis::run, &m_steps.clockNetworkSynthesis)); 
        m_flow->addStep(std::bind(&common::DetailedPlacement::run, &m_steps.detailedPlacement)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
        m_flow->addStep(std::bind(&common::PowerOptimization::optimize, &m_steps.powerOptimization)); 
      }
      
      void buildRoutingFlow() override
      {
        m_flow->addStep(std::bind(&common::GlobalRouting::run, &m_steps.globalRouting)); 
        m_flow->addStep(std::bind(&common::DetailedPlacement::run, &m_steps.detailedPlacement)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
        m_flow->addStep(std::bind(&common::DetailedRouting::run, &m_steps.detailedRouting)); 
        m_flow->addStep(std::bind(&common::TimingOptimization::optimize, &m_steps.timingOptimization));
        m_flow->addStep(std::bind(&common::PowerOptimization::optimize, &m_steps.powerOptimization)); 
      }
  };

  class SynthesisFlowDirector
  {
    std::unique_ptr<FlowBuilder> m_builder;
    public:
      SynthesisFlowDirector(std::unique_ptr<FlowBuilder> && builder) : m_builder(std::move(builder))
      {
      }

      void setBuilder(std::unique_ptr<FlowBuilder> && builder)
      {
        m_builder = std::move(builder);
      }

      std::unique_ptr<PhysicalSynthesisFlow> createFlow()
      {
        m_builder->startFlow();
        m_builder->buildPlacementFlow();
        m_builder->buildCtsFlow();
        m_builder->buildRoutingFlow();
        return m_builder->getFlow();
      }
  };

} //end of namespace creational


#endif //PATTERNS_CREATIONAL_BUILDER_HPP
