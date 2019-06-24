#include <string>
#include <iostream>

using namespace std;

struct Pingable
{
  virtual string ping(const string& message) = 0;
};

struct Pong: Pingable
{
  string ping(const string& message) override
  {
    return message + " pong";
  }
};


// This server is executed on another proccess or machine.
struct Server
{
  static void call(const string& request, string& response)
  {
    response = request + " pong";
  }
};

// Communication proxy allows us to make an
// external call to solve the query.
struct RemotePong: Pingable
{
  string ping(const string& message) override
  {
    string response;
    Server::call(message, response);
    return response;
  }
};

void tryit(Pingable& pp)
{
  cout << pp.ping("ping") << endl;
}

int main()
{
  // Local Server
  Pong pp;
  for (size_t i=0; i<3; ++i) {
    tryit(pp);
  }

  // Remote Server
  RemotePong rp;
  for (size_t i=0; i<3; ++i) {
    tryit(rp);
  }
  return 0;
}
