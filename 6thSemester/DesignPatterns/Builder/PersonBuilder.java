package Builder;

public class PersonBuilder {
    int age;
    String name, address;

    public PersonBuilder age(int age){this.age = age; return this;}
    public PersonBuilder name(String name){this.name = name; return this;}
    public PersonBuilder address(String address){this.address = address; return this;}

    public PublicPerson build(){return new PublicPerson(name,age,address);}

}
