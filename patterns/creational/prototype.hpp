#ifndef PATTERNS_CREATIONAL_PROTOTYPE_HPP
#define PATTERNS_CREATIONAL_PROTOTYPE_HPP

#include <memory>
#include <random>

#include <common/utils.hpp>

namespace creational
{
  template<typename T>
  class PrototypeSolution
  {
    std::vector<T> m_solution;
    double m_quality;

    public:
      PrototypeSolution(std::vector<T> solution, double quality) : m_solution(solution), m_quality(quality)
      {
      
      }

      virtual ~PrototypeSolution(){}
      virtual std::unique_ptr<PrototypeSolution> clone() const = 0;

      double getQuality() const 
      {
        return m_quality;
      }

      const std::vector<T>& getSolution() const
      {
        return m_solution; 
      }

      void setCellSolution(unsigned index, T value)
      {
        m_solution.at(index) = value;  
      }

      void setQuality(double quality)
      {
        m_quality = quality;
      }

      bool operator>(const PrototypeSolution & other)
      {
        return m_quality > other.getQuality();
      }

      friend std::ostream& operator<< (std::ostream& os, const PrototypeSolution & solution)
      {
        os << "Quality: " << solution.m_quality << " -> solution: {";
        for (auto & val : solution.m_solution)
          os << val << ", ";
        os << "}";

        return os;
      }
  };

  class PlacementSolution : public PrototypeSolution<common::Location>
  {
    public:
      PlacementSolution(std::vector<common::Location> solution, double quality) : PrototypeSolution(solution, quality)
      {
        std::cout << "Constructing PlacementSolution" << std::endl;
      }

      std::unique_ptr<PrototypeSolution> clone() const override
      {
        std::cout << "Cloning PlacementSolution" << std::endl;
        return std::make_unique<PlacementSolution>(*this); 
      }
  };

  class CellSizingSolution : public PrototypeSolution<std::string>
  {
    public:
      CellSizingSolution(std::vector<std::string> solution, double quality) : PrototypeSolution(solution, quality)
      {
        std::cout << "Constructing CellSizingSolution" << std::endl;
      }

      std::unique_ptr<PrototypeSolution> clone() const override
      {
        std::cout << "Cloning CellSizingSolution" << std::endl;
        return std::make_unique<CellSizingSolution>(*this); 
      }
  };

  //client
  class PlacementAndSizingOptimization
  {
    private:
      const unsigned m_numTrials;

      void optimizeCellSizes(const CellSizingSolution & prototype)
      {
        std::cout << "...sizing optimization" << std::endl;
        auto bestSolution = prototype.clone();

        for(unsigned i = 0; i < m_numTrials; ++i)
        {
          //The clonned solution is the initial solution (from other steps) to be optimized
          auto curSolution = prototype.clone();

          //dummy solution generator
          //optimization code goes here...
          {
            std::default_random_engine generator;
            std::uniform_real_distribution<double> realDist(1.0, 40.0);
            std::uniform_int_distribution<int> intDist(1, 8);

            curSolution->setQuality(realDist(generator));
            for(unsigned i = 0; i < curSolution->getSolution().size(); ++i)
              curSolution->setCellSolution(i, std::string("X" + std::to_string(intDist(generator))));
          }

          if(*curSolution > *bestSolution)
            bestSolution = std::move(curSolution);
        }
        std::cout << "Best Sizing Solution...." << std::endl;
        std::cout << *bestSolution << std::endl;
      }

      void optimizeCellLocations(const PlacementSolution & prototype)
      {
        std::cout << "...placement optimization" << std::endl;
        auto bestSolution = prototype.clone();

        for(unsigned i = 0; i < m_numTrials; ++i)
        {
          //The clonned solution is the initial solution (from other steps) to be optimized
          auto curSolution = prototype.clone();

          //dummy solution generator
          //optimization code goes here...
          {
            std::default_random_engine generator;
            std::uniform_real_distribution<double> realDist(1.0, 50.0);
            std::uniform_int_distribution<int> intDist(0, 10);

            curSolution->setQuality(realDist(generator));
            for(unsigned i = 0; i < curSolution->getSolution().size(); ++i)
              curSolution->setCellSolution(i, common::Location(intDist(generator), intDist(generator)));
          }

          if(*curSolution > *bestSolution)
            bestSolution = std::move(curSolution);
        }
        std::cout << "Best Sizing Solution...." << std::endl;
        std::cout << *bestSolution << std::endl;
      }

    public:
      PlacementAndSizingOptimization(unsigned numTrials) : m_numTrials(numTrials)
      {
      }

      void optimize(const CellSizingSolution & sizingSolution, const PlacementSolution & placementSolution)
      {
        optimizeCellSizes(sizingSolution);
        optimizeCellLocations(placementSolution);
      }
  };

} // end of namespace creational

#endif //PATTERNS_CREATIONAL_PROTOTYPE_HPP

