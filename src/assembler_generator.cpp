#include <bits/stdc++.h>

#include <assembler_generator.hpp>
#include <bitset>
#include <lvalue.hpp>
#include <lvalue_array.hpp>
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
  // insert_label was called before jumpToLabel, so there is no label. Add
  // label
  if (lab == labels.end())
    labels[label] = std::make_pair(labelLine, std::vector<uint64_t>());
  else  // someone set line as a jump point from to label, so now set only
        // jump point to as a label_line
    lab->second.first = labelLine;
}

void AssemblerGenerator::LabelManager::jumpToLabel(const std::string& jumpCode,
                                                   const std::string& label) {
  // jump_code is incomplete as JUMP or JZERO x or JODD y, but this is fine.
  // Add it to code and add jump from point to label
  asmGenerator->addCode(jumpCode);

  // jump code is here, so current line is our jump to point
  uint64_t jumpLine = asmGenerator->getCurrentAsmLine();
  auto lab = labels.find(label);

  // jumpToLabel was called before insert_label, so there is no label.
  // Add label with invalid label line, but add jump from point to vector
  if (lab == labels.end())
    labels[label] = std::make_pair(0, std::vector<uint64_t>{jumpLine});
  else  // there is a label here, so add another jump from point to vector
    lab->second.second.push_back(jumpLine);
}

