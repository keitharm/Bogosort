#include "bogo.h"

int main(int argc, char *argv[]) {
  hideCursor();

  // Seed RNG
  struct timeval time; 
  gettimeofday(&time,NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

  // File checks
  if (argc == 1) {
    cout << RED << "Error:\t" << WHITE << "No list file supplied!" << WHITE << endl;
    return 1;
  }

  if (!file_exists(argv[1])) {
    cout << RED << "Error:\t" << WHITE << "File " << WHITE << CYAN << argv[1] << WHITE << " is invalid." << endl;
    return 2;
  }

  // Read in file if it is ok
  ifstream is(argv[1]);
  istream_iterator<int> start(is), end;
  vector<int> numbers(start, end);

  // Sort the array like a normal useful sort so we can compare to bogosort
  vector<int> sorted = sortNums(numbers);

  // Output how many numbers to sort
  cout << "Read " << BLUE << comma(numbers.size()) << WHITE << " numbers" << endl;

  // init stats
  long attempts = 0;
  long avg = 0;
  int diff = 0;
  int prev = 0;
  string s = "";

  // init avg
  time_t started = std::time(0);
  time_t current = started;

  // BOGO SORT!!!
  while (!equal(numbers, sorted)) {
    current = std::time(0);  // Fetch current time for avg stats
    swap(numbers);           // Perform swap
    attempts++;
    diff = current-started;  // Get elapsed time

    // Only start showing status after 1st second and then every second after
    if (diff >= 1 && diff != prev) {
      prev = diff;
      avg = attempts/(diff);
      clearScreen();
      displayList(numbers, sorted);

      cout << endl << "Total attempts:\t\t" << YELLOW << comma(attempts) << WHITE << endl;
      cout << "Swaps per second:\t" << CYAN << comma(avg) << WHITE << endl;
      s = diff == 1 ? "" : "s";
      cout << "Time elapsed:\t\t" << GREEN << comma(diff) << WHITE << " second" << s << endl;
    }
  }
  cout << endl << "Sorted list: ";
  displayList(numbers, sorted);
  cout << endl << endl << "Done! Took a total of " << YELLOW << comma(attempts) << WHITE << " attempts and " << GREEN << comma(diff) << WHITE << " seconds at " << CYAN << comma(avg) << WHITE << " swaps per second to sort " << BLUE << comma(numbers.size()) << WHITE << " numbers!" << endl;

  showCursor();
  return 0;
}

bool file_exists(const string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

void swap(vector<int> &nums) {
  int a = randInt(0, nums.size());
  int b = randInt(0, nums.size());
  int tmp = nums[a];
  nums[a] = nums[b];
  nums[b] = tmp;
}

bool equal(vector<int> &a, vector<int> &b) {
  return a == b;
}

int randInt(int min, int max) {
  return rand() % max + min;
}

bool comp(int i,int j) {
  return (i<j);
}

vector<int> sortNums(vector<int> original) {
  sort(original.begin(), original.end(), comp);

  return original;
}

string comma(long value) {
  string numWithCommas = to_string(value);
  long insertPosition = numWithCommas.length() - 3;
  while (insertPosition > 0) {
    numWithCommas.insert(insertPosition, ",");
    insertPosition-=3;
  }
  return numWithCommas;
}

void hideCursor() {
  cout << "\033[?25l";
}

void showCursor() {
  cout << "\033[?25h";
}

void clearScreen() {
  cout << "\033[2J\033[H";
}

void displayList(vector<int> &actual, vector<int> &expected) {
  int a = 0;
  for (vector<int>::iterator it=actual.begin(); it!=actual.end(); ++it) {
    if (actual[a] == expected[a]) {
      cout << GREEN << *it << WHITE << ' ';
    } else {
      cout << RED << *it << WHITE << ' ';
    }
    ++a;
  }
}
