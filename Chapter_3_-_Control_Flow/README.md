## 3. Control Flow
    1. Statements and Blocks
        * expression
        * statement
            * ; statement terminator
        * Braces { and } are used to group a _compound statement_, or _block_.
    2. If-Else
        * if (expression) {statement} else {statement}
    3. Else-If
        * if (expression) {statement} else if (expression) {statement} else {statement}
        * binary search
    4. Switch
        * one of a number of _constant_ integer values
        * switch (expression) {
                case const-expr: statements
                case const-expr: statements
                defult: statements
            }
    5. Loops - While and For
        * while (expression)
            statement
        * A matter of preference
        * When no initialization or increment conditions, then while is more natural
    6. Loops - Do-While
        * Tests the termination condition at the bottom
        * do
             statement
          while (expression);
        * Useful when at least one loop expression should be executed (like storing at least one data in an array)
    7. Break and Continue
        * Not neccessary
        * Useful when the loop is too complicated
    8. Goto and Labels
        * Not neccessary
        * To abandon processing in some deply nested structure
        * Break cannot easily replace Goto in the following exaple:
            for (...)
                for (...) {
                    ...
                    if (disaster)
                        goto error;
                }
            ...
            error:
                /\* clean up the mess \*/
