package Builder;

public class Person {
    private int age;
    private String address;
    private String name;

    private Person(String name, int age, String address) {
        this.name = name;
        this.address = address;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person [Name=" + name + ", Age=" + age + ", Address=" + address + "]";
    }

    public static class Builder{
        private int age;
        private String address;
        private String name;

        public Builder age(int age){
            this.age = age;
            return this;
        }

        public Builder name(String name){
            this.name = name;
            return this;
        }

        public Builder address(String address){
            this.address = address;
            return this;
        }

        public Person build(){
            return new Person(this.name, this.age, this.address);
        }

    }
}
