package Builder;

public class PublicPerson {
    private int age;
    private String address;
    private String name;

    public PublicPerson(String name, int age, String address) {
        this.name = name;
        this.address = address;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person [Name=" + name + ", Age=" + age + ", Address=" + address + "]";
    }
}
