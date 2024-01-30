#include <bits/stdc++.h>

#include <assembler_generator.hpp>
#include <bitset>
#include <lvalue.hpp>
#include <lvalue_array.hpp>
#include <lvalue_pointer_arr.hpp>
#include <lvalue_pointer_var.hpp>
#include <lvalue_var.hpp>
#include <rvalue.hpp>

AssemblerGenerator::LabelManager::LabelManager(AssemblerGenerator* asmGenerator)
    : asmGenerator{asmGenerator}, labelCounter{1} {}

std::string AssemblerGenerator::LabelManager::createLabel(
    const std::string& name) {
    return name + "_" + std::to_string(labelCounter++);
}

std::string AssemblerGenerator::LabelManager::createLabel() {
    return createLabel("LABEL");
}

void AssemblerGenerator::LabelManager::insertLabel(const std::string& label) {
    uint64_t labelLine = asmGenerator->getCurrentAsmLine();

    auto lab = labels.find(label);
    if (lab == labels.end())
        labels[label] = std::make_pair(labelLine, std::vector<uint64_t>());
    else
        lab->second.first = labelLine;
}

void AssemblerGenerator::LabelManager::jumpToLabel(const std::string& jumpCode,
                                                   const std::string& label) {
    asmGenerator->addCode(jumpCode);

    uint64_t jumpLine = asmGenerator->getCurrentAsmLine();
    auto lab = labels.find(label);

    if (lab == labels.end())
        labels[label] = std::make_pair(0, std::vector<uint64_t>{jumpLine});
    else
        lab->second.second.push_back(jumpLine);
}

void AssemblerGenerator::LabelManager::generateCodeFromLabels() {
    for (auto& label : labels) {
        uint64_t jumpTo = label.second.first;
        auto& jumpFromVector = label.second.second;
        for (auto& jumpFrom : jumpFromVector) {
            asmGenerator->code[jumpFrom - 1] += " " + std::to_string(jumpTo);
        }
        jumpFromVector.clear();
    }
}

AssemblerGenerator::AssemblerGenerator()
    : labelManager{AssemblerGenerator::LabelManager(this)} {}

void AssemblerGenerator::addCode(const std::string& line) {
    code.push_back(line);
}

size_t AssemblerGenerator::getCurrentAsmLine() const { return code.size(); }

void AssemblerGenerator::asmRead() { addCode("READ"); }

void AssemblerGenerator::asmWrite() { addCode("WRITE"); }

void AssemblerGenerator::asmLoad(const Register& x) {
    addCode("LOAD " + x.getName());
}

void AssemblerGenerator::asmStore(const Register& x) {
    addCode("STORE " + x.getName());
}

void AssemblerGenerator::asmAdd(const Register& x) {
    addCode("ADD " + x.getName());
}

void AssemblerGenerator::asmSub(const Register& x) {
    addCode("SUB " + x.getName());
}

void AssemblerGenerator::asmGet(const Register& x) {
    addCode("GET " + x.getName());
}

void AssemblerGenerator::asmPut(const Register& x) {
    addCode("PUT " + x.getName());
}

void AssemblerGenerator::asmRst(const Register& x) {
    addCode("RST " + x.getName());
}

void AssemblerGenerator::asmInc(const Register& x) {
    addCode("INC " + x.getName());
}

void AssemblerGenerator::asmDec(const Register& x) {
    addCode("DEC " + x.getName());
}

void AssemblerGenerator::asmShl(const Register& x) {
    addCode("SHL " + x.getName());
}

void AssemblerGenerator::asmShr(const Register& x) {
    addCode("SHR " + x.getName());
}

void AssemblerGenerator::asmJump(uint64_t target) {
    addCode("JUMP " + std::to_string(target));
}

void AssemblerGenerator::asmJPos(uint64_t target) {
    addCode("JPOS " + std::to_string(target));
}

void AssemblerGenerator::asmJZero(uint32_t target) {
    addCode("JZERO " + std::to_string(target));
}

void AssemblerGenerator::asmStrk(const Register& x) {
    addCode("STRK " + x.getName());
}

void AssemblerGenerator::asmJumpR(const Register& x) {
    addCode("JUMPR " + x.getName());
}

void AssemblerGenerator::asmJumpLabel(const std::string& label) {
    labelManager.jumpToLabel("JUMP", label);
}

