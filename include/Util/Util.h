/*****************************
 * Copyright 2025 Cracklings *
 * Created Mar 15 2025       *
 *****************************/

#pragma once

namespace Prism::Util
{
  template <typename _Main_object, typename... _Kept_alive>
  class Scoped
  {
  public:
    Scoped(_Main_object main_object, _Kept_alive... kept_alive) : _main_object(main_object), _kept_alive(kept_alive...)
    {}

    _Main_object &operator*() { return _main_object; }

    _Main_object *operator->() { return &_main_object; }

    operator _Main_object &() { return _main_object; }

    operator _Main_object *() { return &_main_object; }

    operator bool() const { return _main_object != nullptr; }

  private:
    _Main_object               _main_object;
    std::tuple<_Kept_alive...> _kept_alive;
  };

  template <template <typename> typename _Container, typename _Main_object, typename... _Kept_alive>
  class Scoped_container : public Scoped_container_recurse<_Container, _Main_object, _Kept_alive...>
  {
  public:
    Scoped_container(_Container<_Main_object> main_container, _Kept_alive... kept_alive)
        : Scoped_container_recurse<_Container, _Main_object, _Kept_alive...>(main_container, kept_alive...)
    {}
  };

  template <template <typename> typename _Container, typename _Head, typename... _Rest>
  class Scoped_container_recurse : public Scoped_container_recurse<_Container, _Rest...>
  {
  public:
    Scoped_container_recurse(_Container<_Head> head, _Rest... rest)
        : Scoped_container_recurse<_Container, _Rest...>(rest...), _head(head)
    {}

    template <std::string _Field_name>
    void set(_Container<_Head> head)
    {
      _head = head;
    }

    template <std::string _Field_name>
    _Container<_Head> &get()
    {
      return _head;
    }

  private:
    _Container<_Head> _head;
  };

} // namespace Prism::Util
