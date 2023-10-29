#include <bitset>

typedef std::bitset<1000> type_element;

class UtiliyFunc
{
public:
  type_element set_current;
  int val = 0;
  int set_size = 0;
  int count_eval = 0;

  UtiliyFunc(){};

  UtiliyFunc(const UtiliyFunc& f){
    val = f.val;
    set_size = f.set_size;
    count_eval = f.count_eval;
    set_current = f.set_current;
  }

  int add_element(type_element element_new)
  {
    set_current |= element_new;
    set_size++;
    count_eval++;
    val = set_current.count();
    return val;
  }

  int marginal_gain(type_element element_new)
  {
    count_eval++;
    return (set_current | element_new).count() - val;
  }

  int singleton_value(type_element s) {return s.count(); } 

  int value() { return val; }
  
  int size() { return set_size; }

  int num_eval() { return count_eval; }
};
