#ifndef PATTERNS_RESOURCES_HPP
#define PATTERNS_RESOURCES_HPP

#include <boost/core/noncopyable.hpp>
#include <iostream>

namespace common
{
  class TimingAnalyzer : public boost::noncopyable
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
      
      void Analyze()
      {
        std::cout << "Running TimingAnalyzer" << std::endl;
      }
  };

  class PowerAnalyzer : public boost::noncopyable
  {
    PowerAnalyzer()
    {
      std::cout << "Constructing PowerAnalyzer!" << std::endl;
    }

    ~PowerAnalyzer()
    {
      std::cout << "Destructing PowerAnalyzer!" << std::endl;
    }

    void Analyze()
    {
      std::cout << "Running PowerAnalyzer" << std::endl;
    }
  };

  class AreaAnalyzer : public boost::noncopyable
  {
    AreaAnalyzer()
    {
      std::cout << "Constructing AreaAnalyzer!" << std::endl;
    }

    ~AreaAnalyzer()
    {
      std::cout << "Destructing AreaAnalyzer!" << std::endl;
    }

    void Analyze()
    {
      std::cout << "Running AreaAnalyzer" << std::endl;
    }
  };

} // enf of namespace common

#endif // PATTERNS_RESOURCES_HPP
