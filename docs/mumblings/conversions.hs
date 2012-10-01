-- Conversions are done by functions with the same name as a type
-- A Foo -> Bar conversion has the type signature

:: Foo -> Bar
foo(x) = 

-- For example
:: String -> Int
string(x) = 


:: (A => B) -> A
list(y) = x for x in y


There are two types of conversions: implicit and explicit.
The rule of implicit conversions states that
    An Int may be converted to a Real
    A custom data may be converted to a tuple
    A tuple may be converted to a custom data
    types may be converted to Any, however conversion from Any to a type (other than Any) requires either an explicit cast int(x) or that the code is only reachable if the any is of a specific type
        The only pattern that compilers must recognize is
            if someany is Int
                -- statement involving someany
        
        Compilers may optionally recognize usages such as
            if someany is Int
                if somethingelse is Bar
                    -- statement involving someany
        or even
            if true && 3 < 5 && (fermatsLastTheoremIsFalse() || someany is Bar)
                -- statement involving someany
        
        Compilers are free to allow any other construct in which they can prove that the code is only reachable if the any is a certain type. Compilers may warn, however it is recommended that compilers do not warn *by default* for very obvious uses of implicit any casting that a production grade compiler can be expected to catch. The reason for this is that readable code is preferable to making code ugly for compatibility with poor quality compilers, and if users are interested in such compatibility, they can enable the warnings themselves.
        However we do not wish to make the language too difficult to implement.
        
A Real may NOT be converted to an Int implicitly. There are many options available for converting a Real to an Int
    floor()
        Mathematical floor function
    ceil()
        Mathematical ceiling function
    int()
        Integer part
    round()
        Round to the nearest integer




