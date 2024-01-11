#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <assembler_generator.hpp>
#include <conditional_branch_manager.hpp>
#include <cstdint>
#include <loop_manager.hpp>
#include <procedure_manager.hpp>
#include <string>
#include <value.hpp>

class Compiler {
   private:
    LoopManager loopManager;
    AssemblerGenerator asmGenerator;
    ConditionalBranchManager branchManager;
    ProcedureManager procManager;

   public:
    Compiler() {
        std::string startLbael = asmGenerator.startProgram();
        procManager.getMainProcedure().setStartLabel(startLbael);
    }
    ~Compiler() = default;
    Compiler(const Compiler& from) = default;
    Compiler& operator=(const Compiler& from) = default;
    Compiler(Compiler&&) = default;
    Compiler& operator=(Compiler&&) = default;

    VariableManager& getVarManager() {
        return procManager.getCurrentProcedure().getVarManager();
    }
    LoopManager& getLoopManager() { return loopManager; }
    AssemblerGenerator& getAsmGenerator() { return asmGenerator; }
    ConditionalBranchManager& getBranchManager() { return branchManager; }
    ProcedureManager& getProcManager() { return procManager; }

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