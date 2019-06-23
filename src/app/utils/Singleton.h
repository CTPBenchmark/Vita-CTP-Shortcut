#pragma once

#include <utility>
#include <stdexcept>

template <class T>
class Singleton
{
public:
  template <typename... Args>
  static T* createInstance(Args... args)
  {
    if (!instance_)
      {
        instance_ = new T(std::forward<Args>(args)...);
      }

    return instance_;
  }

  static T* getInstance()
  {
    if (!instance_)
      {
        throw std::runtime_error("Accessed singleton before that instance is created");
      }

    return instance_;
  }

  static
  void destroyInstance()
  {
    delete instance_;
    instance_ = nullptr;
  }

private:
  static T* instance_;
};

template <class T> T*  Singleton<T>::instance_ = nullptr;
