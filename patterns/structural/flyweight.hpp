#ifndef PATTERNS_STRUCTURAL_FLYWEIGHT_HPP
#define PATTERNS_STRUCTURAL_FLYWEIGHT_HPP
 
#include <iostream>
#include <memory>
#include <common/utils.hpp>
#include <unordered_set>

namespace structural
{

template <class T>
class FlyweightFactory
{
  std::unordered_set<T> m_values;

  public:
    const T& getValue(T key)
    {
      auto ret = m_values.find(key);
      if(ret != std::end(m_values))
      {
        return *ret;
      }
      else
      {
        return *m_values.emplace(key).first;
      }
    }
};

class StandardCells
{
  FlyweightFactory<std::string> m_footprintFactory;
  //instrinsic characteristics (i.e. shared among cells with the same footprint)
  std::vector<const std::string*> m_footprints;
  //non-shareable characteristic
  std::vector<std::string> m_names;
  unsigned m_numCells;
  
  public:
    void reserve(unsigned numCells)
    {
      m_footprints.reserve(numCells);
      m_names.reserve(numCells);
    }

    unsigned create(std::string name, std::string footprint)
    {
      ++m_numCells;
      m_names.emplace_back(name);
      m_footprints.emplace_back(&m_footprintFactory.getValue(footprint));
      return m_numCells;
    }

    const std::string& footprint(unsigned id)
    {
      return *m_footprints.at(id);
    }
};


} //end of namespace structural


#endif //PATTERNS_STRUCTURAL_FLYWEIGHT_HPP
