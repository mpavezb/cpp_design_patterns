
class Printer {
  // resource is managed statically
  // different instances have access to the same resource.
  //
  // This field will not be inherited.
  static int id;

public:
  // API can lead to hard to find errors. The user might
  // not know that the resource is shared.
  int get_id() const { return id; }
  void set_id(int value) { id = value; }
};
int Printer::id = 0;

int main() {
  Printer p1, p2;
  p1.set_id(0);
  p2.get_id();
}
