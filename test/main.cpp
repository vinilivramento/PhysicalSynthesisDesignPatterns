#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <common/optimization.hpp>
#include <common/physicalsynthesissteps.hpp>

#include <patterns/behavioral/chain_of_responsability.hpp>
#include <patterns/behavioral/command.hpp>
#include <patterns/behavioral/observer.hpp>
#include <patterns/behavioral/strategy.hpp>

#include <patterns/creational/abstract_factory.hpp>
#include <patterns/creational/builder.hpp>
#include <patterns/creational/factory_method.hpp>
#include <patterns/creational/prototype.hpp>
#include <patterns/creational/singleton.hpp>

#include <patterns/structural/adapter.hpp>
#include <patterns/structural/bridge.hpp>
#include <patterns/structural/composite.hpp>
#include <patterns/structural/decorator.hpp>
#include <patterns/structural/facade.hpp>
#include <patterns/structural/flyweight.hpp>
#include <patterns/structural/proxy.hpp>

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

TEST_CASE("ChainOfResponsability", "[behavioral][chain_of_responsability]") 
{
  std::cout << "----------Chain of Responsability Test------------" << std::endl;
  
  auto ilpRipUpAndReRoute= std::make_shared<ILPRipUpAndReRoute>();
  auto aStarRipUpAndReRoute = std::make_shared<AStarRipUpAndReRoute>(ilpRipUpAndReRoute);
  auto fastGreedyRipUpAndReRoute= std::make_shared<FastGreedyRipUpAndReRoute>(aStarRipUpAndReRoute);

  std::vector<Net> unroutedNets { {"n1", 2}, {"n2", 3}, {"n3", 4}, {"n4", 5}, {"n5", 6} };

  for(auto & net : unroutedNets)
  {
    std::cout << "--Rip-up and ReRoute " << net.name << std::endl;
    fastGreedyRipUpAndReRoute->handleRouteRequest(net);
  }
}

TEST_CASE("Command", "[behavioral][command]") 
{
  std::cout << "----------Command Test------------" << std::endl;

  //client GUI
  CellTransformer transformer;
  auto receiver = std::bind(&CellTransformer::transform, &transformer, std::placeholders::_1);
  CommandInvoker invoker;
  
  std::cout << "Executing Commands" << std::endl;
  auto cmd1 = std::make_shared<CellTransformCommand>(receiver, Transform{1, TransformType::MOVE, Location{1,2}, Location{3,4}});
  invoker.executeCommand(cmd1);

  auto cmd2 = std::make_shared<CellTransformCommand>(receiver, Transform{2, TransformType::MOVE, Location{3,4}, Location{7,8}});
  invoker.executeCommand(cmd2);

  auto cmd3 = std::make_shared<CellTransformCommand>(receiver, Transform{3, TransformType::MOVE, Location{6,6}, Location{9,9}});
  invoker.executeCommand(cmd3);

  std::cout << "Undoing Commands" << std::endl;
  invoker.undo();
  invoker.undo();

  std::cout << "Redoing Commands" << std::endl;
  invoker.redo();

  std::cout << "Executing Commands" << std::endl;
  auto cmd4 = std::make_shared<CellTransformCommand>(receiver, Transform{4, TransformType::RESIZE, "X1", "X8"});
  invoker.executeCommand(cmd4);

  auto cmd5 = std::make_shared<CellTransformCommand>(receiver, Transform{4, TransformType::MOVE, Location{8,6}, Location{10,10}});
  invoker.executeCommand(cmd5);

  auto cmd6 = std::make_shared<CellTransformCommand>(receiver, Transform{5, TransformType::RESIZE, "X8", "X2"});
  invoker.executeCommand(cmd6);

  std::cout << "Undoing Commands" << std::endl;
  invoker.undo();
  invoker.undo();
  invoker.undo();

  std::cout << "Redoing Commands" << std::endl;
  invoker.redo();
  invoker.redo();
  invoker.redo();
}

