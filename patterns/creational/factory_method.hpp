#ifndef PATTERNS_CREATIONAL_FACTORY_METHOD_HPP
#define PATTERNS_CREATIONAL_FACTORY_METHOD_HPP

#include <exception>
#include <memory>
#include <unordered_map>
#include <type_traits>

#include <common/optimization.hpp>

namespace creational
{

template <typename Base, typename KeyType = std::string>
class Factory
{
  using FunctionType = std::function<std::unique_ptr<Base>()>;
  using RegistrationContainer = std::unordered_map<KeyType, FunctionType>;
  RegistrationContainer m_registeredTypes;

  public: 
 
    virtual ~Factory(){}
  
    template <typename T>
    std::enable_if_t< std::is_base_of<Base, T>::value, bool >
    registerNewType(KeyType key)
    {
      auto inserted =  m_registeredTypes.emplace( key, []() -> std::unique_ptr<Base> { return std::make_unique<T>(); } );
      return inserted.second;
    }

    std::unique_ptr<Base> create(KeyType key)
    {
      auto mapped = m_registeredTypes.find(key);
      if( mapped == std::end(m_registeredTypes))
        throw std::runtime_error("The Following Key Is Not Registered In The Factory: " + key );

      return mapped->second();
    }
};

class OptimizationFactory : public Factory<common::Optimization>
{
  public:
    OptimizationFactory()
    {
      registerNewType<common::PowerOptimization>("power-opt");
      registerNewType<common::AreaOptimization>("area-opt");
    }
};

} // end of namespace creational

#endif //PATTERNS_CREATIONAL_FACTORY_METHOD_HPP


