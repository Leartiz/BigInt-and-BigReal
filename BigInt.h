#pragma once
/*
* /File: BigInt.h /
* /Brief: BigInt and BigReal
* /Creator: Leonid Artemev | Leartiz /
* /Date: 2020 /
*/

#include <vector>
#include <string>


namespace lez
{
	// division by zero is zero!

	class BigInt
	{
	public:
		BigInt();
		BigInt(const BigInt& val_);
		BigInt(BigInt&& val_);
		explicit BigInt(std::int32_t val_); // or implicit
		explicit BigInt(std::size_t val_);
		explicit BigInt(std::int64_t val_);
		explicit BigInt(std::uint64_t val_);

		BigInt& operator=(std::int32_t val_);
		BigInt& operator=(std::size_t val_);
		BigInt& operator=(std::int64_t val_);
		BigInt& operator=(std::uint64_t val_);
		BigInt& operator=(BigInt val_);

		std::int32_t to_int32() const;
		std::size_t to_size() const;
		std::int64_t to_int64() const;
		std::uint64_t to_uint64() const;

		std::size_t amount_places() const;
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

		const BigInt operator-() const;
		const BigInt operator+() const;

		BigInt& operator--();
		BigInt& operator++();

		const BigInt operator--(int);
		const BigInt operator++(int);

		const BigInt operator+(std::int32_t r_val_) const;
		const BigInt operator+(std::size_t r_val_) const;
		const BigInt operator+(std::int64_t r_val_) const;
		const BigInt operator+(std::uint64_t r_val_) const;
		const BigInt operator+(const BigInt& r_val_) const;

		const BigInt operator-(std::int32_t r_val_) const;
		const BigInt operator-(std::size_t r_val_) const;
		const BigInt operator-(std::int64_t r_val_) const;
		const BigInt operator-(std::uint64_t r_val_) const;
		const BigInt operator-(const BigInt& r_val_) const;

		BigInt& operator+=(std::int32_t r_val_);
		BigInt& operator+=(std::size_t r_val_);
		BigInt& operator+=(std::int64_t r_val_);
		BigInt& operator+=(std::uint64_t r_val_);
		BigInt& operator+=(const BigInt& r_val_);

		BigInt& operator-=(std::int32_t r_val_);
		BigInt& operator-=(std::size_t r_val_);
		BigInt& operator-=(std::int64_t r_val_);
		BigInt& operator-=(std::uint64_t r_val_);
		BigInt& operator-=(const BigInt& r_val_);

		friend const BigInt operator+(std::int32_t l_val_, const BigInt& r_val_);
		friend const BigInt operator+(std::size_t l_val_, const BigInt& r_val_);
		friend const BigInt operator+(std::int64_t l_val_, const BigInt& r_val_);
		friend const BigInt operator+(std::uint64_t l_val_, const BigInt& r_val_);

		friend const BigInt operator-(std::int32_t l_val_, const BigInt& r_val_);
		friend const BigInt operator-(std::size_t l_val_, const BigInt& r_val_);
		friend const BigInt operator-(std::int64_t l_val_, const BigInt& r_val_);
		friend const BigInt operator-(std::uint64_t l_val_, const BigInt& r_val_);

		const BigInt operator*(std::int32_t r_val_) const;
		const BigInt operator*(std::size_t r_val_) const;
		const BigInt operator*(std::int64_t r_val_) const;
		const BigInt operator*(std::uint64_t r_val_) const;
		const BigInt operator*(const BigInt& r_val_) const;

		const BigInt operator/(std::int32_t r_val_) const;
		const BigInt operator/(std::size_t r_val_) const;
		const BigInt operator/(std::int64_t r_val_) const;
		const BigInt operator/(std::uint64_t r_val_) const;
		const BigInt operator/(const BigInt& r_val_) const;

