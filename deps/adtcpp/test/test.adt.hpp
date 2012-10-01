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
Add expr
    return evaluate(expr.left()) + evaluate(expr.right());
Subtract expr
    return evaluate(expr.left()) - evaluate(expr.right());
Multiply expr
    return evaluate(expr.left()) * evaluate(expr.right());
Divide expr
    return evaluate(expr.left()) / evaluate(expr.right());
Negate expr
    return - evaluate(expr.expr());
Constant expr
    return expr.value;
%end

int main() {
    
    
    %case Expr
    Add expr
        return evaluate(expr.left()) + evaluate(expr.right());
    Subtract expr
        return evaluate(expr.left()) - evaluate(expr.right());
    Multiply expr
        return evaluate(expr.left()) * evaluate(expr.right());
    Divide expr
        return evaluate(expr.left()) / evaluate(expr.right());
    Negate expr
        return - evaluate(expr.expr());
    Constant expr
        return expr.value;
    %end

}
