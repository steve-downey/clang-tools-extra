//===--- ConstRefBuiltinCheck.cpp - clang-tidy-----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ConstRefBuiltinCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ConstRefBuiltinCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      parmVarDecl(hasType(references(
                      qualType(isConstQualified()).bind("referenced_type"))),
                  hasType(references(builtinType())))
          .bind("param"),
      this);
}

void ConstRefBuiltinCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Parameter = Result.Nodes.getNodeAs<ParmVarDecl>("param");
  const auto *Function =
      dyn_cast_or_null<FunctionDecl>(Parameter->getParentFunctionOrMethod());
  auto ReferencedType = *Result.Nodes.getNodeAs<QualType>("referenced_type");
  ReferencedType.removeLocalConst();
  if (Parameter->getName().empty()) {
    diag(Parameter->getLocation(),
         "const reference to %0 type at index '%1' in function '%2'")
      << ReferencedType
      << Parameter->getFunctionScopeIndex()
      << Function->getName();
  } else {
    diag(Parameter->getLocation(),
         "const reference to %0 at parameter '%1' in function '%2'")
      << ReferencedType
      << Parameter->getName()
      << Function->getName();
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
