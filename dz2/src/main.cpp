#include <iostream>
#include <memory>

#include "Addition.hpp"
#include "Brackets.hpp"
#include "Ceil.hpp"
#include "ICalculatable.hpp"
#include "ICalculatableBinary.hpp"
#include "ICalculatableUnary.hpp"
#include "Multiplication.hpp"
#include "Number.hpp"
#include "Parse.hpp"
#include "SqRoot.hpp"
#include "Substraction.hpp"
int main() {
  std::string a("3-2");
  std::unique_ptr<ICalculatable> res = ParseInput(a);
  std::cout << res->Calculate();
  return 0;
}