		const BigInt operator%(std::int32_t r_val_) const;
		const BigInt operator%(std::size_t r_val_) const;
		const BigInt operator%(std::int64_t r_val_) const;
		const BigInt operator%(std::uint64_t r_val_) const;
		const BigInt operator%(const BigInt& r_val_) const;

		BigInt& operator*=(std::int32_t r_val_);
		BigInt& operator*=(std::size_t r_val_);
		BigInt& operator*=(std::int64_t r_val_);
		BigInt& operator*=(std::uint64_t r_val_);
		BigInt& operator*=(const BigInt& r_val_);

		BigInt& operator/=(std::int32_t r_val_);
		BigInt& operator/=(std::size_t r_val_);
		BigInt& operator/=(std::int64_t r_val_);
		BigInt& operator/=(std::uint64_t r_val_);
		BigInt& operator/=(const BigInt& r_val_);

		BigInt& operator%=(std::int32_t r_val_);
		BigInt& operator%=(std::size_t r_val_);
		BigInt& operator%=(std::int64_t r_val_);
		BigInt& operator%=(std::uint64_t r_val_);
		BigInt& operator%=(const BigInt& r_val_);

		friend const BigInt operator*(std::int32_t l_val_, const BigInt& r_val_);
		friend const BigInt operator*(std::size_t l_val_, const BigInt& r_val_);
		friend const BigInt operator*(std::int64_t l_val_, const BigInt& r_val_);
		friend const BigInt operator*(std::uint64_t l_val_, const BigInt& r_val_);

		friend const BigInt operator/(std::int32_t l_val_, const BigInt& r_val_);
		friend const BigInt operator/(std::size_t l_val_, const BigInt& r_val_);
		friend const BigInt operator/(std::int64_t l_val_, const BigInt& r_val_);
		friend const BigInt operator/(std::uint64_t l_val_, const BigInt& r_val_);

		friend const BigInt operator%(std::int32_t l_val_, const BigInt& r_val_);
		friend const BigInt operator%(std::size_t l_val_, const BigInt& r_val_);
		friend const BigInt operator%(std::int64_t l_val_, const BigInt& r_val_);
		friend const BigInt operator%(std::uint64_t l_val_, const BigInt& r_val_);

		bool operator>(std::int32_t r_val_) const;
		bool operator>(std::size_t r_val_) const;
		bool operator>(std::int64_t r_val_) const;
		bool operator>(std::uint64_t r_val_) const;
		bool operator>(const BigInt& r_val_) const;

		bool operator<(std::int32_t r_val_) const;
		bool operator<(std::size_t r_val_) const;
		bool operator<(std::int64_t r_val_) const;
		bool operator<(std::uint64_t r_val_) const;
		bool operator<(const BigInt& r_val_) const;

		bool operator>=(std::int32_t r_val_) const;
		bool operator>=(std::size_t r_val_) const;
		bool operator>=(std::int64_t r_val_) const;
		bool operator>=(std::uint64_t r_val_) const;
		bool operator>=(const BigInt& r_val_) const;

		bool operator<=(std::int32_t r_val_) const;
		bool operator<=(std::size_t r_val_) const;
		bool operator<=(std::int64_t r_val_) const;
		bool operator<=(std::uint64_t r_val_) const;
		bool operator<=(const BigInt& r_val_) const;

		bool operator==(std::int32_t r_val_) const;
		bool operator==(std::size_t r_val_) const;
		bool operator==(std::int64_t r_val_) const;
		bool operator==(std::uint64_t r_val_) const;
		bool operator==(const BigInt& r_val_) const;

		bool operator!=(std::int32_t r_val_) const;
		bool operator!=(std::size_t r_val_) const;
		bool operator!=(std::int64_t r_val_) const;
		bool operator!=(std::uint64_t r_val_) const;
		bool operator!=(const BigInt& r_val_) const;

		friend bool operator>(std::int32_t l_val_, const BigInt& r_val_);
		friend bool operator>(std::size_t l_val_, const BigInt& r_val_);
		friend bool operator>(std::int64_t l_val_, const BigInt& r_val_);
		friend bool operator>(std::uint64_t l_val_, const BigInt& r_val_);

