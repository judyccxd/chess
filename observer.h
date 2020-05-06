#ifndef _OBSERVER_H_
#define _OBSERVER_H_


class Subject;

class Observer {
 public:
  virtual void notify(bool player, int r, int c) = 0; // pass the Subject that called the notify method
  virtual ~Observer() = default;
  virtual void print() = 0;
};

#endif
