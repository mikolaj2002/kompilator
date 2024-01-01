#ifndef LOOP_HPP
#define LOOP_HPP

#include <lvalue.hpp>
#include <memory>

class Loop {
   public:
    typedef enum { LOOP_TYPE_WHILE, LOOP_TYPE_UNTIL } looptype_t;

   private:
    std::string startLabel;
    std::string endLabel;
    looptype_t type;

   public:
    Loop(const std::string& startLabel, const std::string& endLabel,
         looptype_t type);
    virtual ~Loop() = default;
    Loop(const Loop& from) = default;
    Loop& operator=(const Loop& from) = default;
    Loop(Loop&&) = default;
    Loop& operator=(Loop&&) = default;

    const std::string& getStartLabel() const { return startLabel; }
    const std::string& get_end_label() const { return endLabel; }
    void setStartLabel(const std::string& label) { startLabel = label; }
    void setEndLabel(const std::string& label) { endLabel = label; }
    looptype_t getType() const { return type; }
};

#endif