void AssemblerGenerator::asmJPosLabel(const std::string& label) {
    labelManager.jumpToLabel("JPOS", label);
}

void AssemblerGenerator::asmJZeroLabel(const std::string& label) {
    labelManager.jumpToLabel("JZERO", label);
}

void AssemblerGenerator::asmHalt() { addCode("HALT"); }

void AssemblerGenerator::moveRvalueToReg(const Register& x, uint64_t val) {
    std::bitset<sizeof(val) * CHAR_BIT> bits(val);

    size_t i;
    for (i = bits.size() - 1; i > 0; --i)
        if (bits[i]) break;

    asmRst(x);
    for (; i > 0; --i)
        if (bits[i]) {
            asmInc(x);
            asmShl(x);
        } else {
            asmShl(x);
        }

    if (bits[i]) asmInc(x);
}

void AssemblerGenerator::moveAddrToReg(const Register& x, const Lvalue& var) {
    moveRvalueToReg(x, dynamic_cast<const Lvalue&>(var).getAddr());

    if (var.getType() == Value::VALTYPE_LVALUE_ARRAY ||
        var.getType() == Value::VALTYPE_POINTER_ARRAY) {
        Register& temp = Architecture::getFreeRegister();
        temp.lock();
        Register& temp2 = Architecture::getFreeRegister();
        Register& retVal = Architecture::getRetValRegister();

        const Value* accessElement;
        if (var.getType() == Value::VALTYPE_LVALUE_ARRAY) {
            const LvalueArray& arr = dynamic_cast<const LvalueArray&>(var);
            accessElement = arr.getAccessElement();
        } else {
            if (!retVal.isFree() && x.getName() != retVal.getName()) {
                temp2.lock();
                asmPut(temp2);
            }
            asmLoad(x);
            if (x.getName() != retVal.getName()) asmPut(x);
            if (!retVal.isFree() && x.getName() != retVal.getName()) {
                asmGet(temp2);
                temp2.unlock();
            }

            const LvaluePointerArray& arr =
                dynamic_cast<const LvaluePointerArray&>(var);
            accessElement = arr.getAccessElement();
        }

        if (accessElement->getType() == Value::VALTYPE_RVALUE)
            moveRvalueToReg(
                temp, dynamic_cast<const Rvalue*>(accessElement)->getValue());
        else {
            moveRvalueToReg(
                temp, dynamic_cast<const Lvalue*>(accessElement)->getAddr());

            if (!retVal.isFree() || x.getName() == retVal.getName()) {
                temp2.lock();
                asmPut(temp2);
            }
            asmLoad(temp);
            if (accessElement->getType() == Value::VALTYPE_POINTER_VAR) {
                asmLoad(retVal);
            }
            asmPut(temp);
            if (!retVal.isFree() || x.getName() == retVal.getName()) {
                asmGet(temp2);
                temp2.unlock();
            }
        }

        if (!retVal.isFree() && x.getName() != retVal.getName()) {
            temp2.lock();
            asmPut(temp2);
        }
        if (x.getName() != retVal.getName()) asmGet(x);
        asmAdd(temp);
        if (x.getName() != retVal.getName()) asmPut(x);
        if (!retVal.isFree() && x.getName() != retVal.getName()) {
            asmGet(temp2);
            temp2.unlock();
        }

        temp.unlock();
    }
}

std::string AssemblerGenerator::startProgram() {
    std::string startLabel = labelManager.createLabel("main");
    asmJumpLabel(startLabel);
    return startLabel;
}

void AssemblerGenerator::load(const Register& x, const Value& val) {
    if (val.getType() == Value::VALTYPE_RVALUE)
        moveRvalueToReg(x, dynamic_cast<const Rvalue&>(val).getValue());
    else {
        if (val.getType() == Value::VALTYPE_POINTER_VAR ||
            val.getType() == Value::VALTYPE_POINTER_ARRAY)
            loadPointer(x, dynamic_cast<const LvaluePointer&>(val));
        else
            moveAddrToReg(x, dynamic_cast<const Lvalue&>(val));

        Register& retVal = Architecture::getRetValRegister();
        Register& temp = Architecture::getFreeRegister();
        if (!retVal.isFree() && x.getName() != retVal.getName()) {
            temp.lock();
            asmPut(temp);
        }
        asmLoad(x);
        if (x.getName() != retVal.getName()) asmPut(x);
        if (!retVal.isFree() && x.getName() != retVal.getName()) {
            asmGet(temp);
            temp.unlock();
        }
    }
}

