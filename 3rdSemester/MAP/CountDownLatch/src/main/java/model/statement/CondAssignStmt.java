package model.statement;

import exceptions.InterpreterException;
import model.expression.IExpression;
import model.programState.ProgramState;
import model.type.BoolType;
import model.type.Type;
import model.utils.MyIDictionary;

// v = exp1?exp2:exp3 -> if (exp1) then x = exp2 else v = exp3

public class CondAssignStmt implements IStatement {
    private final String v;
    private final IExpression exp1;
    private final IExpression exp2;
    private final IExpression exp3;

    public  CondAssignStmt(String vv, IExpression e1, IExpression e2, IExpression e3){
        this.v = vv;
        this.exp1 = e1;
        this.exp2 = e2;
        this.exp3 = e3;
    }

    @Override
    public ProgramState execute(ProgramState state)throws InterpreterException{
        if(!exp1.eval(state.getSymTable(), state.getHeap()).getType().equals(new BoolType()))
            throw new InterpreterException("Condition must be a boolean\n");
        if(!state.getSymTable().isDefined(v))
            throw new InterpreterException(v + " is not defined\n");
        Type tv = state.getSymTable().lookUp(v).getType();
        Type texp2 = exp2.eval(state.getSymTable(), state.getHeap()).getType();
        Type texp3 = exp3.eval(state.getSymTable(), state.getHeap()).getType();
        if(!tv.equals(texp2)||!tv.equals(texp3))
            throw new InterpreterException("The variable and the 2 expressions must have the same type\n");


        IStatement ifStmt = new IfStatement(exp1, new AssignStatement(v, exp2), new AssignStatement(v, exp3));
        state.getExeStack().push(ifStmt);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException{
        if(!exp1.typeCheck(typeEnv).equals(new BoolType()))
            throw new InterpreterException("Condition must be a boolean expression\n");
        Type tv = typeEnv.lookUp(v);
        Type texp2 = exp2.typeCheck(typeEnv);
        Type texp3 = exp3.typeCheck(typeEnv);

        if(!tv.equals(texp2) || !tv.equals(texp3))
            throw new InterpreterException("The variable and the 2 expressions must have the same type\n");

        return typeEnv;
    }

    @Override
    public IStatement deepCopy() {
        return new CondAssignStmt(v,exp1,exp2,exp3);
    }

    @Override
    public String toString(){return v+"="+exp1+"?"+exp2+":"+exp3;}
}
