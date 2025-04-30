```r
Latest: 0.0.1 - 03/01/2025
Location: Core/Address.hpp
```


# Functions

## Lucy::Address

```cpp
namespace Lucy
{
	template<class T> [[nodiscard]] constexpr auto Address(T& object) noexcept -> T*;
}
```

Safely returns the address of <span style='color: darkturquoise;'>object</span> without calling the *address-of* operator.

### Parameters

```cpp
T& object
```

### Returns

```cpp
T*
```