void AssemblerGenerator::store(const Lvalue& var, const Register& x) {
    Register& temp = Architecture::getFreeRegister();
    temp.lock();
    Register& temp2 = Architecture::getFreeRegister();
    Register& retVal = Architecture::getRetValRegister();

    if (var.getType() == Value::VALTYPE_POINTER_VAR ||
        var.getType() == Value::VALTYPE_POINTER_ARRAY) {
        loadPointer(temp, dynamic_cast<const LvaluePointer&>(var));
    } else
        moveAddrToReg(temp, var);

    if (!retVal.isFree() && x.getName() != retVal.getName()) {
        temp2.lock();
        asmPut(temp2);
    }
    if (x.getName() != retVal.getName()) asmGet(x);
    asmStore(temp);
    if (!retVal.isFree() && x.getName() != retVal.getName()) {
        asmGet(temp2);
        temp2.unlock();
    }

    temp.unlock();
}

void AssemblerGenerator::loadPointer(const Register& x,
                                     const LvaluePointer& val) {
    moveAddrToReg(x, val);
    Register& retVal = Architecture::getRetValRegister();
    Register& temp = Architecture::getFreeRegister();
    if (val.getType() == Value::VALTYPE_POINTER_VAR) {
        if (!retVal.isFree() && x.getName() != retVal.getName()) {
            temp.lock();
            asmPut(temp);
        }
        asmLoad(x);
        if (x.getName() != retVal.getName()) asmPut(x);
        if (!retVal.isFree() && x.getName() != retVal.getName()) {
            asmGet(temp);
            temp.unlock();
        }
    }
}

void AssemblerGenerator::storePointer(const LvaluePointer& var,
                                      const Register& x) {
    Register& temp = Architecture::getFreeRegister();
    temp.lock();
    Register& temp2 = Architecture::getFreeRegister();
    Register& retVal = Architecture::getRetValRegister();

    moveRvalueToReg(temp, var.getAddr());

    if (!retVal.isFree() && x.getName() != retVal.getName()) {
        temp2.lock();
        asmPut(temp2);
    }
    if (x.getName() != retVal.getName()) asmGet(x);
    asmStore(temp);
    if (!retVal.isFree() && x.getName() != retVal.getName()) {
        asmGet(temp2);
        temp2.unlock();
    }

    temp.unlock();
}

void AssemblerGenerator::read(const Lvalue& var) {
    asmRead();
    Architecture::getRetValRegister().lock();
    store(var, Architecture::getRetValRegister());
    Architecture::getRetValRegister().unlock();
}

void AssemblerGenerator::write(const Value& val) {
    if (val.getType() == Value::VALTYPE_RVALUE)
        moveRvalueToReg(Architecture::getRetValRegister(),
                        dynamic_cast<const Rvalue&>(val).getValue());
    else
        load(Architecture::getRetValRegister(),
             dynamic_cast<const Lvalue&>(val));

    asmWrite();
}

void AssemblerGenerator::add(const Value& val1, const Value& val2) {
    Register& temp = Architecture::getFreeRegister();
    temp.lock();
    if (val1.getType() == Value::VALTYPE_RVALUE)
        moveRvalueToReg(temp, dynamic_cast<const Rvalue&>(val1).getValue());
    else
        load(temp, dynamic_cast<const Lvalue&>(val1));

    Register& retVal = Architecture::getRetValRegister();
    retVal.lock();
    if (val2.getType() == Value::VALTYPE_RVALUE)
        moveRvalueToReg(retVal, dynamic_cast<const Rvalue&>(val2).getValue());
    else
        load(retVal, dynamic_cast<const Lvalue&>(val2));

    asmAdd(temp);
    temp.unlock();
}

