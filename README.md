# BetterCookie961-Interpreter
BetterCookie961 Interpreter written in c++

# BetterCookie961 Instructions

BetterCookie961 has 8 basic instructions:

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

# How to write IF constructions

1) IF always starts with an expression. (k > i ! cca)

2) Always after the expression comes !, after which the body is written. {k > i - expression} {! - delimiter} {cca - body}

3) IF has no variables, so numeric values are passed like this:
* `i` - left cookie value
* `k` - right cookie value
* `t` - current cookie value
Example: (k > i ! cca) = {if (k > a): do cca}

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
