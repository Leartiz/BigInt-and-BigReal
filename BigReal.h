#pragma once
/*
* /File: BigReal.h /
* /Brief: BigInt and BigReal
* /Creator: Leonid Artemev | Leartiz /
* /Date: 2020 /
*/

#include <vector>
#include <string>

#include "BigInt.h"


namespace lez
{
	// start_amount_digits_after_comma() edit for all class

	// division by zero is zero!
	class BigReal
	{
	public:
		BigReal();
		BigReal(const BigReal& val_);
		BigReal(BigReal&& val_);
		explicit BigReal(std::int32_t val_); // or implicit
		explicit BigReal(std::size_t val_);
		explicit BigReal(std::int64_t val_);
		explicit BigReal(std::uint64_t val_);
		explicit BigReal(const BigInt& val_);
		explicit BigReal(float val_);
		explicit BigReal(double val_);

		BigReal& operator=(std::int32_t val_);
		BigReal& operator=(std::size_t val_);
		BigReal& operator=(std::int64_t val_);
		BigReal& operator=(std::uint64_t val_);
		BigReal& operator=(const BigInt& val_);
		BigReal& operator=(float val_);
		BigReal& operator=(double val_);
		BigReal& operator=(BigReal val_);

		std::int32_t to_int32() const;
		std::size_t to_size() const;
		std::int64_t to_int64() const;
		std::uint64_t to_uint64() const;
		BigInt to_big_int() const;
		float to_float() const;
		double to_double() const;

		std::size_t amount_places() const; // only numbers
		std::size_t amount_places_whole_part() const;
		std::size_t amount_places_fractional_part() const;
		bool is_neg() const;
		bool is_zero() const;
		void reverse_neg();
		void set_neg();
		void reset_neg();
		void reset();

		explicit operator bool() const;
		explicit operator std::int32_t() const;
		explicit operator std::size_t() const;
		explicit operator std::int64_t() const;
		explicit operator std::uint64_t() const;
		explicit operator BigInt() const;
		explicit operator float() const;
		explicit operator double() const;

		const BigReal operator-() const;
		const BigReal operator+() const;

		BigReal& operator--();
		BigReal& operator++();

		const BigReal operator--(int);
		const BigReal operator++(int);

		const BigReal operator+(std::int32_t r_val_) const;
		const BigReal operator+(std::size_t r_val_) const;
		const BigReal operator+(std::int64_t r_val_) const;
		const BigReal operator+(std::uint64_t r_val_) const;
		const BigReal operator+(const BigInt& r_val_) const;
		const BigReal operator+(float r_val_) const;
		const BigReal operator+(double r_val_) const;
		const BigReal operator+(const BigReal& r_val_) const;

		const BigReal operator-(std::int32_t r_val_) const;
		const BigReal operator-(std::size_t r_val_) const;
		const BigReal operator-(std::int64_t r_val_) const;
		const BigReal operator-(std::uint64_t r_val_) const;
		const BigReal operator-(const BigInt& r_val_) const;
		const BigReal operator-(float r_val_) const;
		const BigReal operator-(double r_val_) const;
		const BigReal operator-(const BigReal& r_val_) const;

		BigReal& operator+=(std::int32_t r_val_);
		BigReal& operator+=(std::size_t r_val_);
		BigReal& operator+=(std::int64_t r_val_);
		BigReal& operator+=(std::uint64_t r_val_);
		BigReal& operator+=(const BigInt& r_val_);
		BigReal& operator+=(float r_val_);
		BigReal& operator+=(double r_val_);
		BigReal& operator+=(const BigReal& r_val_);

		BigReal& operator-=(std::int32_t r_val_);
		BigReal& operator-=(std::size_t r_val_);
		BigReal& operator-=(std::int64_t r_val_);
		BigReal& operator-=(std::uint64_t r_val_);
		BigReal& operator-=(const BigInt& r_val_);
		BigReal& operator-=(float r_val_);
		BigReal& operator-=(double r_val_);
		BigReal& operator-=(const BigReal& r_val_);

