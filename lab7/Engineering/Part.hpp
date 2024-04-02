#ifndef PART_HPP
#define PART_HPP

class Part {
public:
  Part();

  Part(const Part &part);

  Part(const char *name_, double mass_);

  virtual ~Part();

  void dllAdd();

  void dllRemove();

  virtual void show() const;

  static void showList();

protected:
  char *name;
  double mass;
  Part *prev, *next;

  void setName(const char *name_);

  static Part *dllTop;
};

#endif
