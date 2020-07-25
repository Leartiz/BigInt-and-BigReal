/*
* /File: BigInt.cpp /
* /Brief: BigInt and BigReal
* /Creator: Leonid Artemev | Leartiz /
* /Date: 2020 /
*/

#include <utility>
#include <cmath>
#include <sstream>
#include <algorithm>

#include "BigInt.h"


namespace lez
{

BigInt::BigInt() :
	b_num_vec(1, static_cast<std::int8_t>(0)), // default
	b_is_neg(false)
{
}

BigInt::BigInt(const BigInt& val_) :
	b_num_vec(val_.b_num_vec),
	b_is_neg(val_.b_is_neg)
{
}

BigInt::BigInt(BigInt&& val_) :
	b_num_vec(std::move(val_.b_num_vec)),
	b_is_neg(std::move(val_.b_is_neg))
{
}

BigInt::BigInt(std::int32_t val_) :
	BigInt()
{
	*this = to_big_int(val_);
}

BigInt::BigInt(std::size_t val_) :
	BigInt()
{
	*this = to_big_int(val_);
}

BigInt::BigInt(std::int64_t val_) :
	BigInt()
{
	*this = to_big_int(val_);
}

BigInt::BigInt(std::uint64_t val_) :
	BigInt()
{
	*this = to_big_int(val_);
}

BigInt& BigInt::operator=(std::int32_t val_)
{
	BigInt bi = to_big_int(val_);
	return operator=(bi);
}

BigInt& BigInt::operator=(std::size_t val_)
{
	BigInt bi = to_big_int(val_);
	return operator=(bi);
}

BigInt& BigInt::operator=(std::int64_t val_)
{
	BigInt bi = to_big_int(val_);
	return operator=(bi);
}

BigInt& BigInt::operator=(std::uint64_t val_)
{
	BigInt bi = to_big_int(val_);
	return operator=(bi);
}

BigInt& BigInt::operator=(BigInt val_)
{
	BigInt::swap(*this, val_);
	return *this;
}

std::int32_t BigInt::to_int32() const
{
	std::stringstream ss;
	if (b_is_neg)
		ss << "-";
	for (const auto& val : b_num_vec)
		ss << static_cast<std::int32_t>(val);
	std::int32_t val;
	ss >> val;
	return val;
}

std::size_t BigInt::to_size() const
{
	if (b_is_neg)
		return static_cast<std::size_t>(to_int32());
	std::stringstream ss;
	for (const auto& val : b_num_vec)
		ss << static_cast<std::int32_t>(val);
	std::size_t val;
	ss >> val;
	return val;
}

std::int64_t BigInt::to_int64() const
{
	std::stringstream ss;
	if (b_is_neg)
		ss << "-";
	for (const auto& val : b_num_vec)
		ss << static_cast<std::int32_t>(val);
	std::int64_t val;
	ss >> val;
	return val;
}

std::uint64_t BigInt::to_uint64() const
{
	std::stringstream ss;
	if (b_is_neg)
		ss << "-";
	for (const auto& val : b_num_vec)
		ss << static_cast<std::int32_t>(val);
	std::uint64_t val;
	ss >> val;
	return val;
}

std::size_t BigInt::amount_places() const
{
	return b_num_vec.size();
}

bool BigInt::is_neg() const
{
	return b_is_neg;
}

bool BigInt::is_zero() const
{
	for (const auto& val : b_num_vec)
		if (val != static_cast<std::int8_t>(0))
			return false;
	return true;
}

void BigInt::reverse_neg()
{
	if (b_is_neg)
		reset_neg();
	else
		set_neg();
}

void BigInt::set_neg()
{
	b_is_neg = !is_zero();
}

void BigInt::reset_neg()
{
	b_is_neg = false;
}

void BigInt::reset()
{
	*this = BigInt();
}


// ----------------------------------------------------------------------------
// unary
const BigInt BigInt::operator-() const
{
	BigInt bi(*this);
	bi.b_is_neg = (bi.b_is_neg) ? false : !bi.is_zero();
	return bi;
}

const BigInt BigInt::operator+() const
{
	return *this; // cp
}

BigInt& BigInt::operator--()
{
	return operator-=(1);
}

BigInt& BigInt::operator++()
{
	return operator+=(1);
}

const BigInt BigInt::operator--(int)
{
	BigInt bi = *this;
	operator-=(1);
	return bi;
}

const BigInt BigInt::operator++(int)
{
	BigInt bi = *this;
	operator+=(1);
	return bi;
}

BigInt::operator bool() const
{
	return !is_zero();
}

BigInt::operator std::int32_t() const
{
	return to_int32();
}

BigInt::operator std::size_t() const
{
	return to_size();
}

BigInt::operator std::int64_t() const
{
	return to_int64();
}

BigInt::operator std::uint64_t() const
{
	return to_uint64();
}


// ----------------------------------------------------------------------------
// arithmetic + and -
const BigInt BigInt::operator+(std::int32_t r_val_) const
{
	BigInt bi = to_big_int(r_val_);
	return operator+(bi);
}

const BigInt BigInt::operator+(std::size_t r_val_) const
{
	BigInt bi = to_big_int(r_val_);
	return operator+(bi);
}

const BigInt BigInt::operator+(std::int64_t r_val_) const
{
	BigInt bi = to_big_int(r_val_);
	return operator+(bi);
}

const BigInt BigInt::operator+(std::uint64_t r_val_) const
{
	BigInt bi = to_big_int(r_val_);
	return operator+(bi);
}

const BigInt BigInt::operator+(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	BigInt cp_l_val(*this);
	BigInt cp_r_val(r_val_);
	if (!is_neg_l && !is_neg_r)
	{
		cp_l_val = addition(std::move(cp_l_val), std::move(cp_r_val));
		return cp_l_val;
	}
	if (is_neg_l && is_neg_r)
	{
		cp_l_val = addition(std::move(cp_l_val), std::move(cp_r_val));
		cp_l_val.b_is_neg = true;
		return cp_l_val;
	}
	if (!is_neg_l && is_neg_r)
	{
		cp_r_val.b_is_neg = false;
		if (cp_l_val >= cp_r_val)
		{
			cp_l_val = subtraction(std::move(cp_l_val), std::move(cp_r_val));
			return cp_l_val;
		}
		cp_l_val = subtraction(std::move(cp_r_val), std::move(cp_l_val));
		cp_l_val.b_is_neg = true;
	}
	cp_l_val.b_is_neg = false;
	if (r_val_ >= cp_l_val)
	{
		cp_l_val = subtraction(std::move(cp_r_val), std::move(cp_l_val));
		return cp_l_val;
	}
	cp_l_val = subtraction(std::move(cp_l_val), std::move(cp_r_val));
	cp_l_val.b_is_neg = true;
	return cp_l_val;
}

const BigInt BigInt::operator-(std::int32_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator-(r_val);
}

const BigInt BigInt::operator-(std::size_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator-(r_val);
}

const BigInt BigInt::operator-(std::int64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator-(r_val);
}

const BigInt BigInt::operator-(std::uint64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator-(r_val);
}

const BigInt BigInt::operator-(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	BigInt cp_r_val(r_val_);
	if (!is_neg_l && !is_neg_r)
	{
		cp_r_val.b_is_neg = true;
		return operator+(cp_r_val);
	}
	if (is_neg_l && is_neg_r)
	{
		cp_r_val.b_is_neg = false;
		return operator+(cp_r_val);
	}
	if (!is_neg_l && is_neg_r)
	{
		cp_r_val.b_is_neg = false;
		return operator+(cp_r_val);
	}
	cp_r_val.b_is_neg = true;
	return operator+(cp_r_val);
}

BigInt& BigInt::operator+=(std::int32_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigInt& BigInt::operator+=(std::size_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigInt& BigInt::operator+=(std::int64_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigInt& BigInt::operator+=(std::uint64_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigInt& BigInt::operator+=(const BigInt& r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigInt& BigInt::operator-=(std::int32_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigInt& BigInt::operator-=(std::size_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigInt& BigInt::operator-=(std::int64_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigInt& BigInt::operator-=(std::uint64_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

const BigInt operator+(std::int32_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigInt operator+(std::size_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigInt operator+(std::int64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigInt operator+(std::uint64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigInt operator-(std::int32_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator-(r_val_);
}

const BigInt operator-(std::size_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator-(r_val_);
}

const BigInt operator-(std::int64_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator-(r_val_);
}

const BigInt operator-(std::uint64_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator-(r_val_);
}

BigInt BigInt::addition(BigInt l_val_, BigInt r_val_)
{
	std::size_t gen_ap = (l_val_.amount_places() > r_val_.amount_places() ?
		l_val_.amount_places() : r_val_.amount_places());
	BigInt l_full_val = append_leading_zeros(std::move(l_val_), gen_ap);
	BigInt r_full_val = append_leading_zeros(std::move(r_val_), gen_ap);
	bool is_carry = false;
	std::size_t r_i = gen_ap - 1U;
	for (std::size_t i = 0U; i < gen_ap; ++i, --r_i)
	{
		if (is_carry)
		{
			++l_full_val.b_num_vec[r_i];
			is_carry = false;
		}
		l_full_val.b_num_vec[r_i] += r_full_val.b_num_vec[r_i];
		if (l_full_val.b_num_vec[r_i] >= static_cast<std::int8_t>(10))
		{
			l_full_val.b_num_vec[r_i] -= static_cast<std::int8_t>(10);
			is_carry = true;
		}
	}
	if (is_carry)
		l_full_val.b_num_vec.insert(l_full_val.b_num_vec.begin(), static_cast<std::int8_t>(1));
	l_full_val = remove_leading_zeros(std::move(l_full_val));
	return l_full_val;
}

BigInt BigInt::subtraction(BigInt l_val_, BigInt r_val_)
{
	std::size_t gen_ap = (l_val_.amount_places() > r_val_.amount_places() ?
		l_val_.amount_places() : r_val_.amount_places());
	BigInt l_full_val = append_leading_zeros(std::move(l_val_), gen_ap);
	BigInt r_full_val = append_leading_zeros(std::move(r_val_), gen_ap);
	bool is_carry = false;
	std::size_t r_i = gen_ap - 1U;
	for (std::size_t i = 0U; i < gen_ap; ++i, --r_i)
	{
		if (is_carry)
		{
			--l_full_val.b_num_vec[r_i];
			is_carry = false;
		}
		l_full_val.b_num_vec[r_i] -= r_full_val.b_num_vec[r_i];
		if (l_full_val.b_num_vec[r_i] < static_cast<std::int8_t>(0))
		{
			l_full_val.b_num_vec[r_i] += 10;
			is_carry = true;
		}
	}
	l_full_val = remove_leading_zeros(std::move(l_full_val));
	return l_full_val;
}


// ----------------------------------------------------------------------------
// arithmetic * and /
const BigInt BigInt::operator*(std::int32_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator*(r_val);
}

const BigInt BigInt::operator*(std::size_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator*(r_val);
}

const BigInt BigInt::operator*(std::int64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator*(r_val);
}

const BigInt BigInt::operator*(std::uint64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator*(r_val);
}

const BigInt BigInt::operator*(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	BigInt cp_l_val(*this);
	BigInt cp_r_val(r_val_);
	cp_l_val.b_is_neg = false;
	cp_r_val.b_is_neg = false;
	if (cp_l_val > cp_r_val)
		BigInt::swap(cp_l_val, cp_r_val);
	cp_r_val = multiplication(std::move(cp_r_val), std::move(cp_l_val));
	if (is_neg_l == is_neg_r)
	{
		cp_r_val.b_is_neg = false;
		return cp_r_val;
	}
	cp_r_val.b_is_neg = !cp_r_val.is_zero();
	return cp_r_val;
}

BigInt BigInt::multiplication(BigInt l_val_, BigInt r_val_)
{
	BigInt res;
	l_val_.b_num_vec.insert(l_val_.b_num_vec.end(), 
		r_val_.b_num_vec.size() - 1U,
		static_cast<std::int8_t>(0));
	for (std::size_t i = 0U; i < r_val_.b_num_vec.size(); ++i)
	{
		res += simple_multiplication(l_val_, static_cast<std::int32_t>(r_val_.b_num_vec[i]));
		l_val_.b_num_vec.pop_back();
	}
	return res;
}

BigInt BigInt::simple_multiplication(BigInt val_, std::int32_t counter_)
{
	BigInt cp_val(val_);
	if (counter_ == 0)
		val_.reset();
	while (counter_ > 1)
	{
		val_.operator+=(cp_val);
		--counter_;
	}
	return val_;
}

const BigInt BigInt::operator/(std::int32_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator/(r_val);
}

const BigInt BigInt::operator/(std::size_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator/(r_val);
}

const BigInt BigInt::operator/(std::int64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator/(r_val);
}

const BigInt BigInt::operator/(std::uint64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator/(r_val);
}

const BigInt BigInt::operator/(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	BigInt cp_l_val(*this);
	BigInt cp_r_val(r_val_);
	cp_l_val.b_is_neg = false;
	cp_r_val.b_is_neg = false;
	if (r_val_.is_zero()) // division by zero
		return BigInt(); // ret zero
	if (cp_l_val < cp_r_val) // private case
		return BigInt(); 
	cp_r_val = division(std::move(cp_l_val), std::move(cp_r_val));
	if (is_neg_l == is_neg_r)
	{
		cp_r_val.b_is_neg = false;
		return cp_r_val;
	}
	cp_r_val.b_is_neg = !cp_r_val.is_zero();
	return cp_r_val;
}

BigInt BigInt::division(BigInt l_val_, BigInt r_val_)
{
	BigInt res;
	BigInt cp_part_res;
	std::size_t am_zeros = l_val_.b_num_vec.size() - r_val_.b_num_vec.size(); // max size
	r_val_.b_num_vec.insert(r_val_.b_num_vec.end(), am_zeros, static_cast<std::int8_t>(0));
	while (am_zeros != 0)
	{
		cp_part_res = simple_division(l_val_, r_val_);
		cp_part_res.b_num_vec.insert(cp_part_res.b_num_vec.end(),
			am_zeros,
			static_cast<std::int8_t>(0));
		res += cp_part_res;
		r_val_.b_num_vec.pop_back();
		--am_zeros;
	}
	res += simple_division(l_val_, r_val_);
	return res;
}

std::int32_t BigInt::simple_division(BigInt& val_, const BigInt& subthd_)
{
	std::int32_t res = -1;
	while (!val_.is_neg())
	{
		val_ -= subthd_;
		++res;
	}
	val_ += subthd_; // ret remainder
	return res;
}

const BigInt BigInt::operator%(std::int32_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator%(r_val);
}

const BigInt BigInt::operator%(std::size_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator%(r_val);
}

const BigInt BigInt::operator%(std::int64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator%(r_val);
}

const BigInt BigInt::operator%(std::uint64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator%(r_val);
}

const BigInt BigInt::operator%(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	BigInt cp_l_val(*this);
	BigInt cp_r_val(r_val_);
	cp_l_val.b_is_neg = false;
	cp_r_val.b_is_neg = false;
	if (cp_r_val == 0) // remainder of division by zero
		return BigInt(); // ret zero
	if (cp_l_val < cp_r_val)
		return cp_l_val;
	cp_r_val = modulo_division(std::move(cp_l_val), std::move(cp_r_val));
	if (!is_neg_l)
	{
		cp_r_val.b_is_neg = false;
		return cp_r_val;
	}
	cp_r_val.b_is_neg = !cp_r_val.is_zero();
	return cp_r_val;
}

BigInt BigInt::modulo_division(BigInt l_val_, BigInt r_val_)
{
	std::size_t am_zeros = l_val_.b_num_vec.size() - r_val_.b_num_vec.size(); // max size
	r_val_.b_num_vec.insert(r_val_.b_num_vec.end(), am_zeros, static_cast<std::int8_t>(0));
	while (am_zeros != 0)
	{
		simple_division(l_val_, r_val_);
		r_val_.b_num_vec.pop_back();
		--am_zeros;
	}
	simple_division(l_val_, r_val_);
	return l_val_;
}

BigInt& BigInt::operator*=(std::int32_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigInt& BigInt::operator*=(std::size_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigInt& BigInt::operator*=(std::int64_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigInt& BigInt::operator*=(std::uint64_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigInt& BigInt::operator/=(std::int32_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigInt& BigInt::operator/=(std::size_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigInt& BigInt::operator/=(std::int64_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigInt& BigInt::operator/=(std::uint64_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigInt& BigInt::operator/=(const BigInt& r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigInt& BigInt::operator%=(std::int32_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigInt& BigInt::operator%=(std::size_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigInt& BigInt::operator%=(std::int64_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigInt& BigInt::operator%=(std::uint64_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigInt& BigInt::operator%=(const BigInt& r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

const BigInt operator*(std::int32_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigInt operator*(std::size_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigInt operator*(std::int64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigInt operator*(std::uint64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigInt operator/(std::int32_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator/(r_val_);
}

const BigInt operator/(std::size_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator/(r_val_);
}

const BigInt operator/(std::int64_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator/(r_val_);
}

const BigInt operator/(std::uint64_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator/(r_val_);
}

const BigInt operator%(std::int32_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator%(r_val_);
}

const BigInt operator%(std::size_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator%(r_val_);
}

const BigInt operator%(std::int64_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator%(r_val_);
}

const BigInt operator%(std::uint64_t l_val_, const BigInt& r_val_)
{
	BigInt l_val = BigInt::to_big_int(l_val_);
	return l_val.operator%(r_val_);
}


// ----------------------------------------------------------------------------
// comparisons
bool BigInt::operator>(std::int32_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator>(r_val);
}

bool BigInt::operator>(std::size_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator>(r_val);
}

bool BigInt::operator>(std::int64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator>(r_val);
}

bool BigInt::operator>(std::uint64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator>(r_val);
}

bool BigInt::operator>(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	if (is_neg_l && !is_neg_r)
		return false;
	if (!is_neg_l && is_neg_r)
		return true;
	if (this->operator==(r_val_))
		return false;
	if (!is_neg_l && !is_neg_r)
		return logical_more(*this, r_val_);
	return !logical_more(*this, r_val_);
}

bool BigInt::logical_more(BigInt l_val_, BigInt r_val_)
{
	std::size_t gen_ap = (l_val_.amount_places() > r_val_.amount_places() ?
		l_val_.amount_places() : r_val_.amount_places());
	BigInt l_full_val = append_leading_zeros(std::move(l_val_), gen_ap);
	BigInt r_full_val = append_leading_zeros(std::move(r_val_), gen_ap);
	bool is_more = false;
	std::size_t r_i = gen_ap - 1U;
	for (std::size_t i = 0U; i < gen_ap; ++i, --r_i)
	{
		if (l_full_val.b_num_vec[r_i] > r_full_val.b_num_vec[r_i])
			is_more = true;
		else if (l_full_val.b_num_vec[r_i] < r_full_val.b_num_vec[r_i])
			is_more = false;
	}
	return is_more;
}

bool BigInt::operator<(std::int32_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator<(r_val);
}

bool BigInt::operator<(std::size_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator<(r_val);
}

bool BigInt::operator<(std::int64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator<(r_val);
}

bool BigInt::operator<(std::uint64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator<(r_val);
}

bool BigInt::operator<(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	if (is_neg_l && !is_neg_r)
		return true;
	if (!is_neg_l && is_neg_r)
		return false;
	if (this->operator==(r_val_))
		return false;
	if (!is_neg_l && !is_neg_r)
		return logical_less(*this, r_val_);
	return !logical_less(*this, r_val_);
}

bool BigInt::logical_less(BigInt l_val_, BigInt r_val_)
{
	std::size_t gen_ap = (l_val_.amount_places() > r_val_.amount_places() ?
		l_val_.amount_places() : r_val_.amount_places());
	BigInt l_full_val = append_leading_zeros(std::move(l_val_), gen_ap);
	BigInt r_full_val = append_leading_zeros(std::move(r_val_), gen_ap);
	bool is_less = false;
	std::size_t r_i = gen_ap - 1U;
	for (std::size_t i = 0U; i < gen_ap; ++i, --r_i)
	{
		if (l_full_val.b_num_vec[r_i] < r_full_val.b_num_vec[r_i])
			is_less = true;
		else if (l_full_val.b_num_vec[r_i] > r_full_val.b_num_vec[r_i])
			is_less = false;
	}
	return is_less;
}

bool BigInt::operator>=(std::int32_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigInt::operator>=(std::size_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigInt::operator>=(std::int64_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigInt::operator>=(std::uint64_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigInt::operator>=(const BigInt& r_val_) const
{
	return !operator<(r_val_);
}

bool BigInt::operator<=(std::int32_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigInt::operator<=(std::size_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigInt::operator<=(std::int64_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigInt::operator<=(std::uint64_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigInt::operator<=(const BigInt& r_val_) const
{
	return !operator>(r_val_);
}

bool BigInt::operator==(std::int32_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator==(r_val);
}

bool BigInt::operator==(std::size_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator==(r_val);
}

bool BigInt::operator==(std::int64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator==(r_val);
}

bool BigInt::operator==(std::uint64_t r_val_) const
{
	BigInt r_val = to_big_int(r_val_);
	return operator==(r_val);
}

bool BigInt::operator==(const BigInt& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	if (is_neg_l && !is_neg_r)
		return false;
	if (!is_neg_l && is_neg_r)
		return false;
	return logical_equal(*this, r_val_);
}

bool BigInt::logical_equal(BigInt l_val_, BigInt r_val_)
{
	if (l_val_.b_num_vec.size() != r_val_.b_num_vec.size())
		return false;
	bool is_equal = true;
	std::size_t r_i = l_val_.b_num_vec.size() - 1U;
	for (std::size_t i = 0U; is_equal && i < l_val_.b_num_vec.size(); ++i, --r_i)
		if (l_val_.b_num_vec[r_i] != r_val_.b_num_vec[r_i])
			is_equal = false;
	return is_equal;
}

bool BigInt::operator!=(std::int32_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigInt::operator!=(std::size_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigInt::operator!=(std::int64_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigInt::operator!=(std::uint64_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigInt::operator!=(const BigInt& r_val_) const
{
	return !operator==(r_val_);
}

bool operator>(std::int32_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator<(l_val_);
}

bool operator>(std::size_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator<(l_val_);
}

bool operator>(std::int64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator<(l_val_);
}

bool operator>(std::uint64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator<(l_val_);
}

bool operator<(std::int32_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator>(l_val_);
}

bool operator<(std::size_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator>(l_val_);
}

bool operator<(std::int64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator>(l_val_);
}

bool operator<(std::uint64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator>(l_val_);
}

bool operator>=(std::int32_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator>(l_val_);
}

bool operator>=(std::size_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator>(l_val_);
}

bool operator>=(std::int64_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator>(l_val_);
}

bool operator>=(std::uint64_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator>(l_val_);
}

bool operator<=(std::int32_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator<(l_val_);
}

bool operator<=(std::size_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator<(l_val_);
}

bool operator<=(std::int64_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator<(l_val_);
}

bool operator<=(std::uint64_t l_val_, const BigInt& r_val_)
{
	return !r_val_.operator<(l_val_);
}

bool operator==(std::int32_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator==(l_val_);
}

bool operator==(std::size_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator==(l_val_);
}

bool operator==(std::int64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator==(l_val_);
}

bool operator==(std::uint64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator==(l_val_);
}

bool operator!=(std::int32_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator!=(l_val_);
}

bool operator!=(std::size_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator!=(l_val_);
}

bool operator!=(std::int64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator!=(l_val_);
}

bool operator!=(std::uint64_t l_val_, const BigInt& r_val_)
{
	return r_val_.operator!=(l_val_);
}


// ----------------------------------------------------------------------------
// stream
std::istream& BigInt::operator>>(std::istream& stream_)
{
	std::string str;
	std::size_t st_p = 0U;
	stream_ >> str;
	if (str[0] == '-' || str[0] == '+')
		st_p = 1U;
	*this = read_big_int(str, st_p);
	if (str[0] == '-')
		b_is_neg = !is_zero();
	return stream_;
}

std::istream& operator>>(std::istream& stream_, BigInt& bi_)
{
	return bi_.operator>>(stream_);
}

BigInt BigInt::read_big_int(const std::string& str_, std::size_t st_p_)
{
	BigInt bi;
	std::size_t last_digit_p = st_p_;
	for (; last_digit_p < str_.length(); ++last_digit_p)
		if (str_[last_digit_p] < '0' || str_[last_digit_p] > '9')
			break;
	if (st_p_ == last_digit_p)
		return bi;
	bi.b_num_vec.clear();
	bi.b_num_vec.reserve(last_digit_p - st_p_ + 1U);
	for (std::size_t i = st_p_; i < last_digit_p; ++i)
		bi.b_num_vec.push_back(static_cast<std::int8_t>(str_[i] - '0')); // cp
	bi = remove_leading_zeros(std::move(bi));
	return bi;
}

std::ostream& BigInt::operator<<(std::ostream& stream_) const
{
	stream_ << to_string();
	return stream_;
}

std::string BigInt::to_string() const
{
	std::stringstream ss;
	if (b_is_neg)
		ss << "-";
	for (const auto& val : b_num_vec)
		ss << static_cast<std::int32_t>(val);
	return ss.str();
}

std::string BigInt::to_string_unsigned() const
{
	std::stringstream ss;
	for (const auto& val : b_num_vec)
		ss << static_cast<std::int32_t>(val);
	return ss.str();
}

std::ostream& operator<<(std::ostream& stream_, const BigInt& bi_)
{
	return bi_.operator<<(stream_);
}

BigInt BigInt::to_big_int(std::int32_t val_)
{
	BigInt bi;
	auto str = std::to_string(val_);
	to_big_int(bi, str);
	return bi;
}

BigInt BigInt::to_big_int(std::size_t val_)
{
	BigInt bi;
	auto str = std::to_string(val_);
	to_big_int(bi, str);
	return bi;
}

BigInt BigInt::to_big_int(std::int64_t val_)
{
	BigInt bi;
	auto str = std::to_string(val_);
	to_big_int(bi, str);
	return bi;
}

BigInt BigInt::to_big_int(std::uint64_t val_)
{
	BigInt bi;
	auto str = std::to_string(val_);
	to_big_int(bi, str);
	return bi;
}

BigInt BigInt::to_big_int(const std::string& str_)
{
	BigInt bi;
	to_big_int(bi, str_);
	return bi;
}

void BigInt::to_big_int(BigInt& bi_, const std::string& str_) // without check
{
	bi_.b_num_vec.clear();
	if (str_.empty())
	{
		bi_ = BigInt();
		return;
	}
	auto it = str_.cbegin();
	std::size_t offset = 0U;
	if (*it == '-')
	{
		bi_.b_is_neg = true; // direct
		offset = 1U;
		++it;
	}
	bi_.b_num_vec.reserve(str_.length() - offset);
	while (it != str_.cend())
	{
		bi_.b_num_vec.push_back(*it - static_cast<std::int8_t>(48));
		++it;
	}
	bi_ = remove_leading_zeros(bi_);
}

void BigInt::swap(BigInt& l_val_, BigInt& r_val_)
{
	using std::swap;
	swap(l_val_.b_num_vec, r_val_.b_num_vec);
	swap(l_val_.b_is_neg, r_val_.b_is_neg);
}

BigInt BigInt::append_leading_zeros(BigInt val_, std::size_t size_)
{
	while (val_.b_num_vec.size() < size_)
		val_.b_num_vec.insert(val_.b_num_vec.begin(), static_cast<std::int8_t>(0));
	return val_;
}

BigInt BigInt::remove_leading_zeros(BigInt val_)
{
	while (val_.b_num_vec.size() > 1U && (*val_.b_num_vec.begin()) == static_cast<std::int8_t>(0))
		val_.b_num_vec.erase(val_.b_num_vec.begin());
	return val_;
}


// ----------------------------------------------------------------------------
// extra (use in BigReal)
BigInt BigInt::addition_without_remove_leading_zeros(BigInt l_val_, BigInt r_val_)
{
	std::size_t gen_ap = (l_val_.amount_places() > r_val_.amount_places() ?
		l_val_.amount_places() : r_val_.amount_places());
	BigInt l_full_val = append_leading_zeros(std::move(l_val_), gen_ap);
	BigInt r_full_val = append_leading_zeros(std::move(r_val_), gen_ap);
	bool is_carry = false;
	std::size_t r_i = gen_ap - 1U;
	for (std::size_t i = 0U; i < gen_ap; ++i, --r_i)
	{
		if (is_carry)
		{
			++l_full_val.b_num_vec[r_i];
			is_carry = false;
		}
		l_full_val.b_num_vec[r_i] += r_full_val.b_num_vec[r_i];
		if (l_full_val.b_num_vec[r_i] >= static_cast<std::int8_t>(10))
		{
			l_full_val.b_num_vec[r_i] -= static_cast<std::int8_t>(10);
			is_carry = true;
		}
	}
	if (is_carry)
		l_full_val.b_num_vec.insert(l_full_val.b_num_vec.begin(), static_cast<std::int8_t>(1));
	return l_full_val;
}

BigInt BigInt::subtraction_without_remove_leading_zeros(BigInt l_val_, BigInt r_val_)
{
	std::size_t gen_ap = (l_val_.amount_places() > r_val_.amount_places() ?
		l_val_.amount_places() : r_val_.amount_places());
	BigInt l_full_val = append_leading_zeros(std::move(l_val_), gen_ap);
	BigInt r_full_val = append_leading_zeros(std::move(r_val_), gen_ap);
	bool is_carry = false;
	std::size_t r_i = gen_ap - 1U;
	for (std::size_t i = 0U; i < gen_ap; ++i, --r_i)
	{
		if (is_carry)
		{
			--l_full_val.b_num_vec[r_i];
			is_carry = false;
		}
		l_full_val.b_num_vec[r_i] -= r_full_val.b_num_vec[r_i];
		if (l_full_val.b_num_vec[r_i] < static_cast<std::int8_t>(0))
		{
			l_full_val.b_num_vec[r_i] += 10;
			is_carry = true;
		}
	}
	return l_full_val;
}

BigInt::~BigInt()
{
}

} // end nmspc
