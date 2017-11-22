#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <common/optimization.hpp>
#include <common/physicalsynthesissteps.hpp>
#include <patterns/behavioral/command/command.hpp>


#include <patterns/creational/abstract_factory.hpp>
#include <patterns/creational/factory_method.hpp>
#include <patterns/creational/singleton.hpp>

using namespace creational;
using namespace common;

//---------------------- Creational TestCases -----------------------------//

TEST_CASE("Abstract factory", "[creational][abstract_factory]") {
  std::cout << "-------------Abstract Factory---------------" << std::endl;

  std::cout << "---Local Optimization" << std::endl;
  DetailedPlacementAndSpreadingEngine localOptimizationEngine( std::make_unique<LocalCellOptimizationFactory>() );
  localOptimizationEngine.minimizeCongestionAndWirelength();

  std::cout << "---Global Optimization" << std::endl;
  DetailedPlacementAndSpreadingEngine globalOptimizationEngine( std::make_unique<GlobalCellOptimizationFactory>() );
  globalOptimizationEngine.minimizeCongestionAndWirelength();
}

TEST_CASE("Factory method", "[creational][factory_method]") {
  std::cout << "-------------Factory Method---------------" << std::endl;

  OptimizationFactory optFactory;

  REQUIRE_THROWS(optFactory.create("timing-opt"));
  optFactory.registerNewType<TimingOptimization>("timing-opt");
  REQUIRE_NOTHROW(optFactory.create("timing-opt"));

  std::unique_ptr<Optimization> areaOpt = optFactory.create("area-opt");
  std::unique_ptr<Optimization> powerOpt = optFactory.create("power-opt");
  areaOpt->optimize();
  powerOpt->optimize();
}

TEST_CASE("Singleton", "[creational][singleton]") {
  std::cout << "-------------Singleton---------------" << std::endl;

  StandardCellLibrary& cellLibrary = StandardCellLibrary::getInstance();
  StandardCellLibrary& cellLibrary2 = StandardCellLibrary::getInstance();
  REQUIRE(&cellLibrary == &cellLibrary2);
}



//---------------------- Behavioral TestCases -----------------------------//

TEST_CASE("Command", "[behavioral][command]") {
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
