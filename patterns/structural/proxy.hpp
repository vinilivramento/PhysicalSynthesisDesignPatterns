#ifndef PATTERNS_STRUCTURAL_PROXY_HPP
#define PATTERNS_STRUCTURAL_PROXY_HPP
 
#include <iostream>
#include <memory>
#include <common/utils.hpp>

namespace structural
{

//remote proxy - represent an object located remotely


//virtual proxy - Lazy instantiation of heavy objects and keep them constructed and ready to be used when needed

//smart proxy - 

//Protection Proxy - Restrict the access to some resources
//Restrict some flow from the user based on its license. For instance, a cheap license may only have access to low-effor flow and no DFT
//Some other license might have access to more complete features.

class RoutingOptimization
{
  public:
    virtual ~RoutingOptimization() {}
    virtual void lowEffortRoutingOptimization() = 0;
    virtual void mediumEffortRoutingOptimization() = 0;
    virtual void highEffortRoutingOptimization() = 0;
};

class RoutingOptimizationImpl : public RoutingOptimization
{
  public:
    void lowEffortRoutingOptimization() override
    {
      std::cout << "Running Low Effort Routing Optimization" << std::endl;
    }
    
    void mediumEffortRoutingOptimization() override
    {
      std::cout << "Running Medium Effort Routing Optimization" << std::endl;
    }

    void highEffortRoutingOptimization() override
    {
      std::cout << "Running High Effort Routing Optimization" << std::endl;
    }
};

enum class LicenseType {UNIVERSITY_LICENSE, BASIC_LICENSE, FULL_LICENSE};

//class of protection proxy
class RoutingOptimizationProxy : public RoutingOptimization
{
  std::unique_ptr<RoutingOptimization> m_routingOptimization;
  LicenseType m_curLicense;

  public:
    RoutingOptimizationProxy(LicenseType curLicense) : m_routingOptimization(std::make_unique<RoutingOptimizationImpl>()), m_curLicense(curLicense)
    {
    }

    void lowEffortRoutingOptimization() override
    {
      std::cout << "License accepted" << std::endl;
      m_routingOptimization->lowEffortRoutingOptimization();
    }
    
    void mediumEffortRoutingOptimization() override
    {
      if(m_curLicense == LicenseType::BASIC_LICENSE || m_curLicense == LicenseType::FULL_LICENSE)
      {
        std::cout << "License accepted" << std::endl;
        m_routingOptimization->mediumEffortRoutingOptimization();
      }
      else
      {
        std::cerr << "Error: Your license does not support medium effort optimization!" << std::endl;
      }
    }

    void highEffortRoutingOptimization() override
    {
      if(m_curLicense == LicenseType::FULL_LICENSE)
      {
        std::cout << "License accepted" << std::endl;
        m_routingOptimization->highEffortRoutingOptimization();
      }
      else
      {
        std::cerr << "Error: Your license does not support high  effort optimization!" << std::endl;
      }
    }
};

} //end of namespace structural


#endif //PATTERNS_STRUCTURAL_PROXY_HPP
