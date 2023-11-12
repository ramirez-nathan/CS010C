#ifndef __PRINTJOB_H
#define __PRINTJOB_H
#include <iostream>
using namespace std;

class PrintJob {
private:
  int priority;
  int jobNumber;
  int numPages;

public:
  PrintJob (const int&, const int&, const int&);
  int getPriority ( ) const;
  int getJobNumber ( ) const;
  int getPages ( ) const;
  //You can add additional functions here
};
#endif