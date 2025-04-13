package Command;

import javax.naming.ldap.Control;

public class Remote {
    public Remote(){
    }

    public void PressButton(Command command){
        command.execute();
    }
}
