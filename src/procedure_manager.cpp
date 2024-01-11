#include <procedure_manager.hpp>

ProcedureManager::ProcedureManager()
    : mainProcedure{Procedure("0", "to_be_def_later")},
      isMainProcedureSet{false} {}

void ProcedureManager::addProcedure(const Procedure& procedure) {
    procedures.push_back(procedure);
}

Procedure& ProcedureManager::getProcedure(const std::string& name) {
    for (auto& procedure : procedures) {
        if (procedure.getName() == name) {
            return procedure;
        }
    }
    return mainProcedure;
}

Procedure& ProcedureManager::getCurrentProcedure() {
    if (isMainProcedureSet) {
        return mainProcedure;
    } else {
        return procedures.back();
    }
}

bool ProcedureManager::isProcedureDeclared(const std::string& name) {
    for (auto& procedure : procedures) {
        if (procedure.getName() == name) {
            return true;
        }
    }
    return false;
}
