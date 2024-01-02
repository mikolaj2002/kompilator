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
  // else  // Array, t[a] or t[10]
  // {
  //     const LvalueArray& arr = dynamic_cast<const LvalueArray&>(var);
  //     moveRvalueToReg(x, arr.get_addr());  // x := &arr[0]

  //     Register& temp = Architecture::getFreeRegister();
  //     temp.lock();

  //     const Value* accessElement = arr.getAccessElement();
  //     if (access_element->getType() == Value::VALTYPE_RVALUE)
  //         moveRvalueToReg(
  //             temp, dynamic_cast<const
  //             Rvalue*>(accessElement)->getValue());
  //     else {
  //         moveRvalueToReg(
  //             temp, dynamic_cast<const
  //             Lvalue*>(access_element)->getAddr());
  //         asmLoad(temp, temp);  // temp := *(&access_element)
  //     }

  //     asm_add(x, temp);  // x := &arr[access_element]

  //     move_rvalue_to_reg(temp, arr.get_access_offset());  // temp := offset

  //     asm_sub(x, temp);  // x := &arr[access_element - array_offset]

  //     temp.unlock();
  // }
}

void AssemblerGenerator::load(const Register& x, const Value& val) {
  if (val.getType() == Value::VALTYPE_RVALUE)
    moveRvalueToReg(x, dynamic_cast<const Rvalue&>(val).getValue());
  else {
    moveAddrToReg(x, dynamic_cast<const Lvalue&>(val));
    Register& retVal = Architecture::getRetValRegister();
    Register& temp = Architecture::getFreeRegister();
    if (!retVal.isFree()) {
      temp.lock();
      asmPut(temp);
    }
    asmLoad(x);
    asmPut(x);
    if (!retVal.isFree()) {
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

  if (!retVal.isFree()) {
    temp2.lock();
    asmPut(temp2);
  }
  asmGet(x);
  asmStore(temp);
  if (!retVal.isFree()) {
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

void AssemblerGenerator::finishProgram() { asmHalt(); }

void AssemblerGenerator::finishCodeGeneration() {
  labelManager.generateCodeFromLabels();
}

std::string AssemblerGenerator::getGeneratedCode() const {
  std::string result = "";
  for (auto const& line : code) result += line + '\n';
  return result;
}