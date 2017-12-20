#ifndef PATTERNS_STRUCTURAL_ADAPTER_HPP
#define PATTERNS_STRUCTURAL_ADAPTER_HPP
 
#include <iostream>
#include <common/utils.hpp>

namespace structural
{
  class Legacy_Gui
  {
    std::vector<std::pair<common::Location, common::Location>> m_rectangles;
    public:
      Legacy_Gui()
      {
        std::cout << "Constructing Legacy_Gui" << std::endl;
      }
      ~Legacy_Gui()
      {
        std::cout << "Destructing Legacy_Gui" << std::endl;
      }

      unsigned draw_rectangle(common::Location lowerLeftCorner, common::Location upperRightCorner)
      {
        std::cout << "Legacy draw_rectangle -> LLC " << lowerLeftCorner << " URC " << upperRightCorner << std::endl;
        m_rectangles.push_back(std::make_pair(lowerLeftCorner, upperRightCorner));
        return m_rectangles.size()-1;
      }

      void move_rectangle(unsigned id, common::Location newLowerLeftCorner)
      {
        std::cout << "Legacy move_rectangle -> from " << m_rectangles.at(id).first << " to " << newLowerLeftCorner << std::endl;
        auto & old_rectangle = m_rectangles.at(id); 
        auto new_x_urc = old_rectangle.second.first + (old_rectangle.first.first - newLowerLeftCorner.first);
        auto new_y_urc = old_rectangle.second.second + (old_rectangle.first.second - newLowerLeftCorner.second);
        m_rectangles.at(id) = std::make_pair(newLowerLeftCorner, common::Location(new_x_urc, new_y_urc));
      }
  };

  class New_Gui 
  {
    Legacy_Gui m_legacy;
    std::vector<unsigned> m_cell_id_to_rectangle_id;

    public:
      New_Gui(int num_cells) : m_cell_id_to_rectangle_id(num_cells)
      {
        std::cout << "Constructing New_Gui" << std::endl;
      }
      ~New_Gui()
      {
        std::cout << "Destructing New_Gui" << std::endl;
      }

      void draw_cell(const common::Cell & cell)
      {
        std::cout << "New draw_cell" << std::endl;
        common::Location lowerLeftCorner(cell.location.first, cell.location.second);
        common::Location upperRightCorner(cell.location.first + cell.shape.first, cell.location.second + cell.shape.second);
        m_cell_id_to_rectangle_id.at(cell.id) = m_legacy.draw_rectangle(lowerLeftCorner, upperRightCorner); 
      }

      void move_cell(const common::Cell & cell, common::Location newLowerLeftCorner)
      {
        std::cout << "New draw_cell" << std::endl;
        m_legacy.move_rectangle(m_cell_id_to_rectangle_id.at(cell.id), newLowerLeftCorner);
      }
  };
  
} //end of namespace structural


#endif //PATTERNS_STRUCTURAL_ADAPTER_HPP
