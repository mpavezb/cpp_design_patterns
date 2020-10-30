#pragma once

#include <string>
#include <vector>
using namespace std;

struct ChatRoom; // pre-declare the mediator

struct Person {
  string name;
  ChatRoom *room{nullptr}; // Pointer to global mediator
  vector<string> chat_log;

  explicit Person(const string &name);

  // send global message
  void say(const string &message) const;

  // send private message
  void pm(const string &who, const string &message) const;

  // receive a message
  void receive(const string &origin, const string &message);

  bool operator==(const Person &rhs) const;

  bool operator!=(const Person &rhs) const;
};
