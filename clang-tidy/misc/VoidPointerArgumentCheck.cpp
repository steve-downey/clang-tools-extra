//===--- VoidPointerArgumentCheck.cpp - clang-tidy-------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "VoidPointerArgumentCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void VoidPointerArgumentCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(
      parmVarDecl(
          unless(isInstantiated()),
          hasType(pointsTo(voidType())))
          .bind("param"),
      this);
}

void VoidPointerArgumentCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *Parameter = Result.Nodes.getNodeAs<ParmVarDecl>("param");
  const auto *Function =
    dyn_cast_or_null<FunctionDecl>(Parameter->getParentFunctionOrMethod());

  diag(Function->getLocation(), "function '%0' has a void* argument")
    << Function->getName();;
}

} // namespace misc
} // namespace tidy
} // namespace clang