void AssemblerGenerator::LabelManager::generateCodeFromLabels() {
  for (auto& label : labels) {
    uint64_t jumpTo = label.second.first;
    auto& jumpFromVector = label.second.second;
    for (auto& jumpFrom : jumpFromVector) {
      asmGenerator->code[jumpFrom - 1] += " " + std::to_string(jumpTo);
    }
    // we complete code based on this vector, we dont need values from this
    // vector
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
  if (var.getType() == Value::VALTYPE_LVALUE_VAR)
    moveRvalueToReg(x, dynamic_cast<const LvalueVar&>(var).getAddr());
  else  // Array, t[a] or t[10]
  {
    const LvalueArray& arr = dynamic_cast<const LvalueArray&>(var);
    moveRvalueToReg(x, arr.getAddr());  // x := &arr[0]

    Register& temp = Architecture::getFreeRegister();
    temp.lock();

    Register& temp2 = Architecture::getFreeRegister();
    Register& retVal = Architecture::getRetValRegister();

    const Value* accessElement = arr.getAccessElement();
    if (accessElement->getType() == Value::VALTYPE_RVALUE)
      moveRvalueToReg(temp,
                      dynamic_cast<const Rvalue*>(accessElement)->getValue());

    else {
      moveRvalueToReg(temp,
                      dynamic_cast<const Lvalue*>(accessElement)->getAddr());

      if (!retVal.isFree() || x.getName() == retVal.getName()) {
        temp2.lock();
        asmPut(temp2);
      }
      asmLoad(temp);  // temp := *(&access_element)
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
    asmAdd(temp);  // x := &arr[access_element]
    if (x.getName() != retVal.getName()) asmPut(x);
    if (!retVal.isFree() && x.getName() != retVal.getName()) {
      asmGet(temp2);
      temp2.unlock();
    }

    temp.unlock();
  }
}

void AssemblerGenerator::load(const Register& x, const Value& val) {
  if (val.getType() == Value::VALTYPE_RVALUE)
    moveRvalueToReg(x, dynamic_cast<const Rvalue&>(val).getValue());
  else {
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

  // temp := &var
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

void AssemblerGenerator::read(const Lvalue& var) {
  Register& temp = Architecture::getFreeRegister();
  temp.lock();

  // temp := &var
  moveAddrToReg(temp, var);

  asmRead();
  asmStore(temp);

  temp.unlock();
}

void AssemblerGenerator::write(const Value& val) {
  if (val.getType() == Value::VALTYPE_RVALUE)
    moveRvalueToReg(Architecture::getRetValRegister(),
                    dynamic_cast<const Rvalue&>(val).getValue());
  else {
    moveAddrToReg(Architecture::getRetValRegister(),
                  dynamic_cast<const Lvalue&>(val));
    asmLoad(Architecture::getRetValRegister());
  }

  asmWrite();
}

void AssemblerGenerator::add(const Value& val1, const Value& val2) {
  Register& temp = Architecture::getFreeRegister();
  temp.lock();
  if (val1.getType() == Value::VALTYPE_RVALUE)
    moveRvalueToReg(temp, dynamic_cast<const Rvalue&>(val1).getValue());
  else {
    moveAddrToReg(temp, dynamic_cast<const Lvalue&>(val1));
    asmLoad(temp);
    asmPut(temp);
  }

  Register& retVal = Architecture::getRetValRegister();
  retVal.lock();
  if (val2.getType() == Value::VALTYPE_RVALUE)
    moveRvalueToReg(retVal, dynamic_cast<const Rvalue&>(val2).getValue());
  else {
    moveAddrToReg(retVal, dynamic_cast<const Lvalue&>(val2));
    asmLoad(retVal);
  }

  asmAdd(temp);
  temp.unlock();
}

void AssemblerGenerator::sub(const Value& val1, const Value& val2) {
  Register& temp = Architecture::getFreeRegister();
  temp.lock();
  if (val1.getType() == Value::VALTYPE_RVALUE)
    moveRvalueToReg(temp, dynamic_cast<const Rvalue&>(val1).getValue());
  else {
    moveAddrToReg(temp, dynamic_cast<const Lvalue&>(val1));
    asmLoad(temp);
    asmPut(temp);
  }

  Register& retVal = Architecture::getRetValRegister();
  retVal.lock();
  if (val2.getType() == Value::VALTYPE_RVALUE)
    moveRvalueToReg(retVal, dynamic_cast<const Rvalue&>(val2).getValue());
  else {
    moveAddrToReg(retVal, dynamic_cast<const Lvalue&>(val2));
    asmLoad(retVal);
  }

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

  // Peasant Multiplication
  asmGet(temp1);
  asmJZeroLabel(labelEnd);

  // we reuse this jzero as initial check and loop check
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
  // retval will be used in assignment, so dont unlock it now
}

void AssemblerGenerator::div(const Value& val1, const Value& val2) {
  // PREPARATION PHASE
  // Alloc 2 variables (clone of val1 and val2) to make reload easier (1 reg
  // instead of 2 in case of array)
  Lvalue* cloneVal1 = new LvalueVar("clone1", true);
  cloneVal1->setAddr(Architecture::alloc(1));

  Lvalue* cloneVal2 = new LvalueVar("clone2", true);
  cloneVal2->setAddr(Architecture::alloc(1));

  // Copy val1 to clone_val1 and val2_to clone_val2
  Register& temp1 = Architecture::getFreeRegister();
  temp1.lock();

  load(temp1, val1);
  store(*cloneVal1, temp1);

  Register& temp2 = Architecture::getFreeRegister();
  temp2.lock();

  load(temp2, val2);
  store(*cloneVal2, temp2);

  // get temp3 as temp1 (val1) and temp4 as temp1 (val2)
  Register& temp3 = Architecture::getFreeRegister();
  temp3.lock();

  load(temp3, *cloneVal1);

  Register& temp4 = Architecture::getFreeRegister();
  temp4.lock();

  load(temp4, *cloneVal2);
  // Now: temp1 = temp3 = val1, temp2 = temp4 = val2

  Register& retval = Architecture::getRetValRegister();
  retval.lock();

  // CHECK PHASE
  //  0 / 0 -> 0, a / 0 -> 0, 0 / b -> 0
  //  a / b -> 1
  //  a / b -> 0 if a < b

  const std::string label_end = labelManager.createLabel("DIV_END");
  const std::string label_ret0 = labelManager.createLabel("DIV_RETURN_0");
  const std::string label_ret1 = labelManager.createLabel("DIV_RETURN_1");
  const std::string label_start_algo =
      labelManager.createLabel("DIV_START_ALGO");

  // return 0
  asmGet(temp1);
  asmJZeroLabel(label_ret0);
  asmGet(temp2);
  asmJZeroLabel(label_ret0);

  // max{a - b, 0} + max{b - a, 0} == 0 iff a == b. But we know that a != 0 &&
  // b & 0 so return 1
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

  // a < b -> a != b && a - b == 0. We know that a != 0, so a < b. Return 0
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

  // MAIN ALGO PHASE
  // Check Phase destroys a and b in registers we need to reload this
  const std::string label_count_0 = labelManager.createLabel("DIV_COUNT_0");
  const std::string label_reload_b = labelManager.createLabel("DIV_RELOAD_B");
  const std::string label_add_0 = labelManager.createLabel("DIV_ADD_0");
  const std::string label_finish_add_0 =
      labelManager.createLabel("DIV_FINISH_ADD_0");
  const std::string label_loop = labelManager.createLabel("DIV_COUNT_LOOP");
  const std::string label_b_gt = labelManager.createLabel("DIV_B_IS_GREATER");

  labelManager.insertLabel(label_start_algo);
  load(temp1, *cloneVal1);
  load(temp2, *cloneVal2);

  moveRvalueToReg(temp4, 0);
  moveRvalueToReg(temp3, 1);

  labelManager.insertLabel(label_count_0);
  asmGet(temp2);
  asmJZeroLabel(label_reload_b);
  asmShr(temp2);
  asmShr(temp1);
  asmJumpLabel(label_count_0);

  labelManager.insertLabel(label_reload_b);
  load(temp2, *cloneVal2);  // we have broken "b" in temp2 but we need fresh
                            // "b" -> reload

  labelManager.insertLabel(label_add_0);
  asmGet(temp1);
  asmJZeroLabel(label_finish_add_0);
  asmShr(temp1);
  asmShl(temp2);
  asmInc(temp3);
  asmJumpLabel(label_add_0);

  labelManager.insertLabel(label_finish_add_0);
  load(temp1, *cloneVal1);  // as above here we used "a" to calculate temp3
                            // (counter). Reload fresh "a"

  // MAIN DIV LOOP
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

  // store current value in memory, we need current value in reg and prev
  // value in memory
  store(*cloneVal1, temp1);
  asmJumpLabel(label_loop);

  labelManager.insertLabel(label_b_gt);
  load(temp1, *cloneVal1);  // get prev value of "a"
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

  delete cloneVal1;
  delete cloneVal2;
}

void AssemblerGenerator::mod(const Value& val1, const Value& val2) {
  // PREPARATION PHASE
  // Alloc 2 variables (clone of val1 and val2) to make reload easier (1 reg
  // instead of 2 in case of array)
  Lvalue* cloneVal1 = new LvalueVar("clone1", true);
  cloneVal1->setAddr(Architecture::alloc(1));

  Lvalue* cloneVal2 = new LvalueVar("clone2", true);
  cloneVal2->setAddr(Architecture::alloc(1));

  // Copy val1 to clone_val1 and val2_to clone_val2
  Register& temp1 = Architecture::getFreeRegister();
  temp1.lock();

  load(temp1, val1);
  store(*cloneVal1, temp1);

  Register& temp2 = Architecture::getFreeRegister();
  temp2.lock();

  load(temp2, val2);
  store(*cloneVal2, temp2);

  // get temp3 as temp1 (val1) and temp4 as temp1 (val2)
  Register& temp3 = Architecture::getFreeRegister();
  temp3.lock();

  load(temp3, *cloneVal1);

  Register& temp4 = Architecture::getFreeRegister();
  temp4.lock();

  load(temp4, *cloneVal2);
  // Now: temp1 = temp3 = val1, temp2 = temp4 = val2

  Register& retval = Architecture::getRetValRegister();
  retval.lock();

  // CHECK PHASE
  //  0 / 0 -> 0, a / 0 -> 0, 0 / b -> 0
  //  a / b -> 1
  //  a / b -> 0 if a < b

  const std::string label_end = labelManager.createLabel("MOD_END");
  const std::string label_ret0 = labelManager.createLabel("MOD_RETURN_0");
  const std::string label_reta = labelManager.createLabel("MOD_RETURN_a");
  const std::string label_start_algo =
      labelManager.createLabel("MOD_START_ALGO");

  // return 0
  asmGet(temp1);
  asmJZeroLabel(label_ret0);
  asmGet(temp2);
  asmJZeroLabel(label_ret0);

  // max{a - b, 0} + max{b - a, 0} == 0 iff a == b. But we know that a != 0 &&
  // b & 0 so return 1
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

  // a < b -> a != b && a - b == 0. We know that a != 0, so a < b. Return 0
  asmGet(temp3);
  asmSub(temp4);
  asmJZeroLabel(label_reta);
  asmJumpLabel(label_start_algo);

  // TODO: lock retval in the end (same above) !!!!!!!!!!!!!!!!

  labelManager.insertLabel(label_ret0);
  asmRst(temp4);
  asmJumpLabel(label_end);
  labelManager.insertLabel(label_reta);
  load(temp4, *cloneVal1);
  asmJumpLabel(label_end);

  // MAIN ALGO PHASE
  // Check Phase destroys a and b in registers we need to reload this
  const std::string label_count_0 = labelManager.createLabel("MOD_COUNT_0");
  const std::string label_reload_b = labelManager.createLabel("MOD_RELOAD_B");
  const std::string label_add_0 = labelManager.createLabel("MOD_ADD_0");
  const std::string label_finish_add_0 =
      labelManager.createLabel("MOD_FINISH_ADD_0");
  const std::string label_loop = labelManager.createLabel("MOD_COUNT_LOOP");
  const std::string label_b_gt = labelManager.createLabel("MOD_B_IS_GREATER");

  labelManager.insertLabel(label_start_algo);
  load(temp4, *cloneVal1);
  load(temp2, *cloneVal2);

  moveRvalueToReg(temp1, 0);
  moveRvalueToReg(temp3, 1);

  labelManager.insertLabel(label_count_0);
  asmGet(temp2);
  asmJZeroLabel(label_reload_b);
  asmShr(temp2);
  asmShr(temp4);
  asmJumpLabel(label_count_0);

  labelManager.insertLabel(label_reload_b);
  load(temp2, *cloneVal2);  // we have broken "b" in temp2 but we need fresh
                            // "b" -> reload

  labelManager.insertLabel(label_add_0);
  asmGet(temp4);
  asmJZeroLabel(label_finish_add_0);
  asmShr(temp4);
  asmShl(temp2);
  asmInc(temp3);
  asmJumpLabel(label_add_0);

  labelManager.insertLabel(label_finish_add_0);
  load(temp4, *cloneVal1);  // as above here we used "a" to calculate temp3
                            // (counter). Reload fresh "a"

  // MAIN DIV LOOP
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

  // store current value in memory, we need current value in reg and prev
  // value in memory
  store(*cloneVal1, temp4);
  asmJumpLabel(label_loop);

  labelManager.insertLabel(label_b_gt);
  load(temp4, *cloneVal1);  // get prev value of "a"
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

  delete cloneVal1;
  delete cloneVal2;
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

void AssemblerGenerator::finishProgram() { asmHalt(); }

void AssemblerGenerator::finishCodeGeneration() {
  labelManager.generateCodeFromLabels();
}

std::string AssemblerGenerator::getGeneratedCode() const {
  std::string result = "";
  for (auto const& line : code) result += line + '\n';
  return result;
}