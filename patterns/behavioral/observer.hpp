#ifndef PATTERNS_BEHAVIORAL_OBSERVER_HPP
#define PATTERNS_BEHAVIORAL_OBSERVER_HPP
 
#include <iostream>
#include <memory>
#include <unordered_set>

#include <common/utils.hpp>

namespace behavioral
{
 
  class Observer
  {
    public: 
      virtual ~Observer() {}
      virtual void create() = 0;
      virtual void reserve(unsigned size) = 0;
      virtual unsigned size() = 0;
  };

  using CellId = unsigned;

  class Subject 
  {
    public:
      virtual ~Subject() {}
      virtual void attach(Observer * observer) = 0;
      virtual void detach(Observer * observer) = 0;
      
      virtual unsigned create() = 0;
      virtual void reserve(unsigned size) = 0;
      virtual unsigned size() = 0;
  };

  class StandardCells : public Subject
  {
    std::unordered_set< Observer * > m_observers;
    std::vector<CellId> m_cellIds;

    public:
      void attach(Observer * observer) override
      {
        m_observers.emplace(observer);
      }
      
      void detach(Observer * observer) override
      {
        m_observers.erase(observer); 
      }

      unsigned create() override
      {
        m_cellIds.push_back(m_cellIds.size());
        for(auto & observer : m_observers)
        {
          observer->create();
        }
        return m_cellIds.size() - 1;
      }

      void reserve(unsigned size) override
      {
        m_cellIds.reserve(size);
        for(auto & observer : m_observers)
        {
          observer->reserve(size);
        }
      }

      unsigned size() override
      {
        return m_cellIds.size();
      }
  };

  template <class T>
  class CellProperties : public Observer
  {
    std::vector<T> m_properties;
    public:
      
      void create() override
      {
        m_properties.push_back(T());
      }

      void reserve(unsigned size) override
      {
        m_properties.reserve(size);
      }

      unsigned size() override
      {
        return m_properties.size();
      }

      T &operator[](CellId id) 
      {
        return m_properties[id];
      }

      const T &operator[](CellId id) const 
      {
        return m_properties[id];
      }
  };

} //end of namespace behavioral

#endif //PATTERNS_BEHAVIORAL_OBSERVER_HPP