		friend const BigReal operator+(std::int32_t l_val_, const BigReal& r_val_);
		friend const BigReal operator+(std::size_t l_val_, const BigReal& r_val_);
		friend const BigReal operator+(std::int64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator+(std::uint64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator+(const BigInt& l_val_, const BigReal& r_val_);
		friend const BigReal operator+(float l_val_, const BigReal& r_val_);
		friend const BigReal operator+(double l_val_, const BigReal& r_val_);

		friend const BigReal operator-(std::int32_t l_val_, const BigReal& r_val_);
		friend const BigReal operator-(std::size_t l_val_, const BigReal& r_val_);
		friend const BigReal operator-(std::int64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator-(std::uint64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator-(const BigInt& l_val_, const BigReal& r_val_);
		friend const BigReal operator-(float l_val_, const BigReal& r_val_);
		friend const BigReal operator-(double l_val_, const BigReal& r_val_);

		const BigReal operator*(std::int32_t r_val_) const;
		const BigReal operator*(std::size_t r_val_) const;
		const BigReal operator*(std::int64_t r_val_) const;
		const BigReal operator*(std::uint64_t r_val_) const;
		const BigReal operator*(const BigInt& r_val_) const;
		const BigReal operator*(float r_val_) const;
		const BigReal operator*(double r_val_) const;
		const BigReal operator*(const BigReal& r_val_) const;

		const BigReal operator/(std::int32_t r_val_) const;
		const BigReal operator/(std::size_t r_val_) const;
		const BigReal operator/(std::int64_t r_val_) const;
		const BigReal operator/(std::uint64_t r_val_) const;
		const BigReal operator/(const BigInt& r_val_) const;
		const BigReal operator/(float r_val_) const;
		const BigReal operator/(double r_val_) const;
		const BigReal operator/(const BigReal& r_val_) const;

		const BigReal operator%(std::int32_t r_val_) const;
		const BigReal operator%(std::size_t r_val_) const;
		const BigReal operator%(std::int64_t r_val_) const;
		const BigReal operator%(std::uint64_t r_val_) const;
		const BigReal operator%(const BigInt& r_val_) const;
		const BigReal operator%(float r_val_) const;
		const BigReal operator%(double r_val_) const;
		const BigReal operator%(const BigReal& r_val_) const;

		BigReal& operator*=(std::int32_t r_val_);
		BigReal& operator*=(std::size_t r_val_);
		BigReal& operator*=(std::int64_t r_val_);
		BigReal& operator*=(std::uint64_t r_val_);
		BigReal& operator*=(const BigInt& r_val_);
		BigReal& operator*=(float r_val_);
		BigReal& operator*=(double r_val_);
		BigReal& operator*=(const BigReal& r_val_);

		BigReal& operator/=(std::int32_t r_val_);
		BigReal& operator/=(std::size_t r_val_);
		BigReal& operator/=(std::int64_t r_val_);
		BigReal& operator/=(std::uint64_t r_val_);
		BigReal& operator/=(const BigInt& r_val_);
		BigReal& operator/=(float r_val_);
		BigReal& operator/=(double r_val_);
		BigReal& operator/=(const BigReal& r_val_);

		BigReal& operator%=(std::int32_t r_val_);
		BigReal& operator%=(std::size_t r_val_);
		BigReal& operator%=(std::int64_t r_val_);
		BigReal& operator%=(std::uint64_t r_val_);
		BigReal& operator%=(const BigInt& r_val_);
		BigReal& operator%=(float r_val_);
		BigReal& operator%=(double r_val_);
		BigReal& operator%=(const BigReal& r_val_);

		friend const BigReal operator*(std::int32_t l_val_, const BigReal& r_val_);
		friend const BigReal operator*(std::size_t l_val_, const BigReal& r_val_);
		friend const BigReal operator*(std::int64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator*(std::uint64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator*(const BigInt& l_val_, const BigReal& r_val_);
		friend const BigReal operator*(float l_val_, const BigReal& r_val_);
		friend const BigReal operator*(double l_val_, const BigReal& r_val_);

		friend const BigReal operator/(std::int32_t l_val_, const BigReal& r_val_);
		friend const BigReal operator/(std::size_t l_val_, const BigReal& r_val_);
		friend const BigReal operator/(std::int64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator/(std::uint64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator/(const BigInt& l_val_, const BigReal& r_val_);
		friend const BigReal operator/(float l_val_, const BigReal& r_val_);
		friend const BigReal operator/(double l_val_, const BigReal& r_val_);

		friend const BigReal operator%(std::int32_t l_val_, const BigReal& r_val_);
		friend const BigReal operator%(std::size_t l_val_, const BigReal& r_val_);
		friend const BigReal operator%(std::int64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator%(std::uint64_t l_val_, const BigReal& r_val_);
		friend const BigReal operator%(const BigInt& l_val_, const BigReal& r_val_);
		friend const BigReal operator%(float l_val_, const BigReal& r_val_);
		friend const BigReal operator%(double l_val_, const BigReal& r_val_);

		bool operator>(std::int32_t r_val_) const;
		bool operator>(std::size_t r_val_) const;
		bool operator>(std::int64_t r_val_) const;
		bool operator>(std::uint64_t r_val_) const;
		bool operator>(const BigInt& r_val_) const;
		bool operator>(float r_val_) const;
		bool operator>(double r_val_) const;
		bool operator>(const BigReal& r_val_) const;

		bool operator<(std::int32_t r_val_) const;
		bool operator<(std::size_t r_val_) const;
		bool operator<(std::int64_t r_val_) const;
		bool operator<(std::uint64_t r_val_) const;
		bool operator<(const BigInt& r_val_) const;
		bool operator<(float r_val_) const;
		bool operator<(double r_val_) const;
		bool operator<(const BigReal& r_val_) const;

		bool operator>=(std::int32_t r_val_) const;
		bool operator>=(std::size_t r_val_) const;
		bool operator>=(std::int64_t r_val_) const;
		bool operator>=(std::uint64_t r_val_) const;
		bool operator>=(const BigInt& r_val_) const;
		bool operator>=(float r_val_) const;
		bool operator>=(double r_val_) const;
		bool operator>=(const BigReal& r_val_) const;

		bool operator<=(std::int32_t r_val_) const;
		bool operator<=(std::size_t r_val_) const;
		bool operator<=(std::int64_t r_val_) const;
		bool operator<=(std::uint64_t r_val_) const;
		bool operator<=(const BigInt& r_val_) const;
		bool operator<=(float r_val_) const;
		bool operator<=(double r_val_) const;
		bool operator<=(const BigReal& r_val_) const;

		bool operator==(std::int32_t r_val_) const;
		bool operator==(std::size_t r_val_) const;
		bool operator==(std::int64_t r_val_) const;
		bool operator==(std::uint64_t r_val_) const;
		bool operator==(const BigInt& r_val_) const;
		bool operator==(float r_val_) const;
		bool operator==(double r_val_) const;
		bool operator==(const BigReal& r_val_) const;

		bool operator!=(std::int32_t r_val_) const;
		bool operator!=(std::size_t r_val_) const;
		bool operator!=(std::int64_t r_val_) const;
		bool operator!=(std::uint64_t r_val_) const;
		bool operator!=(const BigInt& r_val_) const;
		bool operator!=(float r_val_) const;
		bool operator!=(double r_val_) const;
		bool operator!=(const BigReal& r_val_) const;

		friend bool operator>(std::int32_t l_val_, const BigReal& r_val_);
		friend bool operator>(std::size_t l_val_, const BigReal& r_val_);
		friend bool operator>(std::int64_t l_val_, const BigReal& r_val_);
		friend bool operator>(std::uint64_t l_val_, const BigReal& r_val_);
		friend bool operator>(const BigInt& l_val_, const BigReal& r_val_);
		friend bool operator>(float l_val_, const BigReal& r_val_);
		friend bool operator>(double l_val_, const BigReal& r_val_);

		friend bool operator<(std::int32_t l_val_, const BigReal& r_val_);
		friend bool operator<(std::size_t l_val_, const BigReal& r_val_);
		friend bool operator<(std::int64_t l_val_, const BigReal& r_val_);
		friend bool operator<(std::uint64_t l_val_, const BigReal& r_val_);
		friend bool operator<(const BigInt& l_val_, const BigReal& r_val_);
		friend bool operator<(float l_val_, const BigReal& r_val_);
		friend bool operator<(double l_val_, const BigReal& r_val_);

		friend bool operator>=(std::int32_t l_val_, const BigReal& r_val_);
		friend bool operator>=(std::size_t l_val_, const BigReal& r_val_);
		friend bool operator>=(std::int64_t l_val_, const BigReal& r_val_);
		friend bool operator>=(std::uint64_t l_val_, const BigReal& r_val_);
		friend bool operator>=(const BigInt& l_val_, const BigReal& r_val_);
		friend bool operator>=(float l_val_, const BigReal& r_val_);
		friend bool operator>=(double l_val_, const BigReal& r_val_);

		friend bool operator<=(std::int32_t l_val_, const BigReal& r_val_);
		friend bool operator<=(std::size_t l_val_, const BigReal& r_val_);
		friend bool operator<=(std::int64_t l_val_, const BigReal& r_val_);
		friend bool operator<=(std::uint64_t l_val_, const BigReal& r_val_);
		friend bool operator<=(const BigInt& l_val_, const BigReal& r_val_);
		friend bool operator<=(float l_val_, const BigReal& r_val_);
		friend bool operator<=(double l_val_, const BigReal& r_val_);

		friend bool operator==(std::int32_t l_val_, const BigReal& r_val_);
		friend bool operator==(std::size_t l_val_, const BigReal& r_val_);
		friend bool operator==(std::int64_t l_val_, const BigReal& r_val_);
		friend bool operator==(std::uint64_t l_val_, const BigReal& r_val_);
		friend bool operator==(const BigInt& l_val_, const BigReal& r_val_);
		friend bool operator==(float l_val_, const BigReal& r_val_);
		friend bool operator==(double l_val_, const BigReal& r_val_);

		friend bool operator!=(std::int32_t l_val_, const BigReal& r_val_);
		friend bool operator!=(std::size_t l_val_, const BigReal& r_val_);
		friend bool operator!=(std::int64_t l_val_, const BigReal& r_val_);
		friend bool operator!=(std::uint64_t l_val_, const BigReal& r_val_);
		friend bool operator!=(const BigInt& l_val_, const BigReal& r_val_);
		friend bool operator!=(float l_val_, const BigReal& r_val_);
		friend bool operator!=(double l_val_, const BigReal& r_val_);

		std::size_t get_amount_digits_after_comma() const;
		void set_amount_digits_after_comma(std::size_t am_dig_after_com_);

		std::istream& operator>>(std::istream& stream_);
		std::ostream& operator<<(std::ostream& stream_) const;
		std::string to_string() const;
		std::string to_string_unsigned() const;
		std::string to_string_whole_part() const;
		std::string to_string_unsigned_whole_part() const;
		std::string to_string_fractional_part() const;

		friend std::istream& operator>>(std::istream& stream_, BigReal& bi_);
		friend std::ostream& operator<<(std::ostream& stream_, const BigReal& bi_);

		static BigReal to_big_real(std::int32_t val_);
		static BigReal to_big_real(std::size_t val_);
		static BigReal to_big_real(std::int64_t val_);
		static BigReal to_big_real(std::uint64_t val_);
		static BigReal to_big_real(const BigInt& val_);
		static BigReal to_big_real(float val_);
		static BigReal to_big_real(double val_);

		static void swap(BigReal& l_val_, BigReal& r_val_);
		static std::size_t& start_amount_digits_after_comma(); // lval, for all class, singleton?

		~BigReal();

	private:

		static void append_leading_zeros(std::string& str_, std::size_t size_);
		static void append_leading_zeros_by_size(std::string& str_, std::size_t size_);
		static void append_leading_zeros_by_general_size(std::string& l_val_, std::string& r_val_);
		static void remove_leading_zeros(std::string& str_);
		static void remove_leading_zeros_from_whole_part(BigReal& val_);

		static void append_end_zeros(std::string& str_, std::size_t size_);
		static void append_end_zeros_by_size(std::string& str_, std::size_t size_);
		static void append_end_zeros_by_general_size(std::string& l_val_, std::string& r_val_);
		static void append_end_zeros_by_general_size(BigInt& l_val_, BigInt& r_val_);
		static void remove_end_zeros(std::string& str_);
		static void remove_end_zeros_from_fractional_part(BigReal& val_);

		static BigReal to_big_real(const std::string& str_);
		static void to_big_real(BigReal &br_, const std::string& str_); // full
		static void to_big_real_whole_part(BigReal &br_, std::string str_); // edit whole part
		static void to_big_real_fractional_part(BigReal &br_, std::string str_); // edit fractional part
		static BigReal to_big_real_from_big_int(const BigInt& wp_val_, const BigInt& fp_val_); // only positive

		static bool is_carry_after_addition_fractional_part(const BigInt& l_val_,
			const BigInt& r_val_,
			const BigInt& res_);
		static BigInt remove_first_number_from_big_int(const BigInt& val_); // after carry
		static void set_comma_in_result_string_after_multiplication(std::string& res_str_, std::size_t offset_for_com_);

		static BigReal addition_positive_or_negative_numbers(const BigReal& l_val_, const BigReal& r_val_);
		static BigReal subtraction(const BigReal& l_val_, const BigReal& r_val_); // unsigned, l - r
		static BigReal subtraction_in_order(const BigReal& l_val_, const BigReal& r_val_); // more - less

		// unsigned
		static bool logical_more(const BigReal& l_val_, const BigReal& r_val_);
		static bool logical_more_whole_part(const BigReal& l_val_, const BigReal& r_val_);
		static bool logical_more_fractional_part(const BigReal& l_val_, const BigReal& r_val_);

		static bool logical_less(BigReal l_val_, BigReal r_val_);
		static bool logical_less_whole_part(BigReal l_val_, BigReal r_val_);
		static bool logical_less_fractional_part(BigReal l_val_, BigReal r_val_);

		static bool logical_equal(const BigReal& l_val_, const BigReal& r_val_);
		static bool logical_equal_whole_part(const BigReal& l_val_, const BigReal& r_val_);
		static bool logical_equal_fractional_part(const BigReal& l_val_, const BigReal& r_val_);

		// from str
		static BigReal read_big_real(const std::string& str_, std::size_t st_p_);

		std::vector<std::int8_t> b_whole_part;
		std::vector<std::int8_t> b_fractional_part;
		std::size_t b_am_dig_after_com; // for cout, division...
		bool b_is_neg;
	};
}
