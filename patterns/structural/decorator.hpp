#ifndef PATTERNS_STRUCTURAL_DECORATOR_HPP
#define PATTERNS_STRUCTURAL_DECORATOR_HPP
 
#include <iostream>
#include <memory>
#include <common/utils.hpp>

//Add responsabilities to an object dinamically. Conforms to the interface of a component that is being decorated

namespace structural
{
  class Painter
  {
    public:
      virtual ~Painter() {}
      virtual void paint() = 0;
  };

  class CellsPainter : public Painter
  {
    const std::vector<common::Cell> & m_cells;

    void paint_cell(const common::Cell & cell)
    {
      std::cout << "  CellsPainter::paint_cell() - " << cell.id << std::endl;
    }

    public:
      CellsPainter(const std::vector<common::Cell> & cells) : m_cells(cells)
      {
        std::cout << "Constructing CellsPainter" << std::endl;
      }

      ~CellsPainter()
      {
        std::cout << "Destructing CellsPainter" << std::endl;
      }

      void paint() override
      {
        std::cout << "CellsPainter::paint()" << std::endl;
        for(auto & cell : m_cells)
          paint_cell(cell);
      }
  };

  class PainterDecorator : public Painter
  {
    std::unique_ptr<Painter> m_painter;

    public:
      PainterDecorator(std::unique_ptr<Painter> && painter) : m_painter( std::move(painter) )
      {
      }

      virtual void paint() override
      {
        m_painter->paint();
      }
  };

  class PinsPainter : public PainterDecorator
  {
    using Parent = PainterDecorator;
    const std::vector<common::Pin> & m_pins;
   
    void paint_pin(const common::Pin & pin)
    {
      std::cout << "  PinsPainter::paint_pin() - " << pin.id << std::endl;
    }

    public:
    
      PinsPainter(std::unique_ptr<Painter> && painter, const std::vector<common::Pin> & pins) : 
        PainterDecorator( std::move(painter) ), m_pins(pins)
      {
        std::cout << "Constructing PinsPainter" << std::endl;
      }

      ~PinsPainter()
      {
        std::cout << "Destructing PinsPainter" << std::endl;
      }

      void paint() override
      {
        Parent::paint();
        std::cout << "PinsPainter::paint()" << std::endl;
        for(auto & pin : m_pins)
          paint_pin(pin);
      }
  };

  class SlacksPainter : public PainterDecorator
  {
    using Parent = PainterDecorator;
    const std::vector<common::TimingPoint> & m_timing_points;

    void paint_slack(const common::TimingPoint & timing_point)
    {
      std::cout << "  SlacksPainter::paint_slack() - " << timing_point.id << std::endl;
    }

    public:
      SlacksPainter(std::unique_ptr<Painter> && painter, const std::vector<common::TimingPoint> & timing_points) :
        PainterDecorator( std::move(painter) ), m_timing_points(timing_points)
      {
        std::cout << "Constructing SlacksPainter" << std::endl;
      }

      ~SlacksPainter()
      {
        std::cout << "Destructing SlacksPainter" << std::endl;
      }

      void paint() override
      {
        Parent::paint();
        std::cout << "SlacksPainter::paint()" << std::endl;
        for(auto & tp : m_timing_points)
          paint_slack(tp);
      }
  };
} //end of namespace structural


#endif //PATTERNS_STRUCTURAL_DECORATOR_HPP
