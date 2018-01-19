//
// Created by Сергей Кривонос on 30.09.17.
//

#pragma once
#include "Formula.h"

namespace omnn {
namespace math {


class FormulaOfVaWithSingleIntegerRoot
        : public Formula
{
    using base = Formula;
    
protected:
    size_t grade;
    Valuable Solve(Valuable& v) const override;
    std::ostream& print(std::ostream& out) const override;

public:
    using base::base;
    enum Mode {
        Strict,
        Closest,
        FirstExtrenum
    };
    Mode mode;
    void SetMode(Mode m) { mode = m; }
};
}}