		friend bool operator<(std::int32_t l_val_, const BigInt& r_val_);
		friend bool operator<(std::size_t l_val_, const BigInt& r_val_);
		friend bool operator<(std::int64_t l_val_, const BigInt& r_val_);
		friend bool operator<(std::uint64_t l_val_, const BigInt& r_val_);

		friend bool operator>=(std::int32_t l_val_, const BigInt& r_val_);
		friend bool operator>=(std::size_t l_val_, const BigInt& r_val_);
		friend bool operator>=(std::int64_t l_val_, const BigInt& r_val_);
		friend bool operator>=(std::uint64_t l_val_, const BigInt& r_val_);

		friend bool operator<=(std::int32_t l_val_, const BigInt& r_val_);
		friend bool operator<=(std::size_t l_val_, const BigInt& r_val_);
		friend bool operator<=(std::int64_t l_val_, const BigInt& r_val_);
		friend bool operator<=(std::uint64_t l_val_, const BigInt& r_val_);

		friend bool operator==(std::int32_t l_val_, const BigInt& r_val_);
		friend bool operator==(std::size_t l_val_, const BigInt& r_val_);
		friend bool operator==(std::int64_t l_val_, const BigInt& r_val_);
		friend bool operator==(std::uint64_t l_val_, const BigInt& r_val_);

		friend bool operator!=(std::int32_t l_val_, const BigInt& r_val_);
		friend bool operator!=(std::size_t l_val_, const BigInt& r_val_);
		friend bool operator!=(std::int64_t l_val_, const BigInt& r_val_);
		friend bool operator!=(std::uint64_t l_val_, const BigInt& r_val_);

		std::istream& operator>>(std::istream& stream_);
		std::ostream& operator<<(std::ostream& stream_) const;
		std::string to_string() const;
		std::string to_string_unsigned() const;

		friend std::istream& operator>>(std::istream& stream_, BigInt& bi_);
		friend std::ostream& operator<<(std::ostream& stream_, const BigInt& bi_);

		static BigInt to_big_int(std::int32_t val_);
		static BigInt to_big_int(std::size_t val_);
		static BigInt to_big_int(std::int64_t val_);
		static BigInt to_big_int(std::uint64_t val_);
		static BigInt to_big_int(const std::string& str_);
		static void to_big_int(BigInt& bi_, const std::string& str_); // spec

		static void swap(BigInt& l_val_, BigInt& r_val_);

		// extra (use in BigReal)
		static BigInt addition_without_remove_leading_zeros(BigInt l_val_, BigInt r_val_);
		static BigInt subtraction_without_remove_leading_zeros(BigInt l_val_, BigInt r_val_);

		~BigInt();

	private:

		static BigInt append_leading_zeros(BigInt val_, std::size_t size_);
		static BigInt remove_leading_zeros(BigInt val_);

		static BigInt addition(BigInt l_val_, BigInt r_val_);
		static BigInt subtraction(BigInt l_val_, BigInt r_val_); // more - less

		static BigInt multiplication(BigInt l_val_, BigInt r_val_); // more * less 
		static BigInt simple_multiplication(BigInt val_, std::int32_t counter_);

		static BigInt division(BigInt l_val_, BigInt r_val_); // more / less
		static std::int32_t simple_division(BigInt& val_, const BigInt& subthd_);

		static BigInt modulo_division(BigInt l_val_, BigInt r_val_); // more % less

		// unsigned (can be simplified)
		static bool logical_more(BigInt l_val_, BigInt r_val_);
		static bool logical_less(BigInt l_val_, BigInt r_val_);
		// unsigned, same sizes
		static bool logical_equal(BigInt l_val_, BigInt r_val_);
		// from str
		static BigInt read_big_int(const std::string& str_, std::size_t st_p_);

		std::vector<std::int8_t> b_num_vec;
		bool b_is_neg;
	};
}
