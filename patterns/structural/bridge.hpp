#ifndef PATTERNS_STRUCTURAL_BRIDGE_HPP
#define PATTERNS_STRUCTURAL_BRIDGE_HPP
 
#include <iostream>
#include <memory>
#include <common/utils.hpp>

namespace structural
{
  class TimingAnalysisImplementation
  {
    std::vector<common::TimingPoint> m_topologicalSortedTPs;
    std::vector<double> m_lateSlacks;
    std::vector<double> m_earlySlacks;

    public:
      TimingAnalysisImplementation(const std::vector<common::TimingPoint> & timingPoints)
      {
        topologicalSort(timingPoints);
      }
      virtual ~TimingAnalysisImplementation(){}

      void topologicalSort(const std::vector<common::TimingPoint> & timingPoints)
      {
        //TopologicalSort code goes here
        m_topologicalSortedTPs = timingPoints;
      }

      void runLateScenario()
      {
        std::cout << "Running Full STA for Late Scenario " << std::endl;
        for(auto & tp : m_topologicalSortedTPs)
        {
          propagateLateScenario(tp);
        }
      }

      void runLateEarlyScenario()
      {
        std::cout << "Running Full STA for Late/Early Scenario " << std::endl;
        for(auto & tp : m_topologicalSortedTPs)
        {
          propagateLateScenario(tp);
          propagateEarlyScenario(tp);
        }
      }

      double lateSlack(const common::TimingPoint & timingPoint) { return m_lateSlacks.at(timingPoint.pin_id); }
      
      double earlySlack(const common::TimingPoint & timingPoint) { return m_earlySlacks.at(timingPoint.pin_id); }

      virtual void propagateLateScenario(const common::TimingPoint & timingPoint) = 0;
      virtual void propagateEarlyScenario(const common::TimingPoint & timingPoint) = 0;
  };

  // Simple lumped capacitance and Elmore delay model
  class LumpedCapElmoreDelayTimingAnalysisImplementation : public TimingAnalysisImplementation
  {
    public:
      LumpedCapElmoreDelayTimingAnalysisImplementation(const std::vector<common::TimingPoint> & timingPoints) :
      TimingAnalysisImplementation(timingPoints)
      {
        std::cout << "Constructing LumpedCapElmoreDelayTimingAnalysisImplementation" << std::endl;
      }

      ~LumpedCapElmoreDelayTimingAnalysisImplementation()
      {
        std::cout << "Destructing LumpedCapElmoreDelayTimingAnalysisImplementation" << std::endl;
      }

      void propagateLateScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating LumpedCapElmoreDelay for late scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }

      void propagateEarlyScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating LumpedCapElmoreDelay for early scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }
  };

  // Effective capacitance and Elmore delay
  class EffectiveCapElmoreDelayTimingAnalysisImplementation : public TimingAnalysisImplementation
  {
    public:
      EffectiveCapElmoreDelayTimingAnalysisImplementation(const std::vector<common::TimingPoint> & timingPoints) : 
      TimingAnalysisImplementation(timingPoints)
      {
        std::cout << "Constructing EffectiveCapElmoreDelayTimingAnalysisImplementation" << std::endl;
      }

      ~EffectiveCapElmoreDelayTimingAnalysisImplementation()
      {
        std::cout << "Destructing EffectiveCapElmoreDelayTimingAnalysisImplementation" << std::endl;
      }

      void propagateLateScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating EffectiveCapElmoreDelay for late scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }

      void propagateEarlyScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating EffectiveCapElmoreDelay for early scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }
  };

  // Lumped capacitance and delay with 2 moments (D2M)
  class LumpedCapD2MTimingAnalysisImplementation : public TimingAnalysisImplementation
  {
    public:
      LumpedCapD2MTimingAnalysisImplementation(const std::vector<common::TimingPoint> & timingPoints) :
      TimingAnalysisImplementation(timingPoints)
      {
        std::cout << "Constructing LumpedCapD2MTimingAnalysisImplementation" << std::endl;
      }

      ~LumpedCapD2MTimingAnalysisImplementation()
      {
        std::cout << "Destructing LumpedCapD2MTimingAnalysisImplementation" << std::endl;
      }

      void propagateLateScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating LumpedCapD2M late scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }

      void propagateEarlyScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating LumpedCapD2M for early scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }
  };

  // Effective capacitance and delay with 2 moments (D2M)
  class EffectiveCapD2MTimingAnalysisImplementation : public TimingAnalysisImplementation
  {
    public:
      EffectiveCapD2MTimingAnalysisImplementation(const std::vector<common::TimingPoint> & timingPoints) :
      TimingAnalysisImplementation(timingPoints)
      {
        std::cout << "Constructing EffectiveCapD2MTimingAnalysisImplementation" << std::endl;
      }

      ~EffectiveCapD2MTimingAnalysisImplementation()
      {
        std::cout << "Destructing EffectiveCapD2MTimingAnalysisImplementation" << std::endl;
      }

      void propagateLateScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating EffectiveCapD2M late scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }

      void propagateEarlyScenario(const common::TimingPoint & timingPoint) override
      {
        std::cout << "..Propagating EffectiveCapD2M for early scenario for tp: " << timingPoint.pin_id <<  std::endl;
      }
  };

  // Bridge
  class TimingAnalysisInterface
  {
    protected:
      std::unique_ptr<TimingAnalysisImplementation> m_implementation;
    public:
      TimingAnalysisInterface(std::unique_ptr<TimingAnalysisImplementation> && implementation) : m_implementation(std::move(implementation))
      {
      }
      virtual ~TimingAnalysisInterface(){}

      // Full STA
      virtual void run()
      {
        m_implementation->runLateScenario();
      }
        
      double lateSlack(const common::TimingPoint & timingPoint)
      { 
        return m_implementation->lateSlack(timingPoint);
      }
   };

  class LateEarlyTimingAnalysisInterface : public TimingAnalysisInterface
  {
    public:
      LateEarlyTimingAnalysisInterface(std::unique_ptr<TimingAnalysisImplementation> && implementation) : 
      TimingAnalysisInterface(std::move(implementation))
      {
      }


      virtual void run()
      {
        m_implementation->runLateEarlyScenario();
      }

      double earlySlack(const common::TimingPoint & timingPoint)
      {
        return m_implementation->earlySlack(timingPoint);
      }
  };

} //end of namespace structural


#endif //PATTERNS_STRUCTURAL_BRIDGE_HPP
