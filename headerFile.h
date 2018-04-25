//CHRIS JOSEPH
//CS3377.501
//CSJ160130@UTDALLAS.EDU
//HEADER FILE WHICH HAS CLASSES FOR MAIN CLASS

#ifndef HEADERFILE_H_
#define HEADERFILE_H_

#include <iostream>
#include <string>
#include <stdint.h>


using namespace std;

class BinaryFileHeader
{

 public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;

};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{

 public:

  uint8_t strlength;
  char stringBuffer[maxRecordStringLength];
};




#endif
