# ExpressionTemplate-test
Test for expression template

## typical result

```
96229 [us]  total = 6000
97177 [us]  total = 6000
1 [us]  total = 6000
```
MacOS, Mojave, 2.2 GHz Intel Core i7, compiled with Apple LLVM version 10.0.1 (clang-1001.0.46.4)

Vector calculation with a class lazy::Vect is as fast as usual array (in this case, used std::vector) with double loop.

(Why valarray is very fast is that the result of add calculation is given by auto. Maybe the valarray would be implemented by something like expression templte.)
