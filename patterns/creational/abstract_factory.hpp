#ifndef PATTERNS_CREATIONAL_ABSTRACT_FACTORY_HPP
#define PATTERNS_CREATIONAL_ABSTRACT_FACTORY_HPP

#include <iostream>

namespace creational
{

class DetailedPlacement
{
  public:
    virtual ~DetailedPlacement() {}
    virtual void runDetailedPlacement() = 0;
    virtual void getWirelengthAndCongestion() = 0;
};

class LocalDetailedPlacement: public DetailedPlacement
{
  public:
    void runDetailedPlacement() override
    {
      std::cout << "Running Local Detailed Placement" << std::endl;
    }
    
    void getWirelengthAndCongestion() override
    {
      std::cout << "Computing Wirelength and Congestion Estimate for Local Detailed Placement" << std::endl; 
    }
};

class GlobalDetailedPlacement: public DetailedPlacement
{
  public:
    void runDetailedPlacement() override
    {
      std::cout << "Running Global Detailed Placement" << std::endl;
    }
    
    void getWirelengthAndCongestion() override
    {
      std::cout << "Computing Wirelength and Congestion Estimate for Global Detailed Placement" << std::endl; 
    }
};

class CellSpreading
{
  public:
    virtual ~CellSpreading() {}
    virtual void runCellSpreading() = 0;
    virtual void getWirelengthAndCongestion() = 0;
};

class LocalCellSpreading : public CellSpreading
{
  public:
    void runCellSpreading() override
    {
      std::cout << "Running Local Cell Spreading" << std::endl;
    }

    void getWirelengthAndCongestion() override
    {
      std::cout << "Computing Wirelength and Congestion Estimate for Local Cell Spreading" << std::endl;
    }
};

class GlobalCellSpreading : public CellSpreading
{
  public:
    void runCellSpreading() override
    {
      std::cout << "Running Global Cell Spreading" << std::endl;
    }

    void getWirelengthAndCongestion() override
    {
      std::cout << "Computing Wirelength and Congestion Estimate for Global Cell Spreading" << std::endl;
    }
};

class CellOptimizationFactory
{
  public:
    virtual ~CellOptimizationFactory() {}
    virtual std::unique_ptr<DetailedPlacement> createDetailedPlacement() = 0;
    virtual std::unique_ptr<CellSpreading> createCellSpreading() = 0;
};

class GlobalCellOptimizationFactory: public CellOptimizationFactory
{
  public:
      std::unique_ptr<DetailedPlacement> createDetailedPlacement() override
      {
        return std::make_unique<GlobalDetailedPlacement>();
      }

      std::unique_ptr<CellSpreading> createCellSpreading() override
      {
        return std::make_unique<GlobalCellSpreading>();
      }
};

class LocalCellOptimizationFactory: public CellOptimizationFactory
{
  public:
      std::unique_ptr<DetailedPlacement> createDetailedPlacement() override
      {
        return std::make_unique<LocalDetailedPlacement>();
      }

      std::unique_ptr<CellSpreading> createCellSpreading() override
      {
        return std::make_unique<LocalCellSpreading>();
      }
};

class DetailedPlacementAndSpreadingEngine 
{
  std::unique_ptr<CellOptimizationFactory> m_factory;

  public:
    DetailedPlacementAndSpreadingEngine(std::unique_ptr<CellOptimizationFactory>&& factory) : m_factory(std::move(factory))
    {
    }

    void minimizeCongestionAndWirelength()
    {
      auto detailedPlacement = m_factory->createDetailedPlacement();
      auto cellSpreading = m_factory->createCellSpreading();

      detailedPlacement->runDetailedPlacement();
      detailedPlacement->getWirelengthAndCongestion();

      cellSpreading->runCellSpreading();
      cellSpreading->getWirelengthAndCongestion();
    }
};

} // end of namespace creational

#endif //PATTERNS_CREATIONAL_ABSTRACT_FACTORY_HPP

