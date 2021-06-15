class hello{

    int age; 
    String name;
    int cgpa;

    public hello() {
    }

    public hello(int age, String name, int cgpa) {
        this.age = age;
        this.name = name;
        this.cgpa = cgpa;
    }

    public int getAge() {
        return this.age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCgpa() {
        return this.cgpa;
    }

    public void setCgpa(int cgpa) {
        this.cgpa = cgpa;
    }

    public hello age(int age) {
        setAge(age);
        return this;
    }

    public hello name(String name) {
        setName(name);
        return this;
    }

    public hello cgpa(int cgpa) {
        setCgpa(cgpa);
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof hello)) {
            return false;
        }
        hello hello = (hello) o;
        return age == hello.age && Objects.equals(name, hello.name) && cgpa == hello.cgpa;
    }

    @Override
    public int hashCode() {
        return Objects.hash(age, name, cgpa);
    }

    @Override
    public String toString() {
        return "{" +
            " age='" + getAge() + "'" +
            ", name='" + getName() + "'" +
            ", cgpa='" + getCgpa() + "'" +
            "}";
    }



    public static void main(String[] args) {
        
    }
}
