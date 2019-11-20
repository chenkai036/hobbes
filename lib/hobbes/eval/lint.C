#include <hobbes/eval/lint.H>

namespace hobbes {

template <typename StreamT>
StreamT& operator<<(StreamT& os, const Suggestion& s) {
  os << "lint: " << s.expr->la().lineDesc()
     << ": " << s.code.show()
     << ", " << s.text;
  return os;
}

/// lint rules

class CheckBracketF final : public switchExprTyFn, public switchMDefTyFn {
public:
  CheckBracketF(Linter& linter) : linter(linter) {}

  QualTypePtr withTy(const QualTypePtr& qt) const override {
    return qt;
  }

  /// Suggest explicit brackets to avoid ambiguity in else-expression
  /// if cond then expr-0 else expr-1 infix expr-2
  ///
  /// either `(if cond then expr-0 else expr-1) infix expr-2`
  /// or     `if cond then expr-0 else (expr-1 infix expr-2)`
  ExprPtr with(const App* v) const override {
    if (auto var = is<Var>(v->fn())) {
      if (var->value() == "if") {
        auto elseblock = v->args()[2];
        if (!isNestedExpr(elseblock) && isInfixExpr(elseblock)) {
          linter.raise(Suggestion{LintCode::Enum::INFIX_AFTER_ELSE, v, "use brackets in else-block to avoid ambiguity"});
        }
      }
    }
    return switchExprTyFn::with(v);
  }

  ModuleDefPtr with(const MVarDef* v) const override {
    switchOf(v->varExpr(), *this);
    return switchMDefTyFn::with(v);
  }

  ModuleDefPtr with(const InstanceDef* v) const override {
    for (const auto & member : v->members()) {
      switchOf(member, *this);
    }
    return switchMDefTyFn::with(v);
  }

private:
  static bool isNestedExpr(const ExprPtr& expr) {
    const auto & la = expr->la();
    return la.span.first < la.p0 && la.p1 < la.span.second;
  }

  static bool isInfixExpr(const ExprPtr& expr) {
    if (auto app = is<App>(expr)) {
      auto & args = app->args();
      if (args.size() == 2) {
        auto & op = app->fn();
        auto & left = args[0];
        auto & right = args[1];
        return left->la() < op->la() && op->la() < right->la();
      }
    }
    return false;
  }

  Linter& linter;
};

/// linter

void Linter::raise(const Suggestion& s) {
  suggestions.push_back(s);
}

void Linter::report(std::ostream& os) const {
  for (const auto & suggestion : suggestions) {
    os << suggestion << std::endl;
  }
}

bool Linter::run(const ExprPtr& expr) {
  suggestions.clear(); // TODO stack them, not clear them
  switchOf(expr, CheckBracketF(*this));
  return suggestions.empty();
}

bool Linter::run(const ModulePtr& module) {
  suggestions.clear(); // TODO stack them, not clear them
  for (const auto & mdef : module->definitions()) {
    switchOf(mdef, CheckBracketF(*this));
  }
  return suggestions.empty();
}

}

