#include "clang/AST/AST.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include <iostream>

using namespace clang;
using namespace llvm;
using namespace clang::ast_matchers;
using namespace clang::tooling;

StatementMatcher Matcher = declRefExpr(to(functionDecl().bind("func")));

class FuncPrinter : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const FunctionDecl *FD =
            Result.Nodes.getNodeAs<FunctionDecl>("func")) {
      std::cout << "Function name: " << FD->getNameAsString() << "\n";
      std::cout << "Namespace: "
                << FD->getQualifiedNameAsString()
                << "\n";
    }
  }
};

// Set up the command line options
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::OptionCategory ToolTemplateCategory("tool-template options");

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, ToolTemplateCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  FuncPrinter Printer;
  MatchFinder Finder;
  Finder.addMatcher(Matcher, &Printer);
  return Tool.run(newFrontendActionFactory(&Finder).get());
}