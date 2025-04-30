```r
Latest: 0.0.1 - 04/01/2025
Location: Core/Comparison.hpp
```


# Enumerations

## Lucy::Comparison

```cpp
namespace Lucy
{
	enum class [[nodiscard]] Comparison : unsigned char;
}
```

The resulting type of the *three-way* comparison.

### Enumerators

#### Equivalent

```cpp
Equivalent = 0u
```

The result of the comparison where both values are equivalent to each other. Equivalent to ``a == b``.


#### Lesser

```cpp
Lesser = 1u
```

The result of the comparison where the former's value is lesser than the latter's value. Equivalent to ``a < b``.


#### Greater

```cpp
Greater = 2u
```

The result of the comparison where the former's value is greater than the latter's value. Equivalent to ``a > b``.