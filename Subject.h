#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>

struct Info;
class Observer;

class Subject {
  std::vector<Observer*> observers;

 public:
  void attach(Observer *o);
  void notifyObservers(bool player, int r, int c);
  virtual ~Subject() = 0;
};

#endif
