#pragma once

// compare function, takes two items and returns
// -1 if v1<v2
// 1 if v1>v2
// 0 if v1==v2

typedef int (*CompareFn)(void* v1, void* v2);

//returns the position of an an item od size item_size
//within a file of records
//the file should have been sorted beforehand
//to compare the items the function uses the compare function
//pointer
int binaryFileSearch(int fd, void* item, int item_size, CompareFn compare);

// writes a record of size item_size in position pos in the file
// if the file is too small, it gets enlarged
// returns the number of bytes written
int binaryFileWrite(int fd, void* item, int item_size, int pos);  // tbd

// writes a record of size item_size in position pos in the file
// if the file is too small, it gets enlarged
// returns the number of bytes read or a negative number
// if error
int binaryFileRead(int fd, void* item, int item_size, int pos);   // tbd
