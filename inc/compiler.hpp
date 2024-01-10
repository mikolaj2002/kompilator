#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <assembler_generator.hpp>
#include <conditional_branch_manager.hpp>
#include <cstdint>
#include <loop_manager.hpp>
#include <procedure.hpp>
#include <string>
#include <value.hpp>
#include <variable_manager.hpp>

class Compiler {
 private:
  VariableManager varManager;
  LoopManager loopManager;
  AssemblerGenerator asmGenerator;
  ConditionalBranchManager branchManager;
  std::vector<Procedure> procedures;

 public:
  VariableManager& getVarManager() { return varManager; }
  LoopManager& getLoopManager() { return loopManager; }
  AssemblerGenerator& getAsmGenerator() { return asmGenerator; }
  ConditionalBranchManager& getBranchManager() { return branchManager; }
  void addProcurure(const Procedure& procedure) {
    procedures.push_back(procedure);
  }

  void error(const char* fmt, ...);

  void assertDeclaration(const std::string& name, uint64_t line);
  void assertRedeclaration(const std::string& name, uint64_t line);
  void assertUsage(const std::string& name, Value::valtype_t type,
                   uint64_t line);
  void assertInitalization(Value* val, uint64_t line);
  void assertMutuable(Value* val, uint64_t line);

  void initVariable(Value* val);
};

#endif  // COMPILER_HPP