#ifndef PATTERNS_BEHAVIORAL_CHAIN_OF_RESPONSABILITY_HPP
#define PATTERNS_BEHAVIORAL_CHAIN_OF_RESPONSABILITY_HPP
 
#include <iostream>
#include <memory>
#include <common/utils.hpp>

namespace behavioral
{

//Different optimizations in a chain build by the user?

class RipUpAndReRouteHandler
{
  std::shared_ptr<RipUpAndReRouteHandler> m_parent;

  protected:
    virtual bool routeNet(common::Net & net) = 0;

  public:
    RipUpAndReRouteHandler(std::shared_ptr<RipUpAndReRouteHandler> parent = nullptr) : m_parent(parent)
    {
    }
    virtual ~RipUpAndReRouteHandler() 
    {
    }
   
    virtual void handleRouteRequest(common::Net & net)
    {
      if(m_parent)
      {
        m_parent->handleRouteRequest(net);
      }
    }
};

class FastGreedyRipUpAndReRoute : public RipUpAndReRouteHandler
{
  protected:
    bool routeNet(common::Net & net) override
    {
      std::cout << "GreedyRipUpAndReRoute trying to route net: " << net.name << std::endl;

      //here goes the code to route the net
      return net.num_pins < 4;
    }

  public:
    FastGreedyRipUpAndReRoute(std::shared_ptr<RipUpAndReRouteHandler> parent = nullptr) : RipUpAndReRouteHandler(parent)
    {
      std::cout << "Constructing GreedyRipUpAndReRoute" << std::endl;
    }
    ~FastGreedyRipUpAndReRoute()
    {
      std::cout << "Destructing GreedyRipUpAndReRoute" << std::endl;
    }


    void handleRouteRequest(common::Net & net) override
    {
      if(!routeNet(net))
      {
        std::cout << "Net Not routed" << std::endl;
        RipUpAndReRouteHandler::handleRouteRequest(net);
      }
    }
};

class AStarRipUpAndReRoute : public RipUpAndReRouteHandler
{
  protected:
    bool routeNet(common::Net & net) override
    {
      std::cout << "AStarRipUpAndReRoute trying to route net: " << net.name << std::endl;

      //here goes the code to route the net
      return net.num_pins < 6;
    }

  public:
    AStarRipUpAndReRoute(std::shared_ptr<RipUpAndReRouteHandler> parent = nullptr) : RipUpAndReRouteHandler(parent)
    {
      std::cout << "Constructing AStarRipUpAndReRoute" << std::endl;
    }
    ~AStarRipUpAndReRoute()
    {
      std::cout << "Destructing AStarRipUpAndReRoute" << std::endl;
    }

    void handleRouteRequest(common::Net & net) override
    {
      if(!routeNet(net))
      {
        std::cout << "Net Not routed" << std::endl;
        RipUpAndReRouteHandler::handleRouteRequest(net);
      }
    }
};

class ILPRipUpAndReRoute : public RipUpAndReRouteHandler
{
  protected:
    bool routeNet(common::Net & net) override
    {
      std::cout << "ILPRipUpAndReRoute trying to route net: " << net.name << std::endl;

      //here goes the code to route the net
      return true;
    }

  public:
    ILPRipUpAndReRoute(std::shared_ptr<RipUpAndReRouteHandler> parent = nullptr) : RipUpAndReRouteHandler(parent)
    {
      std::cout << "Constructing ILPRipUpAndReRoute" << std::endl;
    }
    ~ILPRipUpAndReRoute()
    {
      std::cout << "Destructing ILPRipUpAndReRoute" << std::endl;
    }

    void handleRouteRequest(common::Net & net) override
    {
      if(!routeNet(net))
      {
        std::cout << "Net Not routed" << std::endl;
        RipUpAndReRouteHandler::handleRouteRequest(net);
      }
    }
};

} //end of namespace behavioral

#endif //PATTERNS_BEHAVIORAL_CHAIN_OF_RESPONSABILITY_HPP
