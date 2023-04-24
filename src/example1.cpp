#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;

class MyPrinter : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("function"))
      FD->dump();
  }
};

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv);
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
  MatchFinder Finder;
  MyPrinter Printer;
  Finder.addMatcher(functionDecl(hasName("f")).bind("function"), &Printer);
  return Tool.run(newFrontendActionFactory(&Finder).get());
}