//
// Created by Сергей Кривонос on 01.09.17.
//

#pragma once
#include "ValuableDescendantContract.h"

namespace omnn{
namespace extrapolator {

	class Integer;

	class Fraction
			: public ValuableDescendantContract<Fraction>
	{
		using base = ValuableDescendantContract<Fraction>;
		using value_type = omnn::extrapolator::Valuable;
		using const_ref_type = const value_type&;
		value_type numerator, denominator;

	protected:
		std::ostream& print(std::ostream& out) const override;

	public:
		Valuable operator -() const override;
		Valuable& operator +=(const Valuable& v) override;
		Valuable& operator *=(const Valuable& v) override;
		Valuable& operator /=(const Valuable& v) override;
		Valuable& operator %=(const Valuable& v) override;
		Valuable& operator --() override;
		Valuable& operator ++() override;
		bool operator <(const Valuable& v) const override;
		bool operator ==(const Valuable& v) const override;
		void optimize() override;

		using base::base;

		Fraction() : numerator(0), denominator(1)
		{
            hash = numerator.Hash() ^ denominator.Hash();
        }

		Fraction(int n)
				: numerator(n), denominator(1)
		{
            hash = numerator.Hash() ^ denominator.Hash();
        }

		Fraction(const_ref_type n)
		: numerator(n)
		, denominator(1)
		{
			auto e = cast(n);
			if (e)
			{
				numerator = e->numerator;
				denominator = e->denominator;
			}
            hash = numerator.Hash() ^ denominator.Hash();
		}
		Fraction(const Integer& n);

		Fraction(const_ref_type n, const_ref_type d)
				: numerator(n), denominator(d)
		{
            hash = numerator.Hash() ^ denominator.Hash();
        }

		Fraction(Fraction&&) = default;
		Fraction(const Fraction&)=default;
		Fraction& operator=(const Fraction& f)=default;
		Fraction& operator=(Fraction&& f)=default;

        const Valuable& getDenominator() const { return denominator; }
        const Valuable& getNumerator() const { return numerator; }
        
        /// returns rw accessor
		Valuable getDenominator();
        /// returns rw accessor
		Valuable getNumerator();

		Fraction Reciprocal() const;
		const Variable* FindVa() const override;
		void CollectVa(std::set<Variable>& s) const override;
		void Eval(const Variable& va, const Valuable& v) override;
		bool IsSimple() const;
	};

}}
