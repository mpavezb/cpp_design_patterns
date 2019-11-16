#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Document;

/* This interface is OK if all IMachines really provide
   print, scan and fax methods.

   It forces implementers to create dummy methods when
   used on a simpler class.
*/
struct BadIMachine {
  virtual void print(Document &doc) = 0;
  virtual void scan(Document &doc) = 0;
  virtual void fax(Document &doc) = 0;
};

/* A Scanner should not implement an IMachine interface.
- There are 2 options: Leave blank body or throw an exception.
- It gives the user a wrong understanding of the class. It
  will think our scanner can also print.

*/
struct BadScanner : BadIMachine {
  void print(Document &doc) override {
    throw new logic_error("Not implemented.");
  }

  void scan(Document &doc) override {
    // OK
  }

  void fax(Document &doc) override {
    throw new logic_error("Not implemented.");
  }
};

/* Segregated Classes: IPrinter, IScanner and IFax. */
struct IPrinter {
  virtual void print(Document &doc) = 0;
};
struct IScanner {
  virtual void scan(Document &doc) = 0;
};
struct IFax {
  virtual void fax(Document &doc) = 0;
};

/* Printer does not require to implement dummy methods. */
struct Printer : IPrinter {
  void print(Document &doc) override {
    // OK
  }
};
struct Scanner : IScanner {
  void scan(Document &doc) override {
    // OK
  }
};

/* Complex Machine implements printer and scanner interfaces. */
struct ComplexMachine : IPrinter, IScanner {
  void print(Document &doc) override {
    // OK
  }

  void scan(Document &doc) override {
    // OK
  }
};

/* Now we can also use a decorator to create a complex machine. */
struct DecoratedMachine : IPrinter, IScanner {
  IPrinter &printer;
  IScanner &scanner;

  DecoratedMachine(IPrinter &printer, IScanner &scanner)
      : printer(printer), scanner(scanner) {}

  void print(Document &doc) override { printer.print(doc); }

  void scan(Document &doc) override { scanner.scan(doc); }
};

int main() { return 0; }
