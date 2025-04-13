package Observer;

public interface Subjects {
    void addObserver(Observer observer);
    void removeObserver(Observer observer);
    void notifyObservers();
}
