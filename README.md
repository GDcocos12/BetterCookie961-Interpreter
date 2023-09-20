# BetterCookie961-Interpreter
BetterCookie961 Interpreter written in c++

# BetterCookie961 Instructions

* `k` - move the pointer right
* `i` - move the pointer left
* `K` - move the pointer right and copy the value of the left cookie
* `I` - move the pointer left and copy the value of the right cookie
* `c` - increment the current cookie value
* `C` - Adds 10 to current cookie value
* `o` - decrement the current cookie value
* `O` - decreases the current cookie value by 10
* `L` - erase current cookie value
* `9` - output the value of the current cookie (Outputs only chars)
* `a` - debug(ASCII) output. Output the current cookie value
* `e` - **replace** the value of the current cookie with input
* `6` - jump to the **matching** `1` instruction if the current cookie value is zero
* `1` - jump to the **matching** `6` instruction if the current cookie value is **not** zero
* `(` - IF construction starts
* `)` - IF construction ends
* `N` - Return to the initial cookie
* `n` - print current cookie value
* `>` - Go to next line(in output)
* `R` - Write a random value in the range 0-100 to a cookie
* `{` - Beginning of an arithmetic expression
* `}` - End of arithmetic expression
* `r` - Run file from user input
* `B[filename]` - Run file
* `S[milliseconds]` - Sleep function
* `M[WhereToMove(int)]` - Move current cookie value to another cookie
* `-` - Stop executing program
# Some Examples

`M[3]` - Moves the value of this cookie forward 3 steps right.
`M[-1]` - Moves the value of this cookie forward 1 step left.

# How to write IF constructions

IF construction operators:
* `>` - bigger
* `<` - less
* `=` - equal
* `~` - not equal

1) IF always starts with an expression. (k > i ! cca)

2) Always after the expression comes !, after which the body is written. {k > i - expression} {! - delimiter} {cca - body}

3) IF has no variables, so numeric values are passed like this:
* `i` - left cookie value
* `k` - right cookie value
* `t` - current cookie value
Example: (k > i ! cca) = {if (k > i): do cca}


ATTENTION! Before calling the IF, "create" all the cookies you need (move to them)!
Example: cc(k > i ! cca) - ERROR, because right cookie does not exist. kkki(k > i ! cca) - SUCCESS, right and left cookies exist.
More examples:
* `kkk(k > i ! cca)` - ERROR, right cookie does not exist.
* `ki(k < i ! cca)` - ERROR, left cookie does not exist.

You can also write IF inside the BODY of another IF.
Examples:
* `cckccckcccci(k > i ! kkcckccckcci(i > k ! cca))` - SUCCESS.
* `cckccckcccci(k > i ! (i < k ! cca))` - SUCCESS.
* `cckccckcccci(k > (i < k ! cca))` - ERROR, no body.

**IF constructs ALWAYS have !, otherwise you will get an error.**

# How to write arithmetic expressions

Arithmetic expressions have 4 operators:
* `+` - addition
* `-` - subtraction
* `*` - multiplication
* `%` - division

Numeric values are passed through:
* `k` - right cookie value
* `t` - current cookie value
* `i` - left cookie value

**After executing an arithmetic expression, the result is written to the current cookie**

Examples:

`{t + k}` - current cookie value + right cookie value
`{t - i}` - current cookie value - left cookie value

**ATTENTION! The arithmetic expression only uses 2 values and 1 operator!**

`{t + k - i}` = `{t + k}`
`{i * k - t + k}` = `{i * k}`

Program Examples:

`ekei{t + k}n` - Calculates the sum of two numbers
`ekekei{t + k}{t + i}n` - Calculates the sum of three numbers
