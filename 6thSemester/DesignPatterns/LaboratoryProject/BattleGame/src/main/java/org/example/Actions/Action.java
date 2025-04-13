package org.example.Actions;

public interface Action { //Encapsulates a request as an object — lets you parameterize and queue actions.
    void execute();
    void unexecute();
}
