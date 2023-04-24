add_llvm_executable(ns_filter ns_filter.cpp)

set_property(TARGET ns_filter PROPERTY CXX_STANDARD 17)
target_link_libraries(ns_filter PRIVATE 
LLVMCore
LLVMIRReader
LLVMSupport
clangFrontend
clangSerialization
clangDriver
clangParse
clangSema
clangAnalysis
clangAST
clangBasic
clangEdit
clangLex
clangTransformer
clangTooling)