void AssemblerGenerator::sub(const Value& val1, const Value& val2) {
    Register& temp = Architecture::getFreeRegister();
    temp.lock();
    if (val1.getType() == Value::VALTYPE_RVALUE)
        moveRvalueToReg(temp, dynamic_cast<const Rvalue&>(val1).getValue());
    else
        load(temp, dynamic_cast<const Lvalue&>(val1));

    Register& retVal = Architecture::getRetValRegister();
    retVal.lock();
    if (val2.getType() == Value::VALTYPE_RVALUE)
        moveRvalueToReg(retVal, dynamic_cast<const Rvalue&>(val2).getValue());
    else
        load(retVal, dynamic_cast<const Lvalue&>(val2));

    asmSub(temp);
    temp.unlock();
}

void AssemblerGenerator::mul(const Value& val1, const Value& val2) {
    Register& retval = Architecture::getRetValRegister();
    retval.lock();

    Register& temp1 = Architecture::getFreeRegister();
    temp1.lock();
    load(temp1, val1);

    Register& temp2 = Architecture::getFreeRegister();
    temp2.lock();
    load(temp2, val2);

    Register& isOddReg = Architecture::getFreeRegister();
    isOddReg.lock();

    Register& result = Architecture::getFreeRegister();
    result.lock();
    asmRst(result);

    const std::string labelEnd = labelManager.createLabel("MUL_END");
    const std::string labelLoop = labelManager.createLabel("MUL_LOOP");
    const std::string labelInsideLoop =
        labelManager.createLabel("MUL_INSIDE_LOOP");
    const std::string labelOdd = labelManager.createLabel("MUL_ODD");

    asmGet(temp1);
    asmJZeroLabel(labelEnd);

    labelManager.insertLabel(labelLoop);
    asmGet(temp2);
    asmJZeroLabel(labelEnd);
    asmPut(isOddReg);
    asmShr(isOddReg);
    asmShl(isOddReg);
    asmSub(isOddReg);
    asmJPosLabel(labelOdd);
    labelManager.insertLabel(labelInsideLoop);
    asmShl(temp1);
    asmShr(temp2);
    asmJumpLabel(labelLoop);

    labelManager.insertLabel(labelOdd);
    asmGet(result);
    asmAdd(temp1);
    asmPut(result);
    asmJumpLabel(labelInsideLoop);

    temp1.unlock();
    temp2.unlock();
    isOddReg.unlock();
    result.unlock();

    labelManager.insertLabel(labelEnd);
    asmGet(result);
}

