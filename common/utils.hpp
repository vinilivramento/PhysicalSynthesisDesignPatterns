#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <ostream>

namespace common
{
  //width,height
  using Shape    = std::pair<unsigned, unsigned>;
  //x,y
  using Location = std::pair<unsigned, unsigned>;
  //rise,fall
  using TimingInfo = std::pair<double, double>;
  
  enum class LogicFunction {INV, NAND2, NOR2};

  struct Net
  {
    std::string name;
    unsigned num_pins;
  };

  struct TimingPoint
  {
    unsigned id;
    unsigned pin_id;
    double slack;
  };

  struct Pin
  {
    unsigned id;
    unsigned cell_id;
    Location offset;
    Shape shape;
  };

  struct Cell
  {
    unsigned id;
    common::Location location;
    common::Shape shape;
    std::string size;
  };

} //end of namespace common

namespace std
{
  std::ostream& operator<< (std::ostream& os, const common::Location & location)
  {
    os << "(" << location.first << ", " << location.second << ")";
    return os;  
  }

  std::ostream& operator<< (std::ostream& os, const common::TimingInfo & info)
  {
    os << "(" << info.first << ", " << info.second << ")";
    return os;  
  }

  std::ostream& operator<< (std::ostream& os, const common::Cell & cell)
  {
    os << " Cell Id: " << cell.id
    << " Location: " << cell.location 
    << " Shape: " << cell.shape;
    return os;
  }
}

#endif //COMMON_UTILS_HPP


