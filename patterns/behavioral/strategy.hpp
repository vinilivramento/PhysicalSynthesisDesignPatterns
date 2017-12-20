#ifndef PATTERNS_BEHAVIORAL_STRATEGY_HPP
#define PATTERNS_BEHAVIORAL_STRATEGY_HPP
 
#include <iostream>
#include <memory>
#include <common/utils.hpp>

namespace behavioral
{
  class IncrementalPlacementStrategy
  {
    public:
      virtual ~IncrementalPlacementStrategy() {}
      virtual void place_cell(common::Cell & cell) = 0;
  };

  class GreedyIncrementalPlacement : public IncrementalPlacementStrategy
  {
    public:
      void place_cell(common::Cell & cell) override
      {
        std::cout << "GreedyIncrementalPlacement::place_cell() - " << cell.id << std::endl;
      }
  };

  class DynamicProgrammingIncrementalPlacement : public IncrementalPlacementStrategy
  {
    public:
      void place_cell(common::Cell & cell) override
      {
        std::cout << "DynamicProgrammingIncrementalPlacement::place_cell() - " << cell.id << std::endl;
      }
  };

  class IncrementalLegalizationStrategy
  {
    public:
      virtual ~IncrementalLegalizationStrategy() {}
      virtual void legalize_cell(common::Cell & cell) = 0;
  };

  class WindowBasedIncrementalLegalization : public IncrementalLegalizationStrategy
  {
    public:
      void legalize_cell(common::Cell & cell) override
      {
        std::cout << "WindowBasedIncrementalLegalization::legalize_cell() - " << cell.id << std::endl;
      }
  };

  class AbacusIncrementalLegalization : public IncrementalLegalizationStrategy
  {
    public:
      void legalize_cell(common::Cell & cell) override
      {
        std::cout << "AbacusIncrementalLegalization::legalize_cell() - " << cell.id << std::endl;
      }
  };

  //client
  class IncrementalPlacement
  {
    std::unique_ptr<IncrementalPlacementStrategy> m_incrementalPlacementStrategy;
    std::unique_ptr<IncrementalLegalizationStrategy> m_incrementalLegalizationStrategy;
    
    public:
      IncrementalPlacement(std::unique_ptr<IncrementalPlacementStrategy> && incremental_placement_strategy,
                           std::unique_ptr<IncrementalLegalizationStrategy> && incremental_legalization_strategy) :
        m_incrementalPlacementStrategy( std::move(incremental_placement_strategy) ), 
        m_incrementalLegalizationStrategy( std::move(incremental_legalization_strategy) ) 
        {
        }

        void run(std::vector<common::Cell> & cells)
        {
          for(auto & cell : cells)
          {
            m_incrementalPlacementStrategy->place_cell(cell);
            m_incrementalLegalizationStrategy->legalize_cell(cell);
          }
        }
  };

} //end of namespace behavioral

#endif //PATTERNS_BEHAVIORAL_STRATEGY
