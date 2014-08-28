/**
 * @brief Handy fuctions
 * @details Several handy things I was missing from std.
 *
 */
#include <cstdint>
#include <limits>
#include <string>
#include <vector>
#include <sstream>

namespace nonstd
{
/**
 * @brief Fast simple string hash (Bernstein?)
 * @details Compile-time hash. Src: http://stackoverflow.com/a/7869639 (with
 *changes)
 *
 * @param s string to hash
 * @param off used for obfucation compilers
 *
 * @return hash value of s
 */
constexpr unsigned int hash(const char *s, int off = 0)
{
	return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

/**
 * @brief Pack the string into an unsigned int
 * @details Compile-time hash. Using 7 bits (ascii) it packs 9 chars into a
 *uint64_t. Src: http://stackoverflow.com/a/7869639
 *
 * @param s string to hash
 * @param off used for obfucation compilers
 *
 * @return hash value of s
 */
template <class T = uint64_t, unsigned int Bits = 7>
constexpr T pack(const char *s, unsigned int off = 0)
{
	return (Bits * off >=
				std::numeric_limits<unsigned char>::digits * sizeof(T) ||
			!s[off])
			   ? 0
			   : (((T)s[off] << (Bits * off)) | pack<T, Bits>(s, off + 1));
}
/**
 * @brief Splits string into array
 * @details Splits (tokenize) string into tokens separed by delimiter.
 *
 * @param str string to tokenize
 * @param delim delimiter
 *
 * @return separed tokens
 */
std::vector<std::string> split(const std::string &str, char delim)
{
	// create stream from input
	std::stringstream ss(str);

	// tokens to return
	std::vector<std::string> tokens;

	std::string token;
	while (std::getline(ss, token, delim)) {
		tokens.push_back(token);
	}

	return tokens;
}
}