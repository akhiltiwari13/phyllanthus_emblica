"""
When the length of a solution is calculated, all comments and spaces are ignored.
Your task is to implement a simplified version of this length calculator.
Assume that there are only two types of comments:
line-comment: starting with '//' and ending at the end of the line;
block-comment: starting with '/*', and ending with the first occurrence of '*/'. It may span several lines.
Each non-space character outside comments adds 1 to the total length.
Note that all characters inside each comment are ignored, so they don't introduce nested comments.
See the examples for more details.
Also note that outside any other comment both '//' and '/*' start a new comment
(i.e. in this task you don't have to consider the cases where '//', '/*' or '*/' appear inside a string literal).
"""
import re


def length(code: str) -> int:
    # remove single line comments.
    code = re.sub(r'//.*', '', code)

    # remove multi-line comments.
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)

    code = re.sub(r'\s', '', code)

    return len(code)


def __main__():
    print("main")
    str = '''#include<iostream> //ignore single line comment
    /* this is a multi 
            line comment that must be ignored as well
            int x = ignore;
            till this line*/
            var = 2
            string sx = "don't ignore";
            //ignore again
            print(var)
            //ignore again
            //ignore again'''
    print("length(str):{}", length(str))


__main__()
