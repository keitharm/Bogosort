#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <locale>
#include <sys/stat.h>
#include <sys/time.h>

using namespace std;

// Colors codes for friendly UI
#define WHITE  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"
#define PURPLE "\033[35m"
#define CYAN   "\033[36m"

bool file_exists(const string&);
void swap(vector<int>&);
int randInt(int, int);
bool comp(int, int);
vector<int> sortNums(vector<int>);
bool equal(vector<int>&, vector<int>&);
string comma(long);
void hideCursor();
void showCursor();
void clearScreen();
void displayList(vector<int>&, vector<int>&);