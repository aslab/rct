#ifndef __EXCEPTION_HPP
#define __EXCEPTION_HPP

#include <iostream>
using namespace std;

class Exception
{
  public:
    Exception(const char *format = "[no message]", ...);
    virtual ~Exception() {}

  protected:
    char msg[1024];
    friend ostream &operator<<(ostream &, const Exception&);
};

#define assert_exception(expr) { if(!(expr)){throw new Exception("%s: line %d: Assertion \"%s\" failed", __FILE__, __LINE__, #expr);} }
#define error_exception(string) { throw new Exception("%s: line %d: Error: %s", __FILE__, __LINE__, #string); }
#define TRY try {
#define CATCH } catch(Exception *e) { cout << *e << "\n"; exit(1); }

#endif
