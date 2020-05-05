#include <string>
class User
{
private:
  std::string username;
public:
  void setName(std::string name)
  {
    username = name;
  }
  std::string getName()
  {
    return username;
  }
};