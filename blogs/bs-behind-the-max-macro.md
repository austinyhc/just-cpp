---
title: BiteSize - Behind the `max` Macro
tags: bitesize, c
---

# Behind the `max` Macro

Naively, when we think of the `max` macro, the one line of code comes across. However, when we look into the source codes of [linux/include/linux/minmax.h](https://github.com/torvalds/linux/blob/master/include/linux/minmax.h), it is not what we simply think it is, instead there are lines of codes. Moreover, how the Linux Kernel contributers write them is not commonly seen.

In this article, let's start off with a vanilla `max` macro (we will call it ==`MAX0`== in this article) shown below and step by step we will do some case studies of Linux Kernel codes and see how Linux Kernel developers perfectionize it in practice.
```clike
#define max(x, y) (x) > (y) ? (x) : (y)
```
:::info
In order to avoid any unexpected behavior, please always use **parentheses** to wrap the parameters while defining a macro.
:::

## Introducing `typeof` Keyword

[typeof](https://gcc.gnu.org/onlinedocs/gcc/Typeof.html) is a GNU extension provided by the `gcc`, and later being adopted by `icc` and `clang`. It is used to get the type of an object druing the **compile time**.

According to the `gcc` documentation,

> `typeof` is often useful in conjunction with statement expressions. Here is how the two together can be used to define a safe "maximum" macro which operates on any arithmetic type and evaluates each of its arguments exactly once:

```clike
#define max(a,b) ({ \
    typeof (a) _a = (a); \
    typeof (b) _b = (b); \
    _a > _b ? _a : _b; \
})
```

The`max` macro (==`MAX1`==) shown above is designed to avoid the **double evaluation**. Let's look at the following example:
```c
void do_one_time() { printf("called do_one_time!\n"); }

int f1() { do_one_time(); return 0; }
int f2() { do_one_time(); return 1; }

int result = max(f1(), f2());
```
:::info
:bulb: **Trick**: `-E` option tells the `gcc` to stop after ther preprocessing stage.
:::

Let's use `gcc -E` and observe how the preprocessor expand the `max` macro in the codes.
1. In ==`MAX0`== scenario, either `f1()` or `f2()` will be evaluated **twice**. As a result, `called do_one_time!\n` gets printed three times. In our case here, the result is still what a caller expects it to be, but what if `f1()` is an expression like `x++` or `x--`, the result would be incorrect due this **double evaluation** behavior. 
	```clike
	int result = (f1() > f2() ? f1() : f2());
	```
2. In ==`MAX1`== scenario, we see the `f1()` or `f2()` is only being evaluated once and assigned to its intermediate variable which is ***adaptively declared by using the `typeof` keyword***.
	```clike
	int result = ({
	    typeof (f1()) _a = (f1());
	    typeof (f2()) _b = (f2());
	    _a > _b ? _a : _b;
	});
    ```
## Type Checking

Apparently, a Linux Kernel developer considers more. According to the [arch/powerpc/boot/types.h ](https://github.com/torvalds/linux/blob/master/arch/powerpc/boot/types.h), this `max` (==`MAX2`==) not only avoids the **double evaluation** issue but also raises a warning (`warning: comparison of distinct pointer types lacks a cast`) at compile time if the types of the two parameters are not identical.

:::info
These kind of techniques of **early warning at compile time** are noramlly and widely used in Linux Kernel to avoid potential bugs. Also see the [**BUILD_BUG_ON_ZERO()**](https://hackmd.io/@sysprog/c-bitfield#Linux-%E6%A0%B8%E5%BF%83-BUILD_BUG_ON_ZERO).
:::

```clike
#define max(x, y) ({ \
    typeof(x) _x = (x); \
    typeof(y) _y = (y); \
    (void) (&_x == &_y); \
    _x > _y ? _x : _y; })
```

## Naming Conflicts

The ==`MAX2`== has a potential risk of naming conflict, while C does not support [namespace](https://en.wikipedia.org/wiki/Namespace). C developers usually use `struct` to encapsulate variables and function pointers and use `static` to control the [visibility of symbols](https://gcc.gnu.org/wiki/Visibility). Knowing this, let's see how a Linux Kernel contributer fixes this.

Let's use the following codes as the example to compile and execute the following codes. It turns out the result is `1` instead of the expected `2` because `x` and `_x` are not only defined in the local scope but also used in the macro. 
```clike
int main() {
    int x = 1, _x = 2; 
    return max(x , _x);
}
```
```bash
gcc -o m m.c && ./m && echo $?
```
Still, let's use the `gcc -E` command to check the codes. It can be observed that everything is legit C so it won't throw any warnings or errors to signal this **naming conflict** issue.
```clike
return ({
    typeof(x) _x = (x);
    typeof(_x) _y = (_x);
    (void) (&_x == &_y);
    _x > _y ? _x : _y; });
```
This potential risk did not get fixed until [Linux v4.9](https://elixir.bootlin.com/linux/v4.9.275/source/include/linux/kernel.h#L752) (comapred to [Linux v4.8](https://elixir.bootlin.com/linux/v4.9.275/source/include/linux/kernel.h#L752)) (==`MAX3`==)

```clike
#define __max(t1, t2, max1, max2, x, y) ({		\
	t1 max1 = (x);					\
	t2 max2 = (y);					\
	(void) (&max1 == &max2);			\
	max1 > max2 ? max1 : max2; })
#define max(x, y)					\
	__max(typeof(x), typeof(y),			\
	      __UNIQUE_ID(max1_), __UNIQUE_ID(max2_),	\
	      x, y)
```
The `__UNIQUE_ID` is defined in [include/linux/compiler-gcc.h](https://elixir.bootlin.com/linux/v4.9.275/source/include/linux/compiler-gcc.h#L211)
```clike
#define __UNIQUE_ID(prefix) \
    __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)
```
The `__PASTE` is defined in [include/linux/compiler.h](https://elixir.bootlin.com/linux/v4.9.275/source/include/linux/compiler.h#L51)
```clike
#define ___PASTE(a , b) a##b
#define __PASTE(a , b) ___PASTE(a, b)
```
`##` is used for [concatenation](https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html) in C preprocessing stage. In other words, `__PASTE(a,b)` is equivalent to `ab`.

`__COUNTER__` is the key role in this solution. `__COUNTER__` is a GNU extension. Quote from the [$3.7.2 Common Predefined Macros](https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html) in [GCC online documentation](https://gcc.gnu.org/onlinedocs/cpp).

> This macro expands to sequential integral values starting from 0. In conjunction with the `##` operator, this provides a convenient means to generate unique identifiers. Care must be taken to ensure that `__COUNTER__` is not expanded prior to inclusion of precompiled headers which use it. Otherwise, the precompiled headers will not be used.

Every `__COUNTER__` generates an unique number and through the `##`, we add that number or identifier to the end of the original variable name string. Let's look at our codes with macro expanded, we have ***__UNIQUE_ID_max1_0*** and ***__UNIQUE_ID_max2_1***, where the trailing ***_0*** and ***_1*** are given by the `__COUNTER__` keyword.

```c
    int x = 1, _x = 2;
    return ({ typeof(x) __UNIQUE_ID_max1_0 = (x); \
              typeof(_x) __UNIQUE_ID_max2_1 = (_x); \
              (void) (&__UNIQUE_ID_max1_0 == &__UNIQUE_ID_max2_1); \
              __UNIQUE_ID_max1_0 > __UNIQUE_ID_max2_1 ? __UNIQUE_ID_max1_0 : __UNIQUE_ID_max2_1; \
           });
```

## Linux VLA-free Policy
:::success
:door: **Portal** [BiteSize - Variable Length Array](/3x3bhzgDTIagticYfEEAgg)
:::

[Linux is VLA-free since version 4.20](https://www.phoronix.com/news/Linux-Kills-The-VLA). Also it enables the `-Wvla` compiler flag to emit a warning should any variable-length array be found within the kernel's C code. That will help prevent new code from inadvertently using VLAs and also spot any lingering kernel code still relying upon this behavior.

```c
#define X 1
#define Y 2

int main() {
    char sym[max(X, Y)];
    return 0;                                 
}
```
Let's run the above code with ==`MAX3`==. It throws a warning as follows.

```bash
warning: ISO C90 forbids variable length array ‘sym’ [-Wvla]
   |     char sym[max(X, Y)];
   |     ^~~~
```
Interestingly, if we use the ==`MAX0`==, the compiler won't complain because ==`MAX0`==`(X,Y)` is considered to **always be a constant** at the **compile time**.

Let's get back to the main subject, the evolved ==`MAX3`== could be a stumbling block while Linux was on its way to eliminate the VLA.

There is once a transitional [[PATCH] vsprintf: Remove accidental VLA usage share 0](https://lkml.org/lkml/2018/3/7/1077) adding the `SIMPLE_MAX` macro to make the parameters in it to be `const`-qualified type values just in order to work around the `-Wvla` warning.

```diff
--- a/lib/vsprintf.c
+++ b/lib/vsprintf.c
@@ -744,8 +744,9 @@ char *resource_string(char *buf, char *end, struct resource *res,
 #define FLAG_BUF_SIZE		(2 * sizeof(res->flags))
 #define DECODED_BUF_SIZE	sizeof("[mem - 64bit pref window disabled]")
 #define RAW_BUF_SIZE		sizeof("[mem - flags 0x]")
-	char sym[max(2*RSRC_BUF_SIZE + DECODED_BUF_SIZE,
-		     2*RSRC_BUF_SIZE + FLAG_BUF_SIZE + RAW_BUF_SIZE)];
+#define SIMPLE_MAX(x, y)	((x) > (y) ? (x) : (y))
+	char sym[SIMPLE_MAX(2*RSRC_BUF_SIZE + DECODED_BUF_SIZE,
+			    2*RSRC_BUF_SIZE + FLAG_BUF_SIZE + RAW_BUF_SIZE)];
 
 	char *p = sym, *pend = sym + sizeof(sym);
 	int decode = (fmt[0] == 'R') ? 1 : 0;
```

Thus, `max` macro diverged, but having my words, Linux kernel contributors won't give in to this. They started to think how a compiler can check if an inputs are **constant expression** before branching to either ==`MAX0`== or ==`MAX3`==. This demand brings us to [this patch, kernel.h: Retain constant expression output for max()/min()](https://github.com/torvalds/linux/commit/3c8ba0d61d04ced9f8d9ff93977995a9e4e96e91).

> This patch updates the `min()`/`max()` macros to evaluate to a constant expression when called on constant expression arguments. This removes several false-positive stack VLA warnings from an x86 allmodconfig build when `-Wvla` is added.

Additionally, the `max()`/`min()` have been moved from `include/linux/kernel.h` to [`include/linux/minmax.h`](https://github.com/torvalds/linux/blob/master/include/linux/minmax.h) since 2020 at [kernel.h: split out min()/max() et al. helpers](https://github.com/torvalds/linux/commit/b296a6d53339a79082c1d2c1761e948e8b3def69). The current implementation of `max()` macro (==`MAX4`==) is shown below.

```c
#define __is_constexpr(x) \                   
    (sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))

#define __typecheck(x, y) \
    (!!(sizeof((typeof(x) *)1 == (typeof(y) *)1)))

#define __no_side_effects(x, y) \             
    (__is_constexpr(x) && __is_constexpr(y))

#define __safe_cmp(x, y) \
    (__typecheck(x, y) && __no_side_effects(x, y))
                
#define __cmp(x, y, op) ((x) op (y) ? (x) : (y))
                
#define __cmp_once(x, y, unique_x, unique_y, op) ({ \
    typeof(x) unique_x = (x); \
    typeof(y) unique_y = (y); \
    __cmp(unique_x, unique_y, op); })

#define __careful_cmp(x, y, op) \
    __builtin_choose_expr(__safe_cmp(x, y), \
        __cmp(x, y, op), \
        __cmp_once(x, y, __UNIQUE_ID(__x), __UNIQUE_ID(__y), op))
#define max(x, y)       __careful_cmp(x, y, >)
```

Essentially, two key elements come to rescue

* `__is_constexpr` as the name suggests is to check whether the input is a **constant expression**. 
:::success
:door: **Portal**: [BiteSize - Breakdown of `__is_constexpr`](/ViSqVdWhS8O1uOjNgQU_fg)
:::
* `__builtin_choose_expr` is a GNU extension.

> Built-in Function: `type __builtin_choose_expr (const_exp, exp1, exp2)`
> You can use the built-in function `__builtin_choose_expr` to evaluate code depending on the value of a constant expression. This built-in function returns exp1 if `const_exp`, which is an integer constant expression, is nonzero. Otherwise it returns exp2.

> This built-in function is analogous to the ‘? :’ operator in C, except that the expression returned has its type unaltered by promotion rules. Also, the built-in function does not evaluate the expression that is not chosen. For example, if `const_exp` evaluates to true, exp2 is not evaluated even if it has side effects.

In the nutshell, the Linux kernel verion of `max()` macro gets to know which max implementation (==`MAX0`== or ==`MAX3`==) it will go for by telling if the input parameters are both constant expression.

## Why Not Use `inline`?

Naturally, some would say why not use the [inline funtion](https://en.wikipedia.org/wiki/Inline_function) to resolve the problem that ==`MAX3`== is faced with.
```c
static inline int max(int x, int y) {
    return x > y ? x : y;
}
```
Or in plain words, **let the compiler checks the type for us.** The reasons why this is not adopted by the Linux kernel contributors are:
1. `inline` ***hints*** the compiler for the expansion so it does not work consistently.
2. C does not have `template` or the **metaprogramming technique** as C++ does so for generalization's sake, multiple implementations for different type have to be done.
3. ==`MAX4`== seems complex but it has nothing to do with the type. In addition to this, it can work with GNU extension to do some neccesary checking at the compile time. To some C expert, it is more flexible and definitely more preferable.


## Conclusion

Going through the `max` and `min` macro in Linux Kernel, we found that how flexible the C program can be and how thoughtful a Linux Kernel developer could be. Even it depends on a GNU extension, it beautifully and elegantly manages to do the type checking at compile time and stay performant at runtime. 
