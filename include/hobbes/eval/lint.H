#pragma once

#include <hobbes/reflect.H>
#include <hobbes/lang/expr.H>
#include <hobbes/lang/module.H>

#include <ostream>
#include <vector>

namespace hobbes {

DEFINE_ENUM(LintCode,
  (INFIX_AFTER_ELSE)
);

struct Suggestion {
  LintCode    code;
  const Expr* expr;
  const char* text;
};

class Linter {
public:
  bool run(const ExprPtr&);
  bool run(const ModulePtr&);
  void raise(const Suggestion&);
  void report(std::ostream& os) const;

private:
  std::vector<Suggestion> suggestions;
};

}

