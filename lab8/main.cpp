#include <algorithm>
#include <cctype>
#include <clocale>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void task1() {
  std::cout << "Задание 1" << std::endl;
  std::string str;
  std::getline(std::cin, str);
  const size_t firstLetterIdx = str.find_first_not_of(" ");
  str = str.substr(firstLetterIdx,
                   str.find_last_not_of(" ") + 1 - firstLetterIdx);
  const size_t lastSpaceIdx = str.find_last_of(" ");
  std::cout
      << "Индекс последнего пробела перед последним словом в исходной строке: "
      << firstLetterIdx + lastSpaceIdx << std::endl;
  std::swap(str[0], str[lastSpaceIdx + 1]);
  std::cout << str << std::endl;
}

void task2() {
  std::cout << "Задание 2" << std::endl;
  std::string str, digits;
  std::getline(std::cin, str);
  for (const char c : str) {
    if (std::isdigit(c)) {
      digits.push_back(c);
    }
  }
  std::cout << digits << std::endl;
}

void task3() {
  std::cout << "Задание 3" << std::endl;
  std::string str;
  std::ifstream inStream("in.txt");
  str.clear();
  while (!inStream.eof()) {
    if (!str.empty()) {
      str.append(" ");
    }
    std::string word;
    inStream >> word;
    str.append(word);
  }
  const std::string outFname = "out.txt";
  std::ofstream(outFname) << str;
  std::cout << "В файле " << outFname << std::endl;
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &pair) {
  out << pair.first << " - " << pair.second;
  return out;
}

template <class ContainerT, typename T = typename ContainerT::value_type>
void printContainer(const ContainerT &container, const std::string &sep = " ") {
  size_t i = 0;
  for (const T &el : container) {
    std::cout << el;
    if (i < container.size() - 1) {
      std::cout << sep;
    }
    ++i;
  }
  std::cout << std::endl;
}

void task4multiply(std::vector<int> &vec) {
  std::transform(vec.begin(), vec.end(), vec.begin(),
                 [](int n) { return n * 2; });
}

void task4() {
  std::cout << "Задание 4" << std::endl;
  std::vector<int> vec;
  for (size_t i = 0; i < 5; ++i) {
    vec.push_back(std::rand() % 20);
  }
  printContainer(vec);
  task4multiply(vec);
  printContainer(vec);
  vec.erase(vec.begin() + 2);
  printContainer(vec);
}

class Complex {
public:
  Complex() : a(0.0), b(0.0) {}

  Complex(double a_, double b_) : a(a_), b(b_) {}

  Complex operator+(const Complex &other) {
    return {this->a + other.a, this->b + other.b};
  }

  friend std::ostream &operator<<(std::ostream &out, const Complex &complex) {
    out << complex.a << " + i * " << complex.b;
    return out;
  }

private:
  double a, b;
};

void task5() {
  std::cout << "Задание 5" << std::endl;
  const std::vector<Complex> comps = {{-1.2, 6.3}, {4.0, 0.7},  {7.2, -0.8},
                                      {5.3, 3.0},  {-4.9, 6.6}, {-9.3, 0.2}};
  printContainer(comps, "\n");
  std::cout << "Сумма: "
            << std::accumulate(comps.begin(), comps.end(), Complex())
            << std::endl;
}

template <typename T>
void printList(const std::list<T> &list, const std::string &sep = " ") {
  typename std::list<T>::const_iterator iter = list.begin();
  for (size_t i = 0; i < list.size(); ++i) {
    std::cout << *iter;
    ++iter;
    if (i < list.size() - 1) {
      std::cout << sep;
    }
  }
  std::cout << std::endl;
}

void task6multiply(std::list<int> &list) {
  std::transform(list.begin(), list.end(), list.begin(),
                 [](int n) { return n * 2; });
}

void task6() {
  std::cout << "Задание 6" << std::endl;
  std::list<int> list;
  for (size_t i = 0; i < 5; ++i) {
    list.push_back(std::rand() % 20);
  }
  printContainer(list);
  task6multiply(list);
  printContainer(list);
  std::list<int>::iterator i = list.begin();
  std::advance(i, 2);
  list.erase(i);
  printContainer(list);
}

class Rectangle {
public:
  Rectangle() : a(0), b(0) {}

  Rectangle(double a_, double b_) : a(a_), b(b_) {}

  bool operator<(const Rectangle &other) {
    return this->a * this->b < other.a * other.b;
  }

  bool operator==(const Rectangle &other) {
    return this->a * this->b == other.a * other.b;
  }

  friend std::ostream &operator<<(std::ostream &out, const Rectangle &rect) {
    out << rect.a << " x " << rect.b;
    return out;
  }

private:
  double a, b;
};

void task7() {
  std::cout << "Задание 7" << std::endl;
  std::list<Rectangle> rects = {{1.2, 6.3}, {4.0, 0.7}, {7.2, 0.8},
                                {5.3, 3.0}, {4.9, 6.6}, {9.3, 0.2}};
  printContainer(rects, "\n");
  std::cout << "Наибольшая площадь: "
            << *std::max_element(rects.begin(), rects.end()) << std::endl;
}

void task8() {
  std::cout << "Задание 8" << std::endl;
  std::map<std::string, int> nums = {{"one", 100},   {"two", 200},
                                     {"three", 300}, {"four", 400},
                                     {"five", 500},  {"six", 600}};
  printContainer(nums, "\n");
  nums.erase("five");
  nums.erase("six");
  std::cout << "После удаления:" << std::endl;
  printContainer(nums, "\n");
}

void task9() {
  std::cout << "Задание 9" << std::endl;
  std::map<std::string, std::string> subs;
  while (true) {
    std::string str;
    std::getline(std::cin, str);
    if (str.empty()) {
      break;
    }
    std::stringstream sstream(str);
    std::string name, number;
    sstream >> name >> number;
    subs.insert({name, number});
  }
  std::cout << "Абоненты:" << std::endl;
  printContainer(subs, "\n");
  std::cout << "Введите имя абонента для удаления: ";
  std::string name;
  std::cin >> name;
  subs.erase(name);
  std::cout << "Абоненты после удаления:" << std::endl;
  printContainer(subs, "\n");
}

int main() {
  setlocale(LC_ALL, ".UTF8");
  srand(time(nullptr));
  task1();
  task2();
  task3();
  task4();
  task5();
  task6();
  task7();
  task8();
  task9();
  return 0;
}
