#ifndef PATTERNS_BEHAVIORAL_COMMAND_HPP
#define PATTERNS_BEHAVIORAL_COMMAND_HPP

#include <functional>
#include <memory>
#include <vector>

#include <common/optimization.hpp>
#include <common/physicalsynthesissteps.hpp>


namespace behavioral
{

  class Command
  {
    using CommandFunction = std::function<void()>;
    using CommandQueue = std::vector<CommandFunction>;

    CommandQueue m_commands;

    protected: 
      void AddCommand(CommandFunction func);

    public:
      void Run();
         
  };

  class LowEffortPhysicalSynthesisFlow : public Command
  {
    public:
      LowEffortPhysicalSynthesisFlow(const common::MajorPhysicalSynthesisSteps & majorSteps);
  };

} // end of namespace behavioral

#endif //PATTERNS_BEHAVIORAL_COMMAND_HPP


