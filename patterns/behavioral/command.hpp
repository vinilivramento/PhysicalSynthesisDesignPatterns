#ifndef PATTERNS_BEHAVIORAL_COMMAND_HPP
#define PATTERNS_BEHAVIORAL_COMMAND_HPP

#include <iostream>
#include <memory>
#include <stack>

#include <boost/variant.hpp>

#include <common/utils.hpp>

namespace behavioral
{
//GUI with undo capability

enum TransformType {MOVE, RESIZE};

class Transform
{
  public:
    unsigned cell_id;
    TransformType type;
    boost::variant<common::Location, std::string> oldState;
    boost::variant<common::Location, std::string> newState;
};

//Receiver
class CellTransformer
{
  public:
    void transform(const Transform & transform)
    {
      if(transform.type == TransformType::MOVE)
      {
        std::cout << "Moving cell " << transform.cell_id << " from " << boost::get<common::Location>(transform.oldState) 
                                                         << " to "   << boost::get<common::Location>(transform.newState) << std::endl;    
      }
      else if(transform.type == TransformType::RESIZE)
      {
        std::cout << "Resizing cell " << transform.cell_id << " from " << boost::get<std::string>(transform.oldState) 
                                                           <<" to " << boost::get<std::string>(transform.newState) << std::endl;    
      }
    }
};

//command to change a cell characteristic, like size, location, etc
class Command
{
  protected:

  public:
    virtual ~Command() {}
   
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class CellTransformCommand : public Command
{
  using ReceiverFunc = std::function<void(const Transform & transform)>;
  ReceiverFunc m_receiver;
  Transform m_transform;

  public:
    CellTransformCommand(ReceiverFunc receiver, Transform && transform) : m_receiver(receiver), m_transform(std::move(transform))
    {
    }

    void execute() override
    {
      m_receiver(m_transform);
    }

    void undo() override
    {
      std::swap(m_transform.newState, m_transform.oldState);
      execute();
    }

    void redo() override
    {
      std::swap(m_transform.newState, m_transform.oldState);
      execute();
    }
};

class CommandInvoker
{
  std::stack<std::shared_ptr<Command>> m_undoStack;
  std::stack<std::shared_ptr<Command>> m_redoStack;

  public:
    void executeCommand(std::shared_ptr<Command> command)
    {
      command->execute();
      m_undoStack.push(command);
    }

    void undo()
    {
      if(!m_undoStack.empty())
      {
        m_undoStack.top()->undo();
        m_redoStack.push(m_undoStack.top());
        m_undoStack.pop();
      }
    }

    void redo()
    {
      if(!m_redoStack.empty())
      {
        m_redoStack.top()->redo();
        m_undoStack.push(m_redoStack.top());
        m_redoStack.pop();
      }
    }
};

} // end of namespace behavioral

#endif //PATTERNS_BEHAVIORAL_COMMAND_HPP


