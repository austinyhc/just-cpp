---
title: BiteSize - Breakdown of `__is_constexpr`
tags: bitesize, c, constexpr
---

# Breakdown of `__is_constexpr`

The `__is_constexpr` as the name suggests is to check if a input paramter is a **constant expression**. The implementation of the `__is_constexpr` can be found in [include/kernel/kernel.h](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/kernel.h?id=3c8ba0d61d04ced9f8d9ff93977995a9e4e96e91#n814):

```c
#define __is_constexpr(x) \
 	(sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))
```

Let's play with it by running the following code.
```c
#include <stdio.h>
#define define_val 10
#define __is_constexpr(x) \
    (sizeof(int) == sizeof(*(8 ? ((void *) ((long) (x) *0l)) : (int *) 8)))

enum test { enum_val };

int main()
{
    int val = 10;
    const int const_val = 10;

    int a = __is_constexpr(val);
    int b = __is_constexpr(const_val);
    int c = __is_constexpr(10);
    int d = __is_constexpr(define_val);
    int e = __is_constexpr(enum_val);             
    printf("a:%d b:%d c:%d d:%d e:%d\n", a, b, c, d, e);
    return 0;
}
```
The result seems to be correct, but how does it exactly work. Let us move on.
```
a:0 b:0 c:1 d:1 e:1
```
## Terminology
Before jumping right into the code a few terms need to be clarified.

### Constant expressions
 
Let us start with some definition of constant expressions quoted from the C11 standard.

> #### §6.6 2) Description
> A constant expression ***can be evaluated during translation*** rather than runtime, and accordingly may be used in any place that a constant may be.

> #### §6.6 3) Constraints
> Constant expressions shall ***not*** contain ***assignment***, ***increment***, ***decrement***, ***function-call***, or ***comma operators***, except when they are contained within a subexpression that is not evaluated.

:::success
:pill: **Supplements**: [comma operators](https://en.wikipedia.org/wiki/Comma_operator)
:::

Having the above definition in mind, let's look back at the previous test code
* the `val` as in `int val = 0` is not a constant expression
* the `const_val` as in `const int const_val = 10` is not a constant expression
* `10` 和 `define_val` are constant expressions
* `enum_val` as in `enum test { enum_val }` is a constant expression

### Integer constant expression (ICE)

> #### §6.6 6)
> An *integer constant expression* shall have integer type and shall only have operands that are integer constants, enumeration constants, character constants, **sizeof** expressions whose results are integer constants, **\_Alignof** expressions, and floating constants that are the immediate operands of casts. Cast operators in an integer constant expression shall only convert arithmetic types to integer types, except as part of an operand to the **sizeof** or **\_Alignof** operator.

## How the dark magic works

### Null pointer constant vs null pointer

Let's start off by focusing on the second operand of the conditional operator.

```c
(void *)((long)(x) * 0l)
```

:::spoiler :pill: **Non-essential supplement**
:::info
The `(long)(x)` cast is intended to allow `x` to have pointer types and to avoid warnings on `u64` types on 32-bit platforms. However, this detail is not crucial for understanding the key points of the macro. [^1]
:::

<br>

- If `x` **is** an **integer constant expressoin (ICE)**, then `(void *)((long)(x) * 0l)` turns into `NULL` or a [**null pointer constant**](https://www.gnu.org/software/libc/manual/html_node/Null-Pointer-Constant.html).

:::success
:boom: According to the C11 standard, a **null pointer constant** and a **null pointer** are different by definition. That's the main reason why we should always use the official standard book as our learning or reference material. 
:::

>  #### §6.3.2.3 3)
>  An ***integer constant expression*** with the ***value 0***, or such an expression ___cast to type `void *`___, is called a null pointer constant. ***If a null pointer constant is converted to a pointer type, the resulting pointer, called a null pointer***, is guaranteed to compare unequal to a pointer to any object or function.

- On the other hand, if `x` is **not** an ICE, then `(void *)((long)(x) * 0l)` is still of type (`void *`), but it is **not** `NULL`.

Knowing the logic behind the scene, let's translate them into something more programmatic.
- `NULL ≡ ((void *)0)` (not neccesary true because `NULL` is **compiler-dependent**)
- `(void *)`

### Conditional operator 

```c
*(8 ? /*...*/ : (int *)8))
```

:::spoiler :pill: **Non-essential supplement**
:::info
The second 8 literal is intended to avoid compiler warnings about creating pointers to unaligned addresses. The first 8 literal could simply be 1. However, these details are not important for understanding the key points of the macro. [^1]
:::
<br>
Another key here is the conditional operator. A conditional operator  behaves differently upon what you put in the second operand and the third operand. If

The bottom line is that `?:` is not some glorified `if‑else` replacement, but a rather peculiar operator that comes with lots of special rules. `?:` also has very few valid use‑cases in real C code, one of the few valid uses for it is certain function‑like macros.

:::success
:boom: This shows ***again*** the importance of the C standard book. If you assume that a conditional operator is just an alternative of the `if-else`, then you will miss some crucial information.
:::

- `8 ? NULL : (int *) 8` ends up with `(int *)` because as the C standards says, if one of the sides of a conditional operation with pointers is `NULL`, the end result is the othter type.

> #### §6.5.15.6
> [...] if one operand is a null pointer constant, the result has the type of the other operand.

-  `8 ? non-NULL : (int *) 8`

> #### §6.5.15.6
> if both operands are pointers to compatible types or to differently qualified versions of compatible types, the result type is a pointer to an appropriately qualified version of the composite type.


### `sizeof` operator

```c
(sizeof(int) == sizeof(/*...*/))
```

The last missing piece is the `sizeof` operator. In C standard it says:

> #### §6.5.3.4 1) Constraints
> The `sizeof` operator shall not be applied to an expression that has function type or an incomplete type, to the parenthesized name of such a type, or to an expression that designates a bit-field member.

However, GNU C provides an [extension](https://gcc.gnu.org/onlinedocs/gcc/Pointer-Arith.html) to it.

> #### §6.24 Arithmetic on void- and Function-Pointers
> In GNU C, addition and subtraction operations are supported on pointers to `void` and on pointers to functions. ***This is done by treating the size of a `void` or of a function as 1.*** A consequence of this is that `sizeof` is also allowed on void and on function types, and returns 1. The option `-Wpointer-arith` requests a warning if these extensions are used.

So now we have

-  `sizeof(int) ≡ 8` makes the final result to be `true`.
-  `sizeof(void) ≡ 1` makes the final result to be `false`.

## Conclusion

The `__is_constexpr` macro is notable for taking advatage of subtle details of the C standard: the nuance of null pointer constant and null pointer, the conditional operator and finally the `sizeof` operator.


[^1]: Rasmus Villemoes, "Re: detecting integer constant expressions in macros", https://lkml.org/lkml/2018/3/21/775