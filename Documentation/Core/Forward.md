```r
Latest: 0.0.1 - 04/01/2025
Location: Core/Forward.hpp
```


# Function Macros

## lucy_forward

```cpp
#define lucy_forward(forwarded) static_cast<decltype(forwarded)&&>(forwarded)
```

Perfect forwards the value category of the declared type of <span style="color: rgb(120, 120, 120);">forwarded</span>, except for prvalues, which are passed as xvalues.


### Parameters

``forwarded``