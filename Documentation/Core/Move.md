```r
Latest: 0.0.1 - 05/01/2025
Location: Core/Move.hpp
Dependencies:
- Meta/RemoveLvalueReference.hpp
```


# Function Macros

## lucy_move

```cpp
#define lucy_move(moved) static_cast<::Lucy::Meta::RemoveLvalueReference<decltype(moved)>&&>(moved)
```

Produces an xvalue from the value category of the declared type of <span style="color: rgb(120, 120, 120);">moved</span>.


### Parameters

``moved``