void AssemblerGenerator::div(const Value& val1, const Value& val2) {
    Register& temp1 = Architecture::getFreeRegister();
    temp1.lock();
    load(temp1, val1);

    Register& temp2 = Architecture::getFreeRegister();
    temp2.lock();
    load(temp2, val2);

    asmGet(temp1);

    Register& cloneVal1 = Architecture::getFreeRegister();
    cloneVal1.lock();
    asmPut(cloneVal1);

    Register& temp3 = Architecture::getFreeRegister();
    temp3.lock();
    asmPut(temp3);

    asmGet(temp2);

    Register& temp4 = Architecture::getFreeRegister();
    temp4.lock();
    asmPut(temp4);

    Register& cloneVal2 = Architecture::getFreeRegister();
    cloneVal2.lock();
    asmPut(cloneVal2);

    Register& retval = Architecture::getRetValRegister();
    retval.lock();

    const std::string label_end = labelManager.createLabel("DIV_END");
    const std::string label_ret0 = labelManager.createLabel("DIV_RETURN_0");
    const std::string label_ret1 = labelManager.createLabel("DIV_RETURN_1");
    const std::string label_start_algo =
        labelManager.createLabel("DIV_START_ALGO");

    asmGet(temp1);
    asmJZeroLabel(label_ret0);
    asmGet(temp2);
    asmJZeroLabel(label_ret0);

    asmGet(temp1);
    asmSub(temp2);
    asmPut(temp1);
    asmGet(temp2);
    asmSub(temp3);
    asmPut(temp2);
    asmGet(temp1);
    asmAdd(temp2);
    asmPut(temp1);
    asmJZeroLabel(label_ret1);

    asmGet(temp3);
    asmSub(temp4);
    asmJZeroLabel(label_ret0);
    asmJumpLabel(label_start_algo);

    labelManager.insertLabel(label_ret0);
    asmRst(temp4);
    asmJumpLabel(label_end);
    labelManager.insertLabel(label_ret1);
    asmRst(temp4);
    asmInc(temp4);
    asmJumpLabel(label_end);

    const std::string label_count_0 = labelManager.createLabel("DIV_COUNT_0");
    const std::string label_reload_b = labelManager.createLabel("DIV_RELOAD_B");
    const std::string label_add_0 = labelManager.createLabel("DIV_ADD_0");
    const std::string label_finish_add_0 =
        labelManager.createLabel("DIV_FINISH_ADD_0");
    const std::string label_loop = labelManager.createLabel("DIV_COUNT_LOOP");
    const std::string label_b_gt = labelManager.createLabel("DIV_B_IS_GREATER");

    labelManager.insertLabel(label_start_algo);
    asmGet(cloneVal1);
    asmPut(temp1);
    asmGet(cloneVal2);
    asmPut(temp2);

    moveRvalueToReg(temp4, 0);
    moveRvalueToReg(temp3, 1);

    labelManager.insertLabel(label_count_0);
    asmGet(temp2);
    asmJZeroLabel(label_reload_b);
    asmShr(temp2);
    asmShr(temp1);
    asmJumpLabel(label_count_0);

    labelManager.insertLabel(label_reload_b);
    asmGet(cloneVal2);
    asmPut(temp2);

    labelManager.insertLabel(label_add_0);
    asmGet(temp1);
    asmJZeroLabel(label_finish_add_0);
    asmShr(temp1);
    asmShl(temp2);
    asmInc(temp3);
    asmJumpLabel(label_add_0);

    labelManager.insertLabel(label_finish_add_0);
    asmGet(cloneVal1);
    asmPut(temp1);

    labelManager.insertLabel(label_loop);
    asmGet(temp3);
    asmJZeroLabel(label_end);
    asmInc(temp1);
    asmGet(temp1);
    asmSub(temp2);
    asmPut(temp1);
    asmJZeroLabel(label_b_gt);
    asmDec(temp1);
    asmDec(temp3);
    asmShl(temp4);
    asmInc(temp4);
    asmShr(temp2);

    asmGet(temp1);
    asmPut(cloneVal1);
    asmJumpLabel(label_loop);

    labelManager.insertLabel(label_b_gt);
    asmGet(cloneVal1);
    asmPut(temp1);
    asmShl(temp4);
    asmDec(temp3);
    asmShr(temp2);
    asmJumpLabel(label_loop);

    labelManager.insertLabel(label_end);
    asmGet(temp4);

    temp1.unlock();
    temp2.unlock();
    temp3.unlock();
    temp4.unlock();
    cloneVal1.unlock();
    cloneVal2.unlock();
}

void AssemblerGenerator::mod(const Value& val1, const Value& val2) {
    Register& temp1 = Architecture::getFreeRegister();
    temp1.lock();
    load(temp1, val1);

    Register& temp2 = Architecture::getFreeRegister();
    temp2.lock();
    load(temp2, val2);

    asmGet(temp1);

    Register& cloneVal1 = Architecture::getFreeRegister();
    cloneVal1.lock();
    asmPut(cloneVal1);

    Register& temp3 = Architecture::getFreeRegister();
    temp3.lock();
    asmPut(temp3);

    asmGet(temp2);

    Register& cloneVal2 = Architecture::getFreeRegister();
    cloneVal2.lock();
    asmPut(cloneVal2);

    Register& temp4 = Architecture::getFreeRegister();
    temp4.lock();
    asmPut(temp4);

    Register& retval = Architecture::getRetValRegister();
    retval.lock();

    const std::string label_end = labelManager.createLabel("MOD_END");
    const std::string label_ret0 = labelManager.createLabel("MOD_RETURN_0");
    const std::string label_reta = labelManager.createLabel("MOD_RETURN_a");
    const std::string label_start_algo =
        labelManager.createLabel("MOD_START_ALGO");

    asmGet(temp1);
    asmJZeroLabel(label_ret0);
    asmGet(temp2);
    asmJZeroLabel(label_ret0);

    asmGet(temp1);
    asmSub(temp2);
    asmPut(temp1);
    asmGet(temp2);
    asmSub(temp3);
    asmPut(temp2);
    asmGet(temp1);
    asmAdd(temp2);
    asmPut(temp1);
    asmJZeroLabel(label_ret0);

    asmGet(temp3);
    asmSub(temp4);
    asmJZeroLabel(label_reta);
    asmJumpLabel(label_start_algo);

    labelManager.insertLabel(label_ret0);
    asmRst(temp4);
    asmJumpLabel(label_end);
    labelManager.insertLabel(label_reta);
    asmGet(cloneVal1);
    asmPut(temp4);
    asmJumpLabel(label_end);

    const std::string label_count_0 = labelManager.createLabel("MOD_COUNT_0");
    const std::string label_reload_b = labelManager.createLabel("MOD_RELOAD_B");
    const std::string label_add_0 = labelManager.createLabel("MOD_ADD_0");
    const std::string label_finish_add_0 =
        labelManager.createLabel("MOD_FINISH_ADD_0");
    const std::string label_loop = labelManager.createLabel("MOD_COUNT_LOOP");
    const std::string label_b_gt = labelManager.createLabel("MOD_B_IS_GREATER");

    labelManager.insertLabel(label_start_algo);
    asmGet(cloneVal1);
    asmPut(temp4);
    asmGet(cloneVal2);
    asmPut(temp2);

    moveRvalueToReg(temp1, 0);
    moveRvalueToReg(temp3, 1);

    labelManager.insertLabel(label_count_0);
    asmGet(temp2);
    asmJZeroLabel(label_reload_b);
    asmShr(temp2);
    asmShr(temp4);
    asmJumpLabel(label_count_0);

    labelManager.insertLabel(label_reload_b);
    asmGet(cloneVal2);
    asmPut(temp2);

    labelManager.insertLabel(label_add_0);
    asmGet(temp4);
    asmJZeroLabel(label_finish_add_0);
    asmShr(temp4);
    asmShl(temp2);
    asmInc(temp3);
    asmJumpLabel(label_add_0);

    labelManager.insertLabel(label_finish_add_0);
    asmGet(cloneVal1);
    asmPut(temp4);

    labelManager.insertLabel(label_loop);
    asmGet(temp3);
    asmJZeroLabel(label_end);
    asmInc(temp4);
    asmGet(temp4);
    asmSub(temp2);
    asmPut(temp4);
    asmJZeroLabel(label_b_gt);
    asmDec(temp4);
    asmDec(temp3);
    asmShl(temp1);
    asmInc(temp1);
    asmShr(temp2);

    asmGet(temp4);
    asmPut(cloneVal1);
    asmJumpLabel(label_loop);

    labelManager.insertLabel(label_b_gt);
    asmGet(cloneVal1);
    asmPut(temp4);
    asmShl(temp1);
    asmDec(temp3);
    asmShr(temp2);
    asmJumpLabel(label_loop);

    labelManager.insertLabel(label_end);
    asmGet(temp4);

    temp1.unlock();
    temp2.unlock();
    temp3.unlock();
    temp4.unlock();
    cloneVal1.unlock();
    cloneVal2.unlock();
}

ConditionalBranch AssemblerGenerator::branchEq(const Value& val1,
                                               const Value& val2) {
    const std::string labelTrue = labelManager.createLabel("COND_EQ_TRUE");
    const std::string labelFalse = labelManager.createLabel("COND_EQ_FALSE");

    Register& temp1 = Architecture::getFreeRegister();
    temp1.lock();

    Register& temp2 = Architecture::getFreeRegister();
    temp2.lock();

    load(temp1, val1);
    load(temp2, val2);

    asmGet(temp1);
    asmSub(temp2);
    asmJPosLabel(labelFalse);

    asmGet(temp2);
    asmSub(temp1);
    asmJPosLabel(labelFalse);

    labelManager.insertLabel(labelTrue);

    temp1.unlock();
    temp2.unlock();

    return ConditionalBranch(labelFalse);
}

ConditionalBranch AssemblerGenerator::branchNeq(const Value& val1,
                                                const Value& val2) {
    const std::string labelTrue = labelManager.createLabel("COND_NEQ_TRUE");
    const std::string labelFalse = labelManager.createLabel("COND_NEQ_FALSE");

    Register& temp1 = Architecture::getFreeRegister();
    temp1.lock();

    Register& temp2 = Architecture::getFreeRegister();
    temp2.lock();

    load(temp1, val1);
    load(temp2, val2);

    asmGet(temp1);
    asmSub(temp2);
    asmJPosLabel(labelTrue);

    asmGet(temp2);
    asmSub(temp1);
    asmJZeroLabel(labelFalse);

    labelManager.insertLabel(labelTrue);

    temp1.unlock();
    temp2.unlock();

    return ConditionalBranch(labelFalse);
}

ConditionalBranch AssemblerGenerator::branchGt(const Value& val1,
                                               const Value& val2) {
    const std::string labelTrue = labelManager.createLabel("COND_GT_TRUE");
    const std::string labelFalse = labelManager.createLabel("COND_GT_FALSE");

    Register& retVal = Architecture::getRetValRegister();

    Register& temp1 = Architecture::getFreeRegister();
    temp1.lock();

    load(temp1, val2);
    load(retVal, val1);

    asmSub(temp1);
    asmJPosLabel(labelTrue);
    asmJumpLabel(labelFalse);

    labelManager.insertLabel(labelTrue);

    temp1.unlock();

    return ConditionalBranch(labelFalse);
}

ConditionalBranch AssemblerGenerator::branchLt(const Value& val1,
                                               const Value& val2) {
    return branchGt(val2, val1);
}

ConditionalBranch AssemblerGenerator::branchGeq(const Value& val1,
                                                const Value& val2) {
    const std::string labelTrue = labelManager.createLabel("COND_GEQ_TRUE");
    const std::string labelFalse = labelManager.createLabel("COND_GEQ_FALSE");

    Register& retVal = Architecture::getRetValRegister();

    Register& temp1 = Architecture::getFreeRegister();
    temp1.lock();

    load(temp1, val1);
    load(retVal, val2);

    asmSub(temp1);
    asmJZeroLabel(labelTrue);
    asmJumpLabel(labelFalse);

    labelManager.insertLabel(labelTrue);

    temp1.unlock();

    return ConditionalBranch(labelFalse);
}

ConditionalBranch AssemblerGenerator::branchLeq(const Value& val1,
                                                const Value& val2) {
    return branchGeq(val2, val1);
}

void AssemblerGenerator::ifInsertJumpPoint(const ConditionalBranch& branch) {
    labelManager.insertLabel(branch.getLabelFalse());
}

void AssemblerGenerator::ifSkipElse(const ConditionalBranch& branch) {
    asmJumpLabel(branch.getLabelFalse());
}

void AssemblerGenerator::startWhileLoop(const LoopWhile& loop) {
    labelManager.insertLabel(loop.getStartLabel());
}

void AssemblerGenerator::doWhileLoop(const LoopWhile& loop) {
    asmJumpLabel(loop.getStartLabel());
    labelManager.insertLabel(loop.getEndLabel());
}

void AssemblerGenerator::startUntilLoop(const LoopUntil& loop) {
    labelManager.insertLabel(loop.getStartLabel());
}

void AssemblerGenerator::doUntilLoop(const LoopUntil& loop) {
    const std::string labelEnd = labelManager.createLabel("UNTIL_END");
    asmJumpLabel(labelEnd);

    labelManager.insertLabel(loop.getEndLabel());
    asmJumpLabel(loop.getStartLabel());

    labelManager.insertLabel(labelEnd);
}

void AssemblerGenerator::createProcedure(Procedure& proc) {
    labelManager.insertLabel(proc.getStartLabel());
    if (!proc.isMainProcedure()) {
        asmInc(Architecture::getRetValRegister());
        asmInc(Architecture::getRetValRegister());
        store(*(proc.getReturnLine()), Architecture::getRetValRegister());
    }
}

void AssemblerGenerator::endProcedure(Procedure& proc) {
    load(Architecture::getRetValRegister(), *(proc.getReturnLine()));
    asmJumpR(Architecture::getRetValRegister());
}

void AssemblerGenerator::callProcedure(Procedure& proc) {
    asmStrk(Architecture::getRetValRegister());
    asmJumpLabel(proc.getStartLabel());
}

void AssemblerGenerator::finishProgram() { asmHalt(); }

void AssemblerGenerator::finishCodeGeneration() {
    labelManager.generateCodeFromLabels();
}

std::string AssemblerGenerator::getGeneratedCode() const {
    std::string result = "";
    for (auto const& line : code) result += line + '\n';
    return result;
}