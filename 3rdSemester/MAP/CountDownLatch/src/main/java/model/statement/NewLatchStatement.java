package model.statement;

import exceptions.InterpreterException;
import model.expression.IExpression;
import model.programState.ProgramState;
import model.type.IntType;
import model.type.Type;
import model.utils.MyIDictionary;
import model.utils.MyIHeap;
import model.utils.MyILatchTable;
import model.value.IntValue;
import model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewLatchStatement implements IStatement{
    private final String var;
    private final IExpression expression;
    private static final Lock lock = new ReentrantLock();

    public NewLatchStatement(String var, IExpression expression) {
        this.var = var;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws InterpreterException {
        lock.lock();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyILatchTable latchTable = state.getLatchTable();
        if(!expression.eval(symTable, heap).getType().equals(new IntType()))
            throw new InterpreterException("Expression needs to be integer!");
        IntValue nr = (IntValue) (expression.eval(symTable, heap)); // check before
        int number = nr.getValue();
        int freeAddress = latchTable.getFreeAddress();
        if (symTable.isDefined(var)) {
            symTable.update(var, new IntValue(freeAddress));
            latchTable.put(freeAddress, number);
        } else {
            throw new InterpreterException(String.format("%s is not defined in the symbol table!", var));
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        if (typeEnv.lookUp(var).equals(new IntType())) {
            if (expression.typeCheck(typeEnv).equals(new IntType())) {
                return typeEnv;
            } else {
                throw new InterpreterException("Expression doesn't have the int type!");
            }
        } else {
            throw new InterpreterException(String.format("%s is not of int type!", var));
        }
    }

    @Override
    public IStatement deepCopy() {
        return new NewLatchStatement(var, expression.deepCopy());
    }

    @Override
    public String toString() {
        return String.format("newLatch(%s, %s)", var, expression);
    }
}
