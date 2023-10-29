#include <bitset>

typedef std::bitset<1000> type_element;

class UtiliyFunc
{
public:
  type_element set_currnet;
  int val = 0;
  int set_size = 0;
  int count_eval = 0;

  UtiliyFunc(){};

  int add_element(type_element element_new)
  {
    set_currnet |= element_new;
    set_size++;
    count_eval++;
    val = set_currnet.count();
    return val;
  }

  int marginal_gain(type_element element_new)
  {
    count_eval++;
    return (set_currnet | element_new).count() - val;
  }

  int singleton_value(type_element s) {return s.count(); } 

  int value() { return val; }
  
  int size() { return set_size; }

  int num_eval() { return count_eval; }
};
