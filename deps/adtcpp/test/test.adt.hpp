%data Expr
add            (Expr left, Expr right)
subtract       (Expr left, Expr right)
multiply       (Expr left, Expr right)
divide         (Expr left, Expr right)
negate         (Expr expr)
constant       (int value)
%end

%generate Expr
%call evaluate($$)
%template int evaluate($$)
%%case Add expr
    return evaluate(expr.left()) + evaluate(expr.right());
%%case Subtract expr
    return evaluate(expr.left()) - evaluate(expr.right());
%%case Multiply expr
    return evaluate(expr.left()) * evaluate(expr.right());
%%case Divide expr
    return evaluate(expr.left()) / evaluate(expr.right());
%%case Negate expr
    return - evaluate(expr.expr());
%%case Constant expr
    return expr.value;
%end
