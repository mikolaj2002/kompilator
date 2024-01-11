#ifndef PROCEDURE_MANAGER_HPP
#define PROCEDURE_MANAGER_HPP

#include <procedure.hpp>
#include <vector>

class ProcedureManager {
   private:
    std::vector<Procedure> procedures;
    Procedure mainProcedure;
    bool isMainProcedureSet;

   public:
    ProcedureManager();
    ~ProcedureManager() = default;
    ProcedureManager(const ProcedureManager& from) = default;
    ProcedureManager& operator=(const ProcedureManager& from) = default;
    ProcedureManager(ProcedureManager&&) = default;
    ProcedureManager& operator=(ProcedureManager&&) = default;

    void addProcedure(const Procedure& procedure);
    Procedure& getProcedure(const std::string& name);
    Procedure& getCurrentProcedure();
    bool isProcedureDeclared(const std::string& name);
    void setMainProcedure() { isMainProcedureSet = true; }
    Procedure& getMainProcedure() { return mainProcedure; }
};

#endif  // PROCEDURE_MANAGER_HPP