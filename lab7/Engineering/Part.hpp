#ifndef PART_HPP
#define PART_HPP

class Part {
public:
  Part();

  Part(const Part &part);

  explicit Part(const char *name_, double partMass_ = 0.0);

  virtual ~Part();

  void dllAdd();

  void dllRemove();

  virtual void show() const;

  static void showList();

protected:
  char *name;
  double partMass;
  Part *prev, *next;

  void setName(const char *name_);

  static Part *dllTop;
};

#endif
