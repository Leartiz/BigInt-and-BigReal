/*
* /File: BigReal.cpp /
* /Brief: BigInt and BigReal
* /Creator: Leonid Artemev | Leartiz /
* /Date: 2020 /
*/

#include <utility>
#include <cmath>
#include <sstream>
#include <algorithm>

#include "BigReal.h"


namespace lez
{

BigReal::BigReal() :
	b_whole_part(1U, static_cast<std::int8_t>(0)), // zero
	b_fractional_part(1U, static_cast<std::int8_t>(0)),
	b_am_dig_after_com(start_amount_digits_after_comma()),
	b_is_neg(false)
{
}

BigReal::BigReal(const BigReal& val_) :
	b_whole_part(val_.b_whole_part),
	b_fractional_part(val_.b_fractional_part),
	b_am_dig_after_com(val_.b_am_dig_after_com),
	b_is_neg(val_.b_is_neg)
{
}

BigReal::BigReal(BigReal&& val_) :
	b_whole_part(std::move(val_.b_whole_part)),
	b_fractional_part(std::move(val_.b_fractional_part)),
	b_am_dig_after_com(val_.b_am_dig_after_com),
	b_is_neg(val_.b_is_neg)
{
}

BigReal::BigReal(std::int32_t val_) :
	BigReal()
{
	*this = to_big_real(val_);
}

BigReal::BigReal(std::size_t val_) :
	BigReal()
{
	*this = to_big_real(val_);
}

BigReal::BigReal(std::int64_t val_) :
	BigReal()
{
	*this = to_big_real(val_);
}

BigReal::BigReal(std::uint64_t val_) :
	BigReal()
{
	*this = to_big_real(val_);
}

BigReal::BigReal(const BigInt& val_) :
	BigReal()
{
	*this = to_big_real(val_);
}

BigReal::BigReal(float val_) :
	BigReal()
{
	*this = to_big_real(val_);
}

BigReal::BigReal(double val_) :
	BigReal()
{
	*this = to_big_real(val_);
}


// ----------------------------------------------------------------------------
// assignment operator
BigReal& BigReal::operator=(std::int32_t val_)
{
	*this = to_big_real(val_);
	return *this;
}

BigReal& BigReal::operator=(std::size_t val_)
{
	*this = to_big_real(val_);
	return *this;
}

BigReal& BigReal::operator=(std::int64_t val_)
{
	*this = to_big_real(val_);
	return *this;
}

BigReal& BigReal::operator=(std::uint64_t val_)
{
	*this = to_big_real(val_);
	return *this;
}

BigReal& BigReal::operator=(const BigInt& val_)
{
	*this = to_big_real(val_);
	return *this;
}

BigReal& BigReal::operator=(float val_)
{
	*this = to_big_real(val_);
	return *this;
}

BigReal& BigReal::operator=(double val_)
{
	*this = to_big_real(val_);
	return *this;
}

BigReal& BigReal::operator=(BigReal val_)
{
	BigReal::swap(*this, val_);
	return *this;
}


// ----------------------------------------------------------------------------
// to type
std::int32_t BigReal::to_int32() const
{	
	BigInt bi;
	BigInt::to_big_int(bi, to_string_whole_part());
	return bi.to_int32();
}

std::size_t BigReal::to_size() const
{
	BigInt bi;
	BigInt::to_big_int(bi, to_string_whole_part());
	return bi.to_size();
}

std::int64_t BigReal::to_int64() const
{
	BigInt bi;
	BigInt::to_big_int(bi, to_string_whole_part());
	return bi.to_int64();
}

std::uint64_t BigReal::to_uint64() const
{
	BigInt bi;
	BigInt::to_big_int(bi, to_string_whole_part());
	return bi.to_uint64();
}

BigInt BigReal::to_big_int() const
{
	BigInt bi;
	BigInt::to_big_int(bi, to_string_whole_part());
	return bi;
}

float BigReal::to_float() const
{
	std::stringstream ss(to_string());
	float val = 0.0;
	ss >> val;
	return val;
}

double BigReal::to_double() const
{
	std::stringstream ss(to_string());
	double val = 0.0;
	ss >> val;
	return val;
}


// ----------------------------------------------------------------------------
// extra
std::size_t BigReal::amount_places() const
{
	return b_whole_part.size() + b_fractional_part.size();
}

std::size_t BigReal::amount_places_whole_part() const
{
	return b_whole_part.size();
}

std::size_t BigReal::amount_places_fractional_part() const
{
	return b_fractional_part.size();
}

bool BigReal::is_neg() const
{
	return b_is_neg;
}

bool BigReal::is_zero() const
{
	for (const auto& val : b_whole_part)
		if (val != static_cast<std::int8_t>(0))
			return false;
	for (const auto& val : b_fractional_part)
		if (val != static_cast<std::int8_t>(0))
			return false;
	return true;
}

void BigReal::reverse_neg()
{
	if (b_is_neg)
		reset_neg();
	else
		set_neg();
}

void BigReal::set_neg()
{
	b_is_neg = !is_zero();
}

void BigReal::reset_neg()
{
	b_is_neg = false;
}

void BigReal::reset()
{
	*this = BigReal();
}


// ----------------------------------------------------------------------------
// operators
BigReal::operator bool() const
{
	return !is_zero();
}

BigReal::operator std::int32_t() const
{
	return to_int32();
}

BigReal::operator std::size_t() const
{
	return to_size();
}

BigReal::operator std::int64_t() const
{
	return to_int64();
}

BigReal::operator std::uint64_t() const
{
	return to_uint64();
}

BigReal::operator BigInt() const
{
	return to_big_int();
}

BigReal::operator float() const
{
	return to_float();
}

BigReal::operator double() const
{
	return to_double();
}


// ----------------------------------------------------------------------------
// unary
const BigReal BigReal::operator-() const
{
	BigReal br(*this);
	br.b_is_neg = (br.b_is_neg) ? false : !br.is_zero();
	return br;
}

const BigReal BigReal::operator+() const
{
	return *this; // cp
}

BigReal& BigReal::operator--()
{
	return operator-=(1);
}

BigReal& BigReal::operator++()
{
	return operator+=(1);
}

const BigReal BigReal::operator--(int)
{
	BigReal br = *this;
	operator-=(1);
	return br;
}

const BigReal BigReal::operator++(int)
{
	BigReal br = *this;
	operator+=(1);
	return br;
}


// ----------------------------------------------------------------------------
// arithmetic +
const BigReal BigReal::operator+(std::int32_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator+(r_val);
}

const BigReal BigReal::operator+(std::size_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator+(r_val);
}

const BigReal BigReal::operator+(std::int64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator+(r_val);
}

const BigReal BigReal::operator+(std::uint64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator+(r_val);
}

const BigReal BigReal::operator+(const BigInt& r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator+(r_val);
}

const BigReal BigReal::operator+(float r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator+(r_val);
}

const BigReal BigReal::operator+(double r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator+(r_val);
}

const BigReal BigReal::operator+(const BigReal& r_val_) const
{
	BigReal res;
	std::size_t max_am_dig_after_com = std::max(b_am_dig_after_com, r_val_.b_am_dig_after_com);
	if (is_neg() == r_val_.is_neg()) // only pos or neg
	{
		res = addition_positive_or_negative_numbers(*this, r_val_); // without check
		res.set_amount_digits_after_comma(max_am_dig_after_com);
		return res;
	}
	if (!is_neg() && r_val_.is_neg())
	{
		res = subtraction(*this, r_val_); // pos + neg
		res.set_amount_digits_after_comma(max_am_dig_after_com);
		return res;
	}
	res = subtraction(r_val_, *this); // neg + pos
	res.set_amount_digits_after_comma(max_am_dig_after_com);
	return res;
}

BigReal BigReal::addition_positive_or_negative_numbers(const BigReal& l_val_, const BigReal& r_val_)
{
	BigReal res;
	BigInt l_val_fp, r_val_fp, res_fp;
	BigInt l_val_wp, r_val_wp, res_wp;
	// numbers as strings
	std::string l_val_fp_str = l_val_.to_string_fractional_part();
	std::string r_val_fp_str = r_val_.to_string_fractional_part();
	append_end_zeros_by_general_size(l_val_fp_str, r_val_fp_str);

	BigInt::to_big_int(l_val_fp, l_val_fp_str);
	BigInt::to_big_int(r_val_fp, r_val_fp_str);
	BigInt::to_big_int(l_val_wp, l_val_.to_string_unsigned_whole_part());
	BigInt::to_big_int(r_val_wp, r_val_.to_string_unsigned_whole_part());

	res_fp = l_val_fp + r_val_fp;
	res_wp = l_val_wp + r_val_wp;
	if (is_carry_after_addition_fractional_part(l_val_fp, r_val_fp, res_fp))
	{
		++res_wp;
		res_fp = remove_first_number_from_big_int(res_fp);
	}

	res = to_big_real_from_big_int(res_wp, res_fp);
	if (l_val_.is_neg() && r_val_.is_neg()) // should be equal
	{
		res.set_neg();
	}
	return res;
}

BigReal BigReal::subtraction(const BigReal& l_val_, const BigReal& r_val_)
{
	BigReal res;
	bool is_l_val_more = logical_more(l_val_ , r_val_);
	if (is_l_val_more)
	{
		res = subtraction_in_order(l_val_, r_val_);
		return res;
	}
	res = subtraction_in_order(r_val_, l_val_);
	res.set_neg();
	return res;
}

BigReal BigReal::subtraction_in_order(const BigReal& l_val_, const BigReal& r_val_)
{
	BigReal res;
	BigInt l_val_fp, r_val_fp, res_fp;
	BigInt l_val_wp, r_val_wp, res_wp;
	// numbers as strings
	std::string l_val_fp_str = l_val_.to_string_fractional_part();
	std::string r_val_fp_str = r_val_.to_string_fractional_part();
	append_end_zeros_by_general_size(l_val_fp_str, r_val_fp_str);

	BigInt::to_big_int(l_val_fp, l_val_fp_str);
	BigInt::to_big_int(r_val_fp, r_val_fp_str);
	BigInt::to_big_int(l_val_wp, l_val_.to_string_unsigned_whole_part());
	BigInt::to_big_int(r_val_wp, r_val_.to_string_unsigned_whole_part());

	bool is_carry = false;

	if (r_val_fp > l_val_fp)
	{
		l_val_fp_str.insert(0U, 1U, '1');
		BigInt::to_big_int(l_val_fp, l_val_fp_str);
		is_carry = true;
		--l_val_wp;
	}
	res_fp = BigInt::subtraction_without_remove_leading_zeros(l_val_fp, r_val_fp); // save leading zeros
	if (is_carry)
		res_fp = remove_first_number_from_big_int(res_fp);
	res_wp = l_val_wp - r_val_wp;
	res = to_big_real_from_big_int(res_wp, res_fp);
	return res;
}

bool BigReal::is_carry_after_addition_fractional_part(const BigInt& l_val_,
	const BigInt& r_val_,
	const BigInt& res_)
{
	std::size_t max_ap = std::max(l_val_.amount_places(), r_val_.amount_places());
	if (res_.amount_places() > max_ap)
		return true;
	return false;
}

BigInt BigReal::remove_first_number_from_big_int(const BigInt& val_)
{
	std::string val = val_.to_string();
	std::size_t pos_for_remove = 0U;
	if (val.front() == '-')
		++pos_for_remove;
	val.erase(pos_for_remove, 1U);
	return BigInt::to_big_int(val);
}

BigReal BigReal::to_big_real_from_big_int(const BigInt& wp_val_, const BigInt& fp_val_)
{
	std::string str_wp = wp_val_.to_string();
	remove_leading_zeros(str_wp);
	std::string str_fp = fp_val_.to_string_unsigned(); // only positive
	remove_end_zeros(str_fp);
	std::string str_res;
	str_res += str_wp;
	str_res += '.';
	str_res += str_fp;
	return BigReal::to_big_real(str_res);
}


// ----------------------------------------------------------------------------
// arithmetic -
const BigReal BigReal::operator-(std::int32_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator-(r_val);
}

const BigReal BigReal::operator-(std::size_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator-(r_val);
}

const BigReal BigReal::operator-(std::int64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator-(r_val);
}

const BigReal BigReal::operator-(std::uint64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator-(r_val);
}

const BigReal BigReal::operator-(const BigInt& r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator-(r_val);
}

const BigReal BigReal::operator-(float r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator-(r_val);
}

const BigReal BigReal::operator-(double r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator-(r_val);
}

const BigReal BigReal::operator-(const BigReal& r_val_) const
{
	BigReal cp_r_val = r_val_;
	if (!is_neg() && !cp_r_val.is_neg())
	{
		cp_r_val.b_is_neg = true;
		return operator+(cp_r_val);
	}
	if (is_neg() && cp_r_val.is_neg())
	{
		cp_r_val.b_is_neg = false;
		return operator+(cp_r_val);
	}
	if (!is_neg() && cp_r_val.is_neg())
	{
		cp_r_val.b_is_neg = false;
		return operator+(cp_r_val);
	}
	cp_r_val.b_is_neg = true;
	return operator+(cp_r_val);
}


// ----------------------------------------------------------------------------
// with edit lval
BigReal& BigReal::operator+=(std::int32_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator+=(std::size_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator+=(std::int64_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator+=(std::uint64_t r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator+=(const BigInt& r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator+=(float r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator+=(double r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator+=(const BigReal& r_val_)
{
	*this = this->operator+(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(std::int32_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(std::size_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(std::int64_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(std::uint64_t r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(const BigInt& r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(float r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(double r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}

BigReal& BigReal::operator-=(const BigReal& r_val_)
{
	*this = this->operator-(r_val_);
	return *this;
}


// ----------------------------------------------------------------------------
// friend arithmetic + or -
const BigReal operator+(std::int32_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigReal operator+(std::size_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigReal operator+(std::int64_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigReal operator+(std::uint64_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigReal operator+(const BigInt& l_val_, const BigReal& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigReal operator+(float l_val_, const BigReal& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigReal operator+(double l_val_, const BigReal& r_val_)
{
	return r_val_.operator+(l_val_);
}

const BigReal operator-(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator-(r_val_);
}

const BigReal operator-(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator-(r_val_);
}

const BigReal operator-(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator-(r_val_);
}

const BigReal operator-(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator-(r_val_);
}

const BigReal operator-(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator-(r_val_);
}

const BigReal operator-(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator-(r_val_);
}

const BigReal operator-(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator-(r_val_);
}


// ----------------------------------------------------------------------------
// arithmetic *
const BigReal BigReal::operator*(std::int32_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator*(r_val);
}

const BigReal BigReal::operator*(std::size_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator*(r_val);
}

const BigReal BigReal::operator*(std::int64_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator*(r_val);
}

const BigReal BigReal::operator*(std::uint64_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator*(r_val);
}

const BigReal BigReal::operator*(const BigInt& r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator*(r_val);
}

const BigReal BigReal::operator*(float r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator*(r_val);
}

const BigReal BigReal::operator*(double r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator*(r_val);
}

const BigReal BigReal::operator*(const BigReal& r_val_) const
{
	std::string l_val_str = to_string_whole_part() + to_string_fractional_part();
	std::string r_val_str = r_val_.to_string_whole_part() + r_val_.to_string_fractional_part();
	BigInt l_val = BigInt::to_big_int(l_val_str);
	BigInt r_val = BigInt::to_big_int(r_val_str);
	l_val *= r_val;
	std::string res_str = l_val.to_string();
	std::size_t offset = b_fractional_part.size() + r_val_.b_fractional_part.size();
	set_comma_in_result_string_after_multiplication(res_str, offset);
	std::size_t max_am_dig_after_com = std::max(b_am_dig_after_com, r_val_.b_am_dig_after_com);
	BigReal res = BigReal::to_big_real(res_str);
	res.set_amount_digits_after_comma(max_am_dig_after_com);
	return res;
}

void BigReal::set_comma_in_result_string_after_multiplication(std::string& res_str_, std::size_t offset_from_end_for_com_)
{
	if (res_str_ == "0") // private case
	{
		res_str_.insert(1U, ".0");
		return;
	}
	if (res_str_.length() <= offset_from_end_for_com_)
	{
		res_str_.insert(0U, offset_from_end_for_com_ - res_str_.length(), '0');
		res_str_.insert(0U, "0.");
		return;
	}
	res_str_.insert(res_str_.length() - offset_from_end_for_com_, 1U, '.'); // it works?
}


// ----------------------------------------------------------------------------
// arithmetic /
const BigReal BigReal::operator/(std::int32_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator/(r_val);
}

const BigReal BigReal::operator/(std::size_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator/(r_val);
}

const BigReal BigReal::operator/(std::int64_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator/(r_val);
}

const BigReal BigReal::operator/(std::uint64_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator/(r_val);
}

const BigReal BigReal::operator/(const BigInt& r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator/(r_val);
}

const BigReal BigReal::operator/(float r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator/(r_val);
}

const BigReal BigReal::operator/(double r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator/(r_val);
}

const BigReal BigReal::operator/(const BigReal& r_val_) const
{
	std::size_t max_size_fp = std::max(b_fractional_part.size(), r_val_.b_fractional_part.size());
	std::string l_val_str = to_string_unsigned_whole_part() + to_string_fractional_part(); // unsigned
	std::string r_val_str = r_val_.to_string_unsigned_whole_part() + r_val_.to_string_fractional_part();
	append_end_zeros(l_val_str, max_size_fp - b_fractional_part.size());
	append_end_zeros(r_val_str, max_size_fp - r_val_.b_fractional_part.size());

	BigInt l_val = BigInt::to_big_int(l_val_str);
	BigInt r_val = BigInt::to_big_int(r_val_str);
	BigInt res_wp = l_val / r_val; // whole

	BigInt rem_of_div = l_val % r_val;
	std::string rem_of_div_str = rem_of_div.to_string();
	
	std::size_t counter_am_dig_after_com = 0U;
	std::size_t max_am_dig_after_com = std::max(b_am_dig_after_com, r_val_.b_am_dig_after_com);

	BigInt part_res_fp;
	std::string res_fp_str; // fractional
	while (counter_am_dig_after_com < max_am_dig_after_com && !rem_of_div.is_zero())
	{
		rem_of_div *= 10;
		part_res_fp = rem_of_div / r_val; // 0-9
		rem_of_div %= r_val;
		res_fp_str.insert(res_fp_str.length(), part_res_fp.to_string());
		++counter_am_dig_after_com;
	}
	if (res_fp_str.empty())
		res_fp_str.push_back('0');
	std::string res_str = res_wp.to_string() + "." + res_fp_str;
	BigReal res = BigReal::to_big_real(res_str);
	res.set_amount_digits_after_comma(max_am_dig_after_com);
	if (b_is_neg == r_val_.b_is_neg)
	{
		res.b_is_neg = false;
		return res;
	}
	res.b_is_neg = !res.is_zero();
	return res;
}


// ----------------------------------------------------------------------------
// arithmetic %
const BigReal BigReal::operator%(std::int32_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator%(r_val);
}

const BigReal BigReal::operator%(std::size_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator%(r_val);
}

const BigReal BigReal::operator%(std::int64_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator%(r_val);
}

const BigReal BigReal::operator%(std::uint64_t r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator%(r_val);
}

const BigReal BigReal::operator%(const BigInt& r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator%(r_val);
}

const BigReal BigReal::operator%(float r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator%(r_val);
}

const BigReal BigReal::operator%(double r_val_) const
{
	BigReal r_val = BigReal::to_big_real(r_val_);
	return operator%(r_val);
}

const BigReal BigReal::operator%(const BigReal& r_val_) const
{
	BigReal gen_res = operator/(r_val_); // if r_val_ is neg, then ge_res will be neg
	gen_res.b_whole_part.clear();
	gen_res.b_whole_part.push_back(static_cast<std::int8_t>(0)); // set zero
	gen_res *= r_val_; // close to the remainder...
	return gen_res;
}


// ----------------------------------------------------------------------------
// arithmetic *, /, % for lval
BigReal& BigReal::operator*=(std::int32_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator*=(std::size_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator*=(std::int64_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator*=(std::uint64_t r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator*=(const BigInt& r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator*=(float r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator*=(double r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator*=(const BigReal& r_val_)
{
	*this = this->operator*(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(std::int32_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(std::size_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(std::int64_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(std::uint64_t r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(const BigInt& r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(float r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(double r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator/=(const BigReal& r_val_)
{
	*this = this->operator/(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(std::int32_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(std::size_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(std::int64_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(std::uint64_t r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(const BigInt& r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(float r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(double r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}

BigReal& BigReal::operator%=(const BigReal& r_val_)
{
	*this = this->operator%(r_val_);
	return *this;
}


// ----------------------------------------------------------------------------
// arithmetic * for friend
const BigReal operator*(std::int32_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigReal operator*(std::size_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigReal operator*(std::int64_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigReal operator*(std::uint64_t l_val_, const BigReal& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigReal operator*(const BigInt& l_val_, const BigReal& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigReal operator*(float l_val_, const BigReal& r_val_)
{
	return r_val_.operator*(l_val_);
}

const BigReal operator*(double l_val_, const BigReal& r_val_)
{
	return r_val_.operator*(l_val_);
}


// ----------------------------------------------------------------------------
// arithmetic / for friend
const BigReal operator/(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator/(r_val_);
}

const BigReal operator/(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator/(r_val_);
}

const BigReal operator/(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator/(r_val_);
}

const BigReal operator/(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator/(r_val_);
}

const BigReal operator/(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator/(r_val_);
}

const BigReal operator/(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator/(r_val_);
}

const BigReal operator/(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator/(r_val_);
}


// ----------------------------------------------------------------------------
// arithmetic % for friend
const BigReal operator%(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator%(r_val_);
}

const BigReal operator%(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator%(r_val_);
}

const BigReal operator%(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator%(r_val_);
}

const BigReal operator%(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator%(r_val_);
}

const BigReal operator%(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator%(r_val_);
}

const BigReal operator%(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator%(r_val_);
}

const BigReal operator%(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator%(r_val_);
}


// ----------------------------------------------------------------------------
// more
bool BigReal::operator>(std::int32_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator>(r_val);
}

bool BigReal::operator>(std::size_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator>(r_val);
}

bool BigReal::operator>(std::int64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator>(r_val);
}

bool BigReal::operator>(std::uint64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator>(r_val);
}

bool BigReal::operator>(const BigInt& r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator>(r_val);
}

bool BigReal::operator>(float r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator>(r_val);
}

bool BigReal::operator>(double r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator>(r_val);
}

bool BigReal::operator>(const BigReal& r_val_) const
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

bool BigReal::logical_more(const BigReal& l_val_, const BigReal& r_val_)
{
	bool is_mr_wp = logical_more_whole_part(l_val_, r_val_);
	bool is_eq_wp = logical_equal_whole_part(l_val_, r_val_);
	if (!is_mr_wp && is_eq_wp)
		return logical_more_fractional_part(l_val_, r_val_);
	return is_mr_wp;
}

bool BigReal::logical_more_whole_part(const BigReal& l_val_, const BigReal& r_val_)
{
	if (l_val_.amount_places_whole_part() > r_val_.amount_places_whole_part())
		return true;
	if (l_val_.amount_places_whole_part() < r_val_.amount_places_whole_part())
		return false;
	bool is_more = false;
	std::size_t r_i = l_val_.amount_places_whole_part() - 1U;
	for (std::size_t i = 0U; i < l_val_.amount_places_whole_part(); ++i, --r_i)
		if (l_val_.b_whole_part[r_i] > r_val_.b_whole_part[r_i])
			is_more = true;
		else if (l_val_.b_whole_part[r_i] < r_val_.b_whole_part[r_i])
			is_more = false;
	return is_more;
}

bool BigReal::logical_more_fractional_part(const BigReal& l_val_, const BigReal& r_val_)
{
	std::string l_val_fp = l_val_.to_string_fractional_part();
	std::string r_val_fp = r_val_.to_string_fractional_part();
	std::size_t gen_ap_wp = (l_val_fp.length() >= r_val_fp.length()) ?
		l_val_fp.length() : r_val_fp.length();
	append_end_zeros_by_general_size(l_val_fp, r_val_fp);
	bool is_more = false;
	std::size_t r_i = gen_ap_wp - 1U;
	for (std::size_t i = 0U; i < gen_ap_wp; ++i, --r_i)
		if (l_val_fp[r_i] > r_val_fp[r_i])
			is_more = true;
		else if (l_val_fp[r_i] < r_val_fp[r_i])
			is_more = false;
	return is_more;
}


// ----------------------------------------------------------------------------
// less
bool BigReal::operator<(std::int32_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator<(r_val);
}

bool BigReal::operator<(std::size_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator<(r_val);
}

bool BigReal::operator<(std::int64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator<(r_val);
}

bool BigReal::operator<(std::uint64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator<(r_val);
}

bool BigReal::operator<(const BigInt& r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator<(r_val);
}

bool BigReal::operator<(float r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator<(r_val);
}

bool BigReal::operator<(double r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator<(r_val);
}

bool BigReal::operator<(const BigReal& r_val_) const
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

bool BigReal::logical_less(BigReal l_val_, BigReal r_val_)
{
	bool is_ls_wp = logical_less_whole_part(l_val_, r_val_);
	bool is_eq_wp = logical_equal_whole_part(l_val_, r_val_);
	if (!is_ls_wp && is_eq_wp)
		return logical_less_fractional_part(l_val_, r_val_);
	return is_ls_wp;
}

bool BigReal::logical_less_whole_part(BigReal l_val_, BigReal r_val_)
{
	if (l_val_.amount_places_whole_part() > r_val_.amount_places_whole_part())
		return false;
	if (l_val_.amount_places_whole_part() < r_val_.amount_places_whole_part())
		return true;
	bool is_less = false;
	std::size_t r_i = l_val_.amount_places_whole_part() - 1U;
	for (std::size_t i = 0U; i < l_val_.amount_places_whole_part(); ++i, --r_i)
		if (l_val_.b_whole_part[r_i] < r_val_.b_whole_part[r_i])
			is_less = true;
		else if (l_val_.b_whole_part[r_i] > r_val_.b_whole_part[r_i])
			is_less = false;
	return is_less;
}

bool BigReal::logical_less_fractional_part(BigReal l_val_, BigReal r_val_)
{
	std::string l_val_fp = l_val_.to_string_fractional_part();
	std::string r_val_fp = r_val_.to_string_fractional_part();
	std::size_t gen_ap_wp = (l_val_fp.length() >= r_val_fp.length()) ?
		l_val_fp.length() : r_val_fp.length();
	append_end_zeros_by_general_size(l_val_fp, r_val_fp);
	bool is_less = false;
	std::size_t r_i = gen_ap_wp - 1U;
	for (std::size_t i = 0U; i < gen_ap_wp; ++i, --r_i)
		if (l_val_fp[r_i] < r_val_fp[r_i])
			is_less = true;
		else if (l_val_fp[r_i] > r_val_fp[r_i])
			is_less = false;
	return is_less;
}


// ----------------------------------------------------------------------------
// more/less or equal
bool BigReal::operator>=(std::int32_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator>=(std::size_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator>=(std::int64_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator>=(std::uint64_t r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator>=(const BigInt& r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator>=(float r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator>=(double r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator>=(const BigReal& r_val_) const
{
	return !operator<(r_val_);
}

bool BigReal::operator<=(std::int32_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigReal::operator<=(std::size_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigReal::operator<=(std::int64_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigReal::operator<=(std::uint64_t r_val_) const
{
	return !operator>(r_val_);
}

bool BigReal::operator<=(const BigInt& r_val_) const
{
	return !operator>(r_val_);
}

bool BigReal::operator<=(float r_val_) const
{
	return !operator>(r_val_);
}

bool BigReal::operator<=(double r_val_) const
{
	return !operator>(r_val_);
}

bool BigReal::operator<=(const BigReal& r_val_) const
{
	return !operator>(r_val_);
}


// ----------------------------------------------------------------------------
// equal
bool BigReal::operator==(std::int32_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator==(r_val);
}

bool BigReal::operator==(std::size_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator==(r_val);
}

bool BigReal::operator==(std::int64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator==(r_val);
}

bool BigReal::operator==(std::uint64_t r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator==(r_val);
}

bool BigReal::operator==(const BigInt& r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator==(r_val);
}

bool BigReal::operator==(float r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator==(r_val);
}

bool BigReal::operator==(double r_val_) const
{
	BigReal r_val = to_big_real(r_val_);
	return operator==(r_val);
}

bool BigReal::operator==(const BigReal& r_val_) const
{
	bool is_neg_l = b_is_neg;
	bool is_neg_r = r_val_.b_is_neg;
	if (is_neg_l && !is_neg_r)
		return false;
	if (!is_neg_l && is_neg_r)
		return false;
	return logical_equal(*this, r_val_);
}

bool BigReal::logical_equal(const BigReal& l_val_, const BigReal& r_val_) // positive
{
	bool eq_wp = logical_equal_whole_part(l_val_, r_val_);
	bool eq_fp = logical_equal_fractional_part(l_val_, r_val_);
	return eq_wp && eq_fp;
}

bool BigReal::logical_equal_whole_part(const BigReal& l_val_, const BigReal& r_val_)
{
	if (l_val_.amount_places_whole_part() != r_val_.amount_places_whole_part())
		return false;
	bool is_equal = true;
	std::size_t r_i = l_val_.b_whole_part.size() - 1U;
	for (std::size_t i = 0U; is_equal && i < l_val_.b_whole_part.size(); ++i, --r_i)
		if (l_val_.b_whole_part[r_i] != r_val_.b_whole_part[r_i])
			is_equal = false;
	return is_equal;
}

bool BigReal::logical_equal_fractional_part(const BigReal& l_val_, const BigReal& r_val_)
{
	if (l_val_.amount_places_fractional_part() != r_val_.amount_places_fractional_part())
		return false;
	bool is_equal = true;
	std::size_t r_i = l_val_.b_fractional_part.size() - 1U;
	for (std::size_t i = 0U; is_equal && i < l_val_.b_fractional_part.size(); ++i, --r_i)
		if (l_val_.b_fractional_part[r_i] != r_val_.b_fractional_part[r_i])
			is_equal = false;
	return is_equal;
}

bool BigReal::operator!=(std::int32_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigReal::operator!=(std::size_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigReal::operator!=(std::int64_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigReal::operator!=(std::uint64_t r_val_) const
{
	return !operator==(r_val_);
}

bool BigReal::operator!=(const BigInt& r_val_) const
{
	return !operator==(r_val_);
}

bool BigReal::operator!=(float r_val_) const
{
	return !operator==(r_val_);
}

bool BigReal::operator!=(double r_val_) const
{
	return !operator==(r_val_);
}

bool BigReal::operator!=(const BigReal& r_val_) const
{
	return !operator==(r_val_);
}


// ----------------------------------------------------------------------------
// friendly comparisons
bool operator>(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>(r_val_);
}

bool operator>(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>(r_val_);
}

bool operator>(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>(r_val_);
}

bool operator>(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>(r_val_);
}

bool operator>(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>(r_val_);
}

bool operator>(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>(r_val_);
}

bool operator>(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>(r_val_);
}

bool operator<(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<(r_val_);
}

bool operator<(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<(r_val_);
}

bool operator<(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<(r_val_);
}

bool operator<(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<(r_val_);
}

bool operator<(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<(r_val_);
}

bool operator<(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<(r_val_);
}

bool operator<(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<(r_val_);
}

bool operator>=(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>=(r_val_);
}

bool operator>=(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>=(r_val_);
}

bool operator>=(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>=(r_val_);
}

bool operator>=(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>=(r_val_);
}

bool operator>=(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>=(r_val_);
}

bool operator>=(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>=(r_val_);
}

bool operator>=(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator>=(r_val_);
}

bool operator<=(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<=(r_val_);
}

bool operator<=(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<=(r_val_);
}

bool operator<=(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<=(r_val_);
}

bool operator<=(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<=(r_val_);
}

bool operator<=(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<=(r_val_);
}

bool operator<=(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<=(r_val_);
}

bool operator<=(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator<=(r_val_);
}

bool operator==(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator==(r_val_);
}

bool operator==(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator==(r_val_);
}

bool operator==(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator==(r_val_);
}

bool operator==(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator==(r_val_);
}

bool operator==(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator==(r_val_);
}

bool operator==(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator==(r_val_);
}

bool operator==(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator==(r_val_);
}

bool operator!=(std::int32_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator!=(r_val_);
}

bool operator!=(std::size_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator!=(r_val_);
}

bool operator!=(std::int64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator!=(r_val_);
}

bool operator!=(std::uint64_t l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator!=(r_val_);
}

bool operator!=(const BigInt& l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator!=(r_val_);
}

bool operator!=(float l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator!=(r_val_);
}

bool operator!=(double l_val_, const BigReal& r_val_)
{
	BigReal l_val = BigReal::to_big_real(l_val_);
	return l_val.operator!=(r_val_);
}


// ----------------------------------------------------------------------------
// amount digits after comma
std::size_t BigReal::get_amount_digits_after_comma() const
{
	return b_am_dig_after_com;
}

void BigReal::set_amount_digits_after_comma(std::size_t am_dig_after_com_)
{
	b_am_dig_after_com = am_dig_after_com_;
}


// ----------------------------------------------------------------------------
// stream
std::istream& BigReal::operator>>(std::istream& stream_)
{
	// idea
	std::string str;
	std::size_t st_p = 0U;
	char if_there_is_sign_then_it_is_sign = static_cast<char>(0);
	stream_ >> str;
	if (str[0] == '-' || str[0] == '+')
	{
		st_p = 1U;
		if_there_is_sign_then_it_is_sign = str[0];
	}
	*this = read_big_real(str, st_p);
	if (if_there_is_sign_then_it_is_sign == '-')
		b_is_neg = !is_zero();
	return stream_;
}

BigReal BigReal::read_big_real(const std::string& str_, std::size_t st_p_)
{
	BigReal br;
	std::size_t last_digit_wp_p = st_p_;
	bool is_comma = false;
	for (; last_digit_wp_p < str_.length(); ++last_digit_wp_p)
		if (str_[last_digit_wp_p] < '0' || str_[last_digit_wp_p] > '9')
			break;
	if (st_p_ == last_digit_wp_p && str_[last_digit_wp_p] != '.')
		return br; // default
	if (str_[last_digit_wp_p] != '.') // st_p_ != last_digit_p, only whole
	{
		br.b_whole_part.clear();
		br.b_whole_part.reserve(last_digit_wp_p - st_p_ + 1U);
		for (std::size_t i = st_p_; i < last_digit_wp_p; ++i)
			br.b_whole_part.push_back(static_cast<std::int8_t>(str_[i] - '0'));
		remove_leading_zeros_from_whole_part(br); // ref
		return br;
	}
	if (st_p_ != last_digit_wp_p) // str_[last_digit_p] == '.'
	{
		br.b_whole_part.clear();
		br.b_whole_part.reserve(last_digit_wp_p - st_p_ + 1U);
		for (std::size_t i = st_p_; i < last_digit_wp_p; ++i)
			br.b_whole_part.push_back(static_cast<std::int8_t>(str_[i] - '0'));
		remove_leading_zeros_from_whole_part(br);
	}
	// st_p_ == last_digit_p
	++last_digit_wp_p; // skip comma
	std::size_t last_digit_fp_p = last_digit_wp_p;
	for (; last_digit_fp_p < str_.length(); ++last_digit_fp_p)
		if (str_[last_digit_fp_p] < '0' || str_[last_digit_fp_p] > '9')
			break;
	br.b_fractional_part.clear();
	br.b_fractional_part.reserve(last_digit_fp_p - last_digit_wp_p + 1U);
	for (std::size_t i = last_digit_wp_p; i < last_digit_fp_p; ++i)
		br.b_fractional_part.push_back(static_cast<std::int8_t>(str_[i] - '0')); // cp
	remove_end_zeros_from_fractional_part(br);
	return br;
}

std::ostream& BigReal::operator<<(std::ostream& stream_) const
{
	stream_ << to_string();
	return stream_;
}

std::string BigReal::to_string() const
{
	std::stringstream ss;
	if (b_is_neg)
		ss << '-';
	for (std::size_t i = 0; i < b_whole_part.size(); ++i)
		ss << static_cast<std::int32_t>(b_whole_part[i]);
	if (b_fractional_part.empty())
		return ss.str();
	if (b_am_dig_after_com != 0U) // limit
	{
		ss << '.';
		for (std::size_t i = 0; i < b_am_dig_after_com && i < b_fractional_part.size(); ++i)
			ss << static_cast<std::int32_t>(b_fractional_part[i]);
	}
	return ss.str();
}

std::string BigReal::to_string_unsigned() const
{
	std::stringstream ss;
	for (std::size_t i = 0; i < b_whole_part.size(); ++i)
		ss << static_cast<std::int32_t>(b_whole_part[i]);
	if (b_fractional_part.empty())
		return ss.str();
	if (b_am_dig_after_com != 0U)
	{
		ss << '.';
		for (std::size_t i = 0; i < b_am_dig_after_com && i < b_fractional_part.size(); ++i)
			ss << static_cast<std::int32_t>(b_fractional_part[i]);
	}
	return ss.str();
}

std::string BigReal::to_string_whole_part() const
{
	std::stringstream ss;
	if (b_is_neg)
		ss << '-';
	for (std::size_t i = 0; i < b_whole_part.size(); ++i)
		ss << static_cast<std::int32_t>(b_whole_part[i]);
	return ss.str();
}

std::string BigReal::to_string_unsigned_whole_part() const
{
	std::stringstream ss;
	for (std::size_t i = 0; i < b_whole_part.size(); ++i)
		ss << static_cast<std::int32_t>(b_whole_part[i]);
	return ss.str();
}

std::string BigReal::to_string_fractional_part() const
{
	std::stringstream ss;
	for (std::size_t i = 0;  i < b_am_dig_after_com && i < b_fractional_part.size(); ++i)
		ss << static_cast<std::int32_t>(b_fractional_part[i]);
	return ss.str();
}

std::istream& operator>>(std::istream& stream_, BigReal& bi_)
{
	return bi_.operator>>(stream_);
}

std::ostream& operator<<(std::ostream& stream_, const BigReal& bi_)
{
	return bi_.operator<<(stream_);
}


// ----------------------------------------------------------------------------
// to big real from str
BigReal BigReal::to_big_real(const std::string& str_)
{
	BigReal br;
	to_big_real(br, str_);
	return br;
}

void BigReal::to_big_real(BigReal &br_, const std::string& str_) // without check
{
	if (str_.empty())
	{
		br_ = BigReal();
		return;
	}
	std::size_t offset = 0U;
	if (str_.front() == '-')
	{
		br_.b_is_neg = true;
		++offset;
	}
	std::size_t pos_com = str_.length();
	std::size_t pos_after_com = str_.length();
	for (std::size_t i = offset; i < str_.length(); ++i)
	{
		if (str_[i] == '.')
		{
			pos_com = i;
			pos_after_com = i + 1;
			break;
		}
	}
	// sign is already set
	to_big_real_whole_part(br_, str_.substr(offset, pos_com - offset));
	to_big_real_fractional_part(br_, str_.substr(pos_after_com)); // if is (min value zero)
}

void BigReal::to_big_real_whole_part(BigReal &br_, std::string str_) // only positive str (without check)
{
	if (str_.empty())
		str_ = "0";
	remove_leading_zeros(str_);
	br_.b_whole_part.clear();
	br_.b_whole_part.reserve(str_.length());
	for (std::size_t i = 0U; i < str_.length(); ++i)
		br_.b_whole_part.push_back(str_[i] - static_cast<std::int8_t>(48));
}

void BigReal::to_big_real_fractional_part(BigReal &br_, std::string str_)
{
	if (str_.empty())
		str_ = "0"; // min value
	remove_end_zeros(str_);
	br_.b_fractional_part.clear();
	br_.b_fractional_part.reserve(str_.length());
	for (std::size_t i = 0U; i < str_.length(); ++i)
		br_.b_fractional_part.push_back(str_[i] - static_cast<std::int8_t>(48));
}


// ----------------------------------------------------------------------------
// help
void BigReal::append_leading_zeros(std::string& str_, std::size_t size_)
{
	if (str_.empty())
	{
		str_.insert(0U, size_, '0');
		return;
	}
	std::size_t offset = (str_.front() == '-') ? 1U : 0U;
	str_.insert(offset, size_, '0');
}

void BigReal::append_leading_zeros_by_size(std::string& str_, std::size_t size_)
{
	if (str_.empty())
	{
		str_.insert(0U, size_, '0');
		return;
	}
	std::size_t offset = (str_.front() == '-') ? 1U : 0U;
	if (str_.length() - offset >= size_)
		return;
	str_.insert(offset, size_ - str_.length() + offset, '0');
}

void BigReal::append_leading_zeros_by_general_size(std::string& l_val_, std::string& r_val_)
{
	if (l_val_.empty() && r_val_.empty())
		return;
	std::size_t l_size = l_val_.size(); // only numbers
	std::size_t r_size = r_val_.size();
	if (l_val_.empty())
	{
		if (r_val_.front() == '-')
			--r_size;
		l_val_.insert(0U, r_size, '0');
		return;
	}
	if (r_val_.empty())
	{
		if (l_val_.front() == '-')
			--l_size;
		r_val_.insert(0U, l_size, '0');
		return;
	}
	if (r_val_.front() == '-')
		--r_size;
	if (l_val_.front() == '-')
		--l_size;
	std::size_t general_size = std::max(l_size, r_size);
	append_leading_zeros_by_size(l_val_, general_size);
	append_leading_zeros_by_size(r_val_, general_size);
}

void BigReal::remove_leading_zeros(std::string& str_)
{
	if (str_.empty())
		return;
	std::size_t offset = (str_.front() == '-') ? 1U : 0U;
	while (str_.length() > 1U + offset && str_[offset] == '0')
		str_.erase(offset, 1U);
}

void BigReal::remove_leading_zeros_from_whole_part(BigReal& val_)
{
	while (val_.b_whole_part.size() > 1U && val_.b_whole_part.front() == static_cast<std::int8_t>(0))
		val_.b_whole_part.erase(val_.b_whole_part.begin());
}

void BigReal::append_end_zeros(std::string& str_, std::size_t size_)
{
	str_.insert(str_.length(), size_, '0');
}

void BigReal::append_end_zeros_by_size(std::string& str_, std::size_t size_) // without check
{
	// consider only numbers
	if (str_.empty())
	{
		str_.insert(0U, size_, '0');
		return;
	}
	std::size_t offset = (str_.front() == '-') ? 1U : 0U;
	if (str_.length() - offset >= size_)
		return;
	str_.insert(str_.length(), size_ - str_.length() + offset, '0');
}

void BigReal::append_end_zeros_by_general_size(std::string& l_val_, std::string& r_val_)
{
	if (l_val_.empty() && r_val_.empty())
		return;
	std::size_t l_size = l_val_.size(); // only numbers
	std::size_t r_size = r_val_.size();
	if (l_val_.empty())
	{
		if (r_val_.front() == '-')
			--r_size;
		l_val_.insert(0U, r_size, '0');
		return;
	}
	if (r_val_.empty())
	{
		if (l_val_.front() == '-')
			--l_size;
		r_val_.insert(0U, l_size, '0');
		return;
	}
	if (r_val_.front() == '-')
		--r_size;
	if (l_val_.front() == '-')
		--l_size;
	std::size_t general_size = std::max(l_size, r_size);
	append_end_zeros_by_size(l_val_, general_size);
	append_end_zeros_by_size(r_val_, general_size);
}

void BigReal::append_end_zeros_by_general_size(BigInt& l_val_, BigInt& r_val_)
{
	std::string l_val = l_val_.to_string();
	std::string r_val = r_val_.to_string();
	append_end_zeros_by_general_size(l_val, r_val);
	l_val_ = BigInt::to_big_int(l_val);
	r_val_ = BigInt::to_big_int(r_val);
}

void BigReal::remove_end_zeros(std::string& str_)
{
	if (str_.empty())
		return;
	std::size_t offset = (str_.front() == '-') ? 1U : 0U;
	while (str_.length() > 1U + offset && str_.back() == '0')
		str_.pop_back();
}

void BigReal::remove_end_zeros_from_fractional_part(BigReal& val_)
{
	while (val_.b_fractional_part.size() > 1U && val_.b_fractional_part.back() == static_cast<std::int8_t>(0))
		val_.b_fractional_part.pop_back();
}


// ----------------------------------------------------------------------------
// to big real
BigReal BigReal::to_big_real(std::int32_t val_)
{
	BigReal br;
	to_big_real(br, std::to_string(val_));
	return br;
}

BigReal BigReal::to_big_real(std::size_t val_)
{
	BigReal br;
	to_big_real(br, std::to_string(val_));
	return br;
}

BigReal BigReal::to_big_real(std::int64_t val_)
{
	BigReal br;
	to_big_real(br, std::to_string(val_));
	return br;
}

BigReal BigReal::to_big_real(std::uint64_t val_) // only whole
{
	BigReal br;
	to_big_real(br, std::to_string(val_));
	return br;
}

BigReal BigReal::to_big_real(const BigInt& val_)
{
	BigReal br;
	to_big_real(br, val_.to_string());
	return br;
}

BigReal BigReal::to_big_real(float val_)
{
	BigReal br;
	to_big_real(br, std::to_string(val_));
	return br;
}

BigReal BigReal::to_big_real(double val_)
{
	BigReal br;
	to_big_real(br, std::to_string(val_));
	return br;
}

void BigReal::swap(BigReal& l_val_, BigReal& r_val_)
{
	using std::swap;
	swap(l_val_.b_whole_part, r_val_.b_whole_part);
	swap(l_val_.b_fractional_part, r_val_.b_fractional_part);
	swap(l_val_.b_am_dig_after_com, r_val_.b_am_dig_after_com);
	swap(l_val_.b_is_neg, r_val_.b_is_neg);
}

std::size_t& BigReal::start_amount_digits_after_comma()
{
	static std::size_t start_am_dig_after_com = 25U;
	return start_am_dig_after_com;
}

BigReal::~BigReal()
{
}

} // end nmspc
