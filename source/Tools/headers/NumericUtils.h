#pragma once
#include <cstddef>

namespace svlTools
{
/**
 * explicitly converts size_t to an integer but
 * throws a overflow error is the value is greater than INT_MAX.
*/
int size_tToInt(size_t value);
}
