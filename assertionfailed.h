#ifndef UNITTESTS_ASSERTIONFAILED_H__
#define UNITTESTS_ASSERTIONFAILED_H__

#include <sstream>
#include <string>

namespace unittests
{

/**
  \class AssertionFailed assertionfailed.h "ut/assertionfailed.h"
  \ingroup Unittests
  \brief Stores information related to an assertion, allows for data to be added and retrieved.

  The AssertionFailed class stores information about failed assertions.
  Information can be added to an AssertionFailed object using the << operator, this will add information associated with a failed assertion. To retrieve the information back use the get_info method.
  */
class AssertionFailed
{
public:
  /**
    \brief Constructs an empty AssertionFailed object
    */
  AssertionFailed() {}
  /**
    \brief Constructs an AssertionFailed object with the passed in data
    \param data - Initial string to be used for the information
    */
  AssertionFailed(const char* data)
  {
    info_ << data;
  }
  virtual ~AssertionFailed() {}

  /**
    \brief Adds information to this AssertionFailed object
    \param val - The value to be added as information to this object
    \return Returns a reference to this object with the value added to the information held by this object
    */
  template <typename T>
  AssertionFailed& operator<<(T val)
  {
    info_ << val;
    return *this;
  }

  /**
    \brief return a string representation of the information stored by this AssertionFailed object
    */
  std::string get_info()
  {
    return info_.str();
  }
private:
  std::stringstream info_;
};

} // namespace

#endif // UNITTESTS_ASSERTIONFAILED_H__

/* vim: set cindent sw=2 expandtab : */

