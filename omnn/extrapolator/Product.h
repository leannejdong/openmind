//
// Created by Сергей Кривонос on 25.09.17.
//

#pragma once
#include <unordered_set>
#include "ValuableCollectionDescendantContract.h"
#include "Fraction.h"
#include "Variable.h"

namespace omnn{
namespace extrapolator {

    struct ValuableLessCompare
    {
        bool operator()(const Valuable&, const Valuable&);
    };
    

class Product
    : public ValuableCollectionDescendantContract<Product, std::unordered_multiset<Valuable>>
{
    using base = ValuableCollectionDescendantContract<Product, std::unordered_multiset<Valuable>>;
    using base::cont;
    friend class Variable;
    cont members;
    using vars_cont_t = std::multiset<Variable>;
    vars_cont_t vars;
    
protected:
	cont& GetCont() override { return members; }
    std::ostream& print(std::ostream& out) const override;
    Product(const vars_cont_t& v) : vars(v) { Add(1_v); }

public:
    using base::base;

    const cont& GetConstCont() const override { return members; }
    void Add(const Valuable& item) override;
    void Update(typename cont::iterator& it, const Valuable& v) override;
    void Delete(typename cont::iterator& it) override;
    
	template<class... T>
	Product(const T&... vals)
	{
		for (const auto& arg : { Valuable(vals)... })
		{
			Add(arg);
		}
	}

	Product() : members {{1}}
	{
        hash = members.begin()->Hash();
    }
    
    const std::multiset<Variable>& getCommonVars() const;
    Valuable varless() const;

	// virtual operators
	Valuable operator -() const override;
	Valuable& operator +=(const Valuable& v) override;
	Valuable& operator *=(const Valuable& v) override;
	Valuable& operator /=(const Valuable& v) override;
	Valuable& operator %=(const Valuable& v) override;
	Valuable& operator --() override;
	Valuable& operator ++() override;
	void optimize() override;
};


}}
