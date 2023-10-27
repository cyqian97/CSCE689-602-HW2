#include <bitset>

typedef std::bitset<1000> type_set;

class UtiliyFunc
{
public:
  type_set set_currnet;
  int count_evaluate = 0;

  UtiliyFunc(){};

  int add_element(type_set element_new)
  {
    set_currnet |= element_new;
    return set_currnet.count();
  }

  int marginal_gain(type_set element_new)
  {
    count_evaluate++;
    return (set_currnet & element_new).count();
  }

  int value()
  {
    return set_currnet.count();
  }
};