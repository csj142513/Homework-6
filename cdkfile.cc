/*
 * Usage of CDK Matrix
 *
 * File:   cdkfile.cc
 * Author: CHRIS JOSEPH
 * Email:  csj160130@utdallas.edu
 * Course Number:  cs 3377.501
 */

#include <iostream>
#include "cdk.h"
#include "headerFile.h"
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <sstream>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


string decimalToHex(uint32_t n)
{   


 
  // char array to store hexadecimal number
  char hex[100];
     
  // counter for hexadecimal number array
  int i = 0;
  while(n!=0)
    {   
      // temporary variable to store remainder
      int temp  = 0;
         
      // storing remainder in temp variable.
      temp = n % 16;
         
      // check if temp < 10
      if(temp < 10)
        {
	  hex[i] = temp + 48;
	  i++;
        }
      else
        {
	  hex[i] = temp + 55;
	  i++;
        }
         
      n = n/16;
    }

  string word = "";

  // printing hexadecimal number array in reverse order
  for(int j=i-1; j>=0; j--){
    word += hex[j];
  }

  return word;
}


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  BinaryFileHeader *value = new BinaryFileHeader();
  BinaryFileRecord *value2 = new BinaryFileRecord();

  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) value, sizeof(BinaryFileHeader));

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */

  uint32_t number = value->magicNumber;
  //cout << "Number is: " << number << endl;
 string  word = decimalToHex(number);
 string word1 = "Magic: 0x" + word;
  setCDKMatrixCell(myMatrix, 1, 1,word1.c_str());
  //drawCDKMatrix(myMatrix, true); 
  number = 0;  
  number = value->versionNumber;

  int y = (int) number;

  //word;//string which will contain the result

  stringstream convert; // stringstream used for the conversion

  convert << y;//add the value of Number to the characters in the stream

  word = convert.str();//set Result to the content of the stream

  word1 = "";
  word1 = "Version: " + word;
  setCDKMatrixCell(myMatrix, 1, 2, word1.c_str());
  convert.str("");
  uint64_t number2 = value->numRecords;
  y = 0;
  y = (int) number2;
  convert << y;
  word = "";
  word = convert.str();
  word1 = "";
  word1 = "NumRecords: " + word;
  setCDKMatrixCell(myMatrix, 1, 3, word1.c_str());
  drawCDKMatrix(myMatrix, true); 
  int count1 = 2;
  //char store[26];
  for (int count = 0; count < 4; count++)
    {
      binInfile.read((char *) value2, sizeof(BinaryFileRecord));
      convert.str("");
      uint8_t length = value2->strlength;
      int newlength = (int) length;
      convert << newlength;
      string newWord = convert.str();
      setCDKMatrixCell(myMatrix, count1, 1, newWord.c_str());
      drawCDKMatrix(myMatrix, true);
      word = "";
      //char store[26] = "";
      for (int counterr = 0; counterr < 26; counterr++)
	{
	  word += value2->stringBuffer[counterr];
	}
      setCDKMatrixCell(myMatrix, count1, 2, word.c_str());//string(store).c_str());
      drawCDKMatrix(myMatrix, true);

      count1++;
    }
  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
  //cout << word;

  //cout << string(store);
}
