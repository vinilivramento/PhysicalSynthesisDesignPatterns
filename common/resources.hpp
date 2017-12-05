#ifndef PATTERNS_RESOURCES_HPP
#define PATTERNS_RESOURCES_HPP

#include <boost/core/noncopyable.hpp>
#include <iostream>

namespace common
{
  class Analyzer : public boost::noncopyable
  {
    public:
      virtual ~Analyzer(){}
      virtual void analyze() = 0;
  };

  class TimingAnalyzer : public Analyzer 
  {
    public:
      TimingAnalyzer()
      {
        std::cout << "Constructing TimingAnalyzer!" << std::endl;
      }
      ~TimingAnalyzer()
      {
        std::cout << "Destructing TimingAnalyzer!" << std::endl;
      }
      
      void analyze() override
      {
        std::cout << "Running TimingAnalyzer" << std::endl;
      }
  };

  class PowerAnalyzer : public Analyzer 
  {
    PowerAnalyzer()
    {
      std::cout << "Constructing PowerAnalyzer!" << std::endl;
    }

    ~PowerAnalyzer()
    {
      std::cout << "Destructing PowerAnalyzer!" << std::endl;
    }

    void analyze() override
    {
      std::cout << "Running PowerAnalyzer" << std::endl;
    }
  };

  class AreaAnalyzer : public Analyzer 
  {
    AreaAnalyzer()
    {
      std::cout << "Constructing AreaAnalyzer!" << std::endl;
    }

    ~AreaAnalyzer()
    {
      std::cout << "Destructing AreaAnalyzer!" << std::endl;
    }

    void analyze() override
    {
      std::cout << "Running AreaAnalyzer" << std::endl;
    }
  };

} // enf of namespace common

#endif // PATTERNS_RESOURCES_HPP
