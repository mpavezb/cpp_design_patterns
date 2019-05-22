#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

/* Separation of Concerns.

- The Journal class should not care about persistence logic.

- If other Journal-like objects are created, we want to avoid
  defining persistence logic for each one.

- If the persistence manager grows, we keep all the logic in 
  the same place.

*/
struct Journal
{
  string title;
  vector <string> entries;

  Journal(const string& title) : title(title) {};

  void add_entry(const string& entry)
  {
    static int count = 1;
    entries.push_back(lexical_cast<string>(count++) + ": " + entry);
  }
};

struct PersistenceManager
{
  static void save(const Journal& j, const string& filename)
  {
    ofstream ofs(filename);
    for (auto& e : j.entries)
    {
      ofs << e << endl;
    }
  }
};

int main()
{
  Journal journal{"Dear Diary"};
  journal.add_entry("I ate a bug.");
  journal.add_entry("I also ate a spider.");

  PersistenceManager pm;
  pm.save(journal, "diary.txt");

  return 0;
}
