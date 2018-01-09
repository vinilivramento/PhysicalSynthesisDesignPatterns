#ifndef PATTERNS_STRUCTURAL_COMPOSITE_HPP
#define PATTERNS_STRUCTURAL_COMPOSITE_HPP
 
#include <iostream>
#include <memory>
#include <unordered_set>
#include <common/utils.hpp>

namespace structural
{
  // Component
  class Element
  {
    public:
      virtual ~Element() {} 
      
      virtual void add(std::shared_ptr<Element> element) {}
      virtual void erase(std::shared_ptr<Element> element) {}
      
      virtual void setColor(const std::string & color) = 0;
      virtual void setDontTouch(bool dontTouch) = 0;
  };

  // Leaf element
  class CellVisualization : public Element
  {
    const common::Cell & m_cell;
    public:
      CellVisualization(const common::Cell & cell) : m_cell(cell) 
      {
        std::cout << "Constructing CellVisualization" << std::endl;
      }

      ~CellVisualization()
      {
        std::cout << "Destructing CellVisualization" << std::endl;
      }
  
      void setColor(const std::string & color) override
      {
        std::cout << "Setting color of cell " << m_cell.id << " to " << color << std::endl;
      }

      void setDontTouch(bool dontTouch) override
      {
        std::cout << "Setting cell " << m_cell.id << " to dontTouch =  " << dontTouch << std::endl;
      }
  };

  class CellVisualizationGroup : public Element
  {
    std::unordered_set< std::shared_ptr<Element> > m_cells;

    public:
      CellVisualizationGroup()
      {
        std::cout << "Constructing CellVisualizationGroup" << std::endl;
      }

      ~CellVisualizationGroup()
      {
        std::cout << "Destructing CellVisualizationGroup" << std::endl;
      }

      void add(std::shared_ptr<Element> element) override
      {
        m_cells.emplace(element);
      }

      void erase(std::shared_ptr<Element> element) override 
      {
        m_cells.erase(element);
      }

      void setColor(const std::string & color) override
      {
        for(auto & cell : m_cells)
        {
          cell->setColor(color);
        }
      }

      void setDontTouch(bool dontTouch) override
      {
        for(auto & cell : m_cells)
        {
          cell->setDontTouch(dontTouch);
        }
      }
  };

} //end of namespace structural


#endif //PATTERNS_STRUCTURAL_COMPOSITE_HPP