TEST_CASE("Observer", "[behavioral][observer]") 
{
  std::cout << "----------Observer Test------------" << std::endl;

  std::cout << "Creating standard cells with two properties" << std::endl; 
  CellProperties<std::string> cellNames;  
  CellProperties<double> cellAreas;  

  behavioral::StandardCells stdCells; 
  stdCells.attach(&cellNames);
  stdCells.attach(&cellAreas);

  CellId c1 = stdCells.create();
  CellId c2 = stdCells.create();
  CellId c3 = stdCells.create();

  cellNames[c1] = "c1";
  cellNames[c2] = "c2";
  cellNames[c3] = "c3";

  cellAreas[c1] = 1.0;
  cellAreas[c2] = 2.0;
  cellAreas[c3] = 2.0;

  std::cout << "The properties have size " << cellNames.size() << " and " << cellAreas.size() << std::endl;
  
  std::cout << "Detaching cellAreas properties" << std::endl;
  stdCells.detach(&cellAreas);

  CellId c4 = stdCells.create();
  CellId c5 = stdCells.create();

  std::cout << "The properties have size " << cellNames.size() << " and " << cellAreas.size() << std::endl;
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

TEST_CASE("Composite", "[structural][composite]") 
{
  std::cout << "-------------Composite---------------" << std::endl;

  Cell c1{0, Location(1,1), Shape(3, 4)};
  Cell c2{1, Location(3,3), Shape(2, 2)};
  Cell c3{2, Location(9,7), Shape(6, 3)};

  auto c1Visualization = std::make_shared<CellVisualization>(c1);
  auto c2Visualization = std::make_shared<CellVisualization>(c2);
  auto c3Visualization = std::make_shared<CellVisualization>(c3);

  c1Visualization->setColor("Red");
  c2Visualization->setColor("Blue");
  c3Visualization->setDontTouch(true);

  std::cout << "Handling 3 cells as a composite" << std::endl;

  CellVisualizationGroup cellGroup;
  cellGroup.add(c1Visualization);
  cellGroup.add(c2Visualization);
  cellGroup.add(c3Visualization);
  cellGroup.setColor("Green");
  cellGroup.setDontTouch(false);

  std::cout << "Handling 2 cells as a composite" << std::endl;

  cellGroup.erase(c2Visualization);
  cellGroup.setColor("Black");
  cellGroup.setDontTouch(false);
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

TEST_CASE("Facade", "[structural][facade]") 
{
  std::cout << "-------------Facade---------------" << std::endl;
  PhysicalSynthesisFacade physicalSynthesis;

  std::cout << "Placement flow" << std::endl;
  physicalSynthesis.place();

  std::cout << "Clock-Tree Synthesis flow" << std::endl;
  physicalSynthesis.cts();

  std::cout << "Routing flow" << std::endl;
  physicalSynthesis.route();
}

TEST_CASE("Flyweight", "[structural][flyweight]") 
{
  std::cout << "-------------Flyweight---------------" << std::endl;
  structural::StandardCells stdCells;
  stdCells.reserve(20);
  auto id1  = stdCells.create("c1", "NAND3_X32");
  auto id2  = stdCells.create("c2", "NAND3_X32");
  auto id3  = stdCells.create("c3", "NAND3_X32");
  auto id4  = stdCells.create("c4", "NAND3_X32");
  auto id5  = stdCells.create("c5", "NAND3_X32");
  REQUIRE( (&stdCells.footprint(id1) == &stdCells.footprint(id5) ));
  std::cout << "5 NAND3_X32 instances" << std::endl;

  auto id6  = stdCells.create("c6", "INV_X32");
  auto id7  = stdCells.create("c7", "INV_X32");
  auto id8  = stdCells.create("c8", "INV_X32");
  REQUIRE( (&stdCells.footprint(id6) == &stdCells.footprint(id8) ));
  std::cout << "3 INV_X32 instances" << std::endl;
  
  auto id9  = stdCells.create("c9", "INV_X8");
  auto id10 = stdCells.create("c10","INV_X8");
  auto id11 = stdCells.create("c11","INV_X8");
  auto id12 = stdCells.create("c12","INV_X8");
  auto id13 = stdCells.create("c13","INV_X8");
  REQUIRE( (&stdCells.footprint(id9) == &stdCells.footprint(id13) ));
  std::cout << "5 INV_X8 instances" << std::endl;

  auto id14 = stdCells.create("c14","NOR2_Z16");
  auto id15 = stdCells.create("c15","NOR2_Z16");
  auto id16 = stdCells.create("c16","NOR2_Z16");
  auto id17 = stdCells.create("c17","NOR2_Z16");
  REQUIRE( (&stdCells.footprint(id14) == &stdCells.footprint(id17) ));
  std::cout << "4 NOR2_X16 instances" << std::endl;
  
  auto id18 = stdCells.create("c18","DFF_X128");
  auto id19 = stdCells.create("c19","DFF_X128");
  auto id20 = stdCells.create("c20","DFF_X128");
  REQUIRE( (&stdCells.footprint(id18) == &stdCells.footprint(id20) ));
  std::cout << "3 DFF_X32 instances" << std::endl;
}


TEST_CASE("Proxy", "[structural][proxy]") 
{
  std::cout << "-------------Proxy---------------" << std::endl;
  
  {
    std::cout << "License Proxy for University License...." << std::endl;
    RoutingOptimizationProxy routingOptimization(LicenseType::UNIVERSITY_LICENSE);
    routingOptimization.lowEffortRoutingOptimization();
    routingOptimization.mediumEffortRoutingOptimization();
    routingOptimization.highEffortRoutingOptimization();
  }

  {
    std::cout << "License Proxy for Basic License...." << std::endl;
    RoutingOptimizationProxy routingOptimization(LicenseType::BASIC_LICENSE);
    routingOptimization.lowEffortRoutingOptimization();
    routingOptimization.mediumEffortRoutingOptimization();
    routingOptimization.highEffortRoutingOptimization();
  }

  {
    std::cout << "License Proxy for Full License...." << std::endl;
    RoutingOptimizationProxy routingOptimization(LicenseType::FULL_LICENSE);
    routingOptimization.lowEffortRoutingOptimization();
    routingOptimization.mediumEffortRoutingOptimization();
    routingOptimization.highEffortRoutingOptimization();
  }
}

