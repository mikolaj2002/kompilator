#ifndef ASSERMBLER_GENERATOR_HPP
#define ASSERMBLER_GENERATOR_HPP

#include <conditional_branch.hpp>
#include <cstdint>
#include <loop_until.hpp>
#include <loop_while.hpp>
#include <lvalue.hpp>
#include <lvalue_pointer.hpp>
#include <map>
#include <procedure.hpp>
#include <register.hpp>
#include <string>
#include <value.hpp>
#include <vector>

class AssemblerGenerator {
   public:
    class LabelManager {
       private:
        AssemblerGenerator* asmGenerator;
        std::map<std::string, std::pair<uint64_t, std::vector<uint64_t>>>
            labels;
        uint64_t labelCounter;

       public:
        LabelManager(AssemblerGenerator* asmGenerator);
        std::string createLabel(const std::string& name);
        std::string createLabel();
        void insertLabel(const std::string& label);
        void jumpToLabel(const std::string& jumpCode, const std::string& label);
        void generateCodeFromLabels();
    };

    friend class AssemblerGenerator::LabelManager;

   private:
    AssemblerGenerator::LabelManager labelManager;

    std::vector<std::string> code;
    void addCode(const std::string& line);
    size_t getCurrentAsmLine() const;

    void asmRead();
    void asmWrite();
    void asmLoad(const Register& x);
    void asmStore(const Register& x);
    void asmAdd(const Register& x);
    void asmSub(const Register& x);
    void asmGet(const Register& x);
    void asmPut(const Register& x);
    void asmRst(const Register& x);
    void asmInc(const Register& x);
    void asmDec(const Register& x);
    void asmShl(const Register& x);
    void asmShr(const Register& x);
    void asmJump(uint64_t target);
    void asmJPos(uint64_t target);
    void asmJZero(uint32_t target);
    void asmStrk(const Register& x);
    void asmJumpR(const Register& x);
    void asmJumpLabel(const std::string& label);
    void asmJPosLabel(const std::string& label);
    void asmJZeroLabel(const std::string& label);
    void asmHalt();

    void moveRvalueToReg(const Register& x, uint64_t val);
    void moveAddrToReg(const Register& x, const Lvalue& var);

   public:
    AssemblerGenerator();
    virtual ~AssemblerGenerator() = default;
    AssemblerGenerator(const AssemblerGenerator& from) = default;
    AssemblerGenerator& operator=(const AssemblerGenerator& from) = default;
    AssemblerGenerator(AssemblerGenerator&&) = default;
    AssemblerGenerator& operator=(AssemblerGenerator&&) = default;

    std::string startProgram();

    void load(const Register& x, const Value& val);
    void store(const Lvalue& var, const Register& x);
    void loadPointer(const Register& x, const LvaluePointer& val);
    void storePointer(const LvaluePointer& var, const Register& x);

    void read(const Lvalue& var);
    void write(const Value& val);

    void add(const Value& val1, const Value& val2);
    void sub(const Value& val1, const Value& val2);
    void mul(const Value& val1, const Value& val2);
    void div(const Value& val1, const Value& val2);
    void mod(const Value& val1, const Value& val2);

    ConditionalBranch branchEq(const Value& val1, const Value& val2);
    ConditionalBranch branchNeq(const Value& val1, const Value& val2);
    ConditionalBranch branchGt(const Value& val1, const Value& val2);
    ConditionalBranch branchLt(const Value& val1, const Value& val2);
    ConditionalBranch branchGeq(const Value& val1, const Value& val2);
    ConditionalBranch branchLeq(const Value& val1, const Value& val2);

    void startWhileLoop(const LoopWhile& loop);
    void doWhileLoop(const LoopWhile& loop);

    void startUntilLoop(const LoopUntil& loop);
    void doUntilLoop(const LoopUntil& loop);

    void ifInsertJumpPoint(const ConditionalBranch& branch);
    void ifSkipElse(const ConditionalBranch& branch);

    void createProcedure(Procedure& proc);
    void endProcedure(Procedure& proc);
    void callProcedure(Procedure& proc);

    void finishProgram();

    void finishCodeGeneration();

    std::string getGeneratedCode() const;

    AssemblerGenerator::LabelManager& getLabelManager() {
        return labelManager;
    };
};

#endif  // ASSERMBLER_GENERATOR_HPP