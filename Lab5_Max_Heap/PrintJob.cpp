#include "PrintJob.h"

PrintJob::PrintJob (const int &setP, const int &setJ, const int &numP ):priority(setP), jobNumber(setJ), numPages(numP){}
int PrintJob::getPriority () const {
    return priority;
}

int PrintJob::getJobNumber () const {
    return jobNumber;
}

int PrintJob::getPages () const {
    return numPages;
}