#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <common/optimization.hpp>
#include <common/physicalsynthesissteps.hpp>

#include <patterns/behavioral/command.hpp>
#include <patterns/behavioral/strategy.hpp>

#include <patterns/creational/abstract_factory.hpp>
#include <patterns/creational/builder.hpp>
#include <patterns/creational/factory_method.hpp>
#include <patterns/creational/prototype.hpp>
#include <patterns/creational/singleton.hpp>

#include <patterns/structural/adapter.hpp>
#include <patterns/structural/bridge.hpp>
#include <patterns/structural/decorator.hpp>

using namespace common;
using namespace behavioral;
using namespace creational;
using namespace structural;

//---------------------- Creational TestCases -----------------------------//

TEST_CASE("Abstract factory", "[creational][abstract_factory]") 
{
  std::cout << "-------------Abstract Factory---------------" << std::endl;

  std::cout << "---Local Optimization" << std::endl;
  DetailedPlacementAndSpreadingEngine localOptimizationEngine( std::make_unique<LocalCellOptimizationFactory>() );
  localOptimizationEngine.minimizeCongestionAndWirelength();

  std::cout << "---Global Optimization" << std::endl;
  DetailedPlacementAndSpreadingEngine globalOptimizationEngine( std::make_unique<GlobalCellOptimizationFactory>() );
  globalOptimizationEngine.minimizeCongestionAndWirelength();

  std::cout << std::endl;
}

TEST_CASE("builder", "[creational][builder]") 
{
  std::cout << "-------------Builder---------------" << std::endl;  

  SynthesisFlowDirector director(std::make_unique<LowEffortFlowBuilder>());

  {
    std::cout << "---Low Effort Flow" << std::endl;
    auto flow = director.createFlow();
    flow->run();
  }

  {
    std::cout << "---Medium Effort Flow" << std::endl;
    director.setBuilder(std::make_unique<MediumEffortFlowBuilder>());
    auto flow = director.createFlow();
    flow->run();
  }

  {
    std::cout << "---High Effort Flow" << std::endl;
    director.setBuilder(std::make_unique<HighEffortFlowBuilder>());
    auto flow = director.createFlow();
    flow->run();
  }

  std::cout << std::endl;
}

TEST_CASE("Factory method", "[creational][factory_method]") 
{
  std::cout << "-------------Factory Method---------------" << std::endl;

  OptimizationFactory optFactory;

  REQUIRE_THROWS(optFactory.create("timing-opt"));
  optFactory.registerNewType<TimingOptimization>("timing-opt");
  REQUIRE_NOTHROW(optFactory.create("timing-opt"));

  std::unique_ptr<Optimization> areaOpt = optFactory.create("area-opt");
  std::unique_ptr<Optimization> powerOpt = optFactory.create("power-opt");
  areaOpt->optimize();
  powerOpt->optimize();

  std::cout << std::endl;
}

TEST_CASE("Prototype", "[creational][Prototype]") 
{
  std::cout << "-------------Prototype---------------" << std::endl;

  CellSizingSolution sizingSolution({"X1", "X4", "X2", "X8"}, 5.0);
  PlacementSolution placementSolution({Location(1,2), Location(5,8), Location(4,3), Location(9,9)}, 2.0);

  std::cout << "Initial Sizing Solution...." << std::endl;
  std::cout << sizingSolution << std::endl;

  std::cout << "Initial Placement Solution...." << std::endl;
  std::cout << placementSolution << std::endl;

  std::cout << "---Running PlacementAndSizingOptimization" << std::endl;
  PlacementAndSizingOptimization optimization(5);
  optimization.optimize(sizingSolution, placementSolution);
  
  std::cout << std::endl;
}

TEST_CASE("Singleton", "[creational][singleton]") 
{
  std::cout << "-------------Singleton---------------" << std::endl;

  StandardCellLibrary& cellLibrary = StandardCellLibrary::getInstance();
  StandardCellLibrary& cellLibrary2 = StandardCellLibrary::getInstance();
  REQUIRE(&cellLibrary == &cellLibrary2);

  std::cout << std::endl;
}


//---------------------- Behavioral TestCases -----------------------------//

TEST_CASE("Command", "[behavioral][command]") 
{
  std::cout << "----------Command Test------------" << std::endl;

/*  using namespace behavioral;*/
  //using namespace common;

  //MajorPhysicalSynthesisSteps majorPhysicalSynthesisSteps;

  //std::cout << "   #### Low Effort Flow #### " << std::endl;
    
  //LowEffortPhysicalSynthesisFlow lowEffortFlow(majorPhysicalSynthesisSteps);
  /*lowEffortFlow.Run();*/

  //std::cout << "   #### High Effort Flow #### " << std::endl;

  //TimingOptimization timingOptimization;
  //PowerOptimization powerOptimization;

  //Command highEfforPhysicalSynthesisFlow;
  //highEfforPhysicalSynthesisFlow.AddCommand([&majorPhysicalSynthesisSteps](){ majorPhysicalSynthesisSteps.globalPlacement.Run(); });
  //highEfforPhysicalSynthesisFlow.AddCommand([&majorPhysicalSynthesisSteps](){ majorPhysicalSynthesisSteps.detailedPlacement.Run(); });
  //highEfforPhysicalSynthesisFlow.AddCommand([&majorPhysicalSynthesisSteps](){ majorPhysicalSynthesisSteps.clockNetworkSynthesis.Run(); });
  //highEfforPhysicalSynthesisFlow.AddCommand([&majorPhysicalSynthesisSteps](){ majorPhysicalSynthesisSteps.globalRouting.Run(); });
  //highEfforPhysicalSynthesisFlow.AddCommand([&majorPhysicalSynthesisSteps](){ majorPhysicalSynthesisSteps.detailedRouting.Run(); });



  /*highEfforPhysicalSynthesisFlow.Run();*/
}

