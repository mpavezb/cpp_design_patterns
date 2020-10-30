#pragma once

#include "Person.h"
#include <algorithm>

struct ChatRoom {
  // keeps participants
  vector<Person *> people;

  // mediate message forwarding (using the visitor pattern).
  void broadcast(const string &origin, const string &message);

  // mediate entity update.
  void join(Person *p);

  void message(const string &origin, const string &who, const string &message) {
    auto target = std::find_if(begin(people), end(people),
                               [&](const Person *p) { return p->name == who; });
    if (target != end(people)) {
      (*target)->receive(origin, message);
    }
  }
};
