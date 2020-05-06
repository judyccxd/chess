#include "Subject.h"
#include <iostream>
#include "observer.h"

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

Subject::~Subject() {}

void Subject::notifyObservers(bool player, int r, int c) {
  for(int i = 0; i < observers.size(); i++) {
    if(observers[i] == nullptr) {
      observers.erase(observers.begin() + i);
    }
  }
  // std::cout << "size" << observers.size() << std::endl;
  // int i = 0;
  for (auto &ob : observers) {
    ob->notify(player, r, c);
  }
}
