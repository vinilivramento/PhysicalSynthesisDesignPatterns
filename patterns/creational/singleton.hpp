#ifndef PATTERNS_CREATIONAL_SINGLETON_HPP
#define PATTERNS_CREATIONAL_SINGLETON_HPP

namespace creational
{

class StandardCellLibrary
{
  StandardCellLibrary()
  {
    std::cout << "Constructing StandardCellLibary!" << std::endl;
  }

  public:

    StandardCellLibrary(const StandardCellLibrary & singleton) = delete;
    StandardCellLibrary(const StandardCellLibrary && singleton) = delete;
    void operator=(const StandardCellLibrary & singleton) = delete;

    ~StandardCellLibrary()
    {
      std::cout << "Destructing StandardCellLibrary!" << std::endl;
    }

    static StandardCellLibrary& getInstance()
    {
      static StandardCellLibrary instance;
      return instance;
    }
};

} // end of namespace creational

#endif //PATTERNS_CREATIONAL_SINGLETON_HPP

