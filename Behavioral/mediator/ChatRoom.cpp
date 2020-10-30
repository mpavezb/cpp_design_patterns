#include "ChatRoom.h"
#include "Person.h"

void ChatRoom::broadcast(const string &origin, const string &message) {
  for (auto p : people)
    if (p->name != origin)
      // visitor pattern here
      p->receive(origin, message);
}

void ChatRoom::join(Person *p) {
  string join_msg = p->name + " joins the chat";
  broadcast("room", join_msg);
  p->room = this;
  people.push_back(p);
}