TEST_CASE("Strategy", "[behavioral][strategy]") 
{
  std::cout << "----------Strategy Test------------" << std::endl;

  std::vector<Cell> cells{ {0, Location(1,1), Shape(3, 4)},
                           {1, Location(3,3), Shape(2, 2)},
                           {2, Location(9,7), Shape(6, 3)} };

  {
    std::cout << "IncrementalPlacement with GreedyPlacement and WindowBasedLegalization" << std::endl;
    IncrementalPlacement incrementalPlacement(std::make_unique<GreedyIncrementalPlacement>(), std::make_unique<WindowBasedIncrementalLegalization>());
    incrementalPlacement.run(cells);
  }

  {
    std::cout << "IncrementalPlacement with GreedyPlacement and AbacusLegalization" << std::endl;
    IncrementalPlacement incrementalPlacement(std::make_unique<GreedyIncrementalPlacement>(), std::make_unique<AbacusIncrementalLegalization>());
    incrementalPlacement.run(cells);
  }

  {
    std::cout << "IncrementalPlacement with DynamicProgrammingPlacement and AbacusLegalization" << std::endl;
    IncrementalPlacement incrementalPlacement(std::make_unique<DynamicProgrammingIncrementalPlacement>(), std::make_unique<AbacusIncrementalLegalization>());
    incrementalPlacement.run(cells);
  }
}

//---------------------- Structural TestCases -----------------------------//

TEST_CASE("Adapter", "[structural][adapter]") 
{
  std::cout << "-------------Adapter---------------" << std::endl;

  Cell c1{0, Location(1,1), Shape(3, 4)};
  Cell c2{1, Location(3,3), Shape(2, 2)};
  Cell c3{2, Location(9,7), Shape(6, 3)};
  New_Gui gui(3);

  gui.draw_cell(c2);
  gui.draw_cell(c3);
  gui.draw_cell(c1);

  gui.move_cell(c2, Location(4,4));
  gui.move_cell(c1, Location(2,3));
  
  std::cout << std::endl;
}

TEST_CASE("Bridge", "[structural][bridge]") 
{
  std::cout << "-------------Bridge---------------" << std::endl;
  std::vector<TimingPoint> timingPoints{{0}, {1}, {2}, {3}};

  {
    TimingAnalysisInterface lateSta( std::make_unique<LumpedCapElmoreDelayTimingAnalysisImplementation>(timingPoints) );
    lateSta.run();
  }

  {
    TimingAnalysisInterface lateSta( std::make_unique<EffectiveCapElmoreDelayTimingAnalysisImplementation>(timingPoints) );
    lateSta.run();
  }

  {
    LateEarlyTimingAnalysisInterface earlyLateSta( std::make_unique<LumpedCapD2MTimingAnalysisImplementation>(timingPoints) );
    earlyLateSta.run();
  }

  {
    LateEarlyTimingAnalysisInterface earlyLateSta( std::make_unique<EffectiveCapD2MTimingAnalysisImplementation>(timingPoints) );
    earlyLateSta.run();
  }
}

TEST_CASE("Decorator", "[structural][decorator]") 
{
  std::cout << "-------------Decorator---------------" << std::endl;
  
  std::vector<Cell> cells{ {0, Location(1,1), Shape(3, 4)},
                           {1, Location(3,3), Shape(2, 2)},
                           {2, Location(9,7), Shape(6, 3)} };
 
  std::vector<Pin> pins{ {0, 0, Location(0,0), Shape(2, 1)},
                           {1, 1, Location(1,1), Shape(1, 1.5)},
                           {2, 2, Location(2,2), Shape(2, 2)} };

  std::vector<TimingPoint> timing_points{ {0, 0, -2.5},
                                          {1, 1, 0.4},
                                          {2, 2, -3.4} };

  {
    std::cout << "Paint Cells and Pins...." << std::endl;
    auto painter = std::make_unique<PinsPainter>( std::make_unique<CellsPainter>(cells), pins );
    painter->paint();
  }

  {
    std::cout << "Paint Cells, Pins, and Slacks...." << std::endl;
    auto painter = std::make_unique<SlacksPainter>( std::make_unique<PinsPainter>( std::make_unique<CellsPainter>(cells), pins), timing_points );
    painter->paint();
  }

}
