/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
11) Create an abstract class “Publication” with data members ‘noOfPages’, ‘price’,
‘publisherName’ etc. with their accessor/modifier functions. Now create two sub-classes “Book”
and “Journal”. Create a class Library that contains a list of Publications. Write a main() function
and create three Books and two Journals, add them to library and print the details of all
publications.
*/

abstract class Publication {

    int noOfPages;
    long price;
    String publisherName;

    public int getNoOfPages() {
        return noOfPages;
    }

    public void setNoOfPages(int noOfPages) {
        this.noOfPages = noOfPages;
    }

    public long getPrice() {
        return price;
    }

    public void setPrice(long price) {
        this.price = price;
    }

    public String getPublisherName() {
        return publisherName;
    }

    public void setPublisherName(String publisherName) {
        this.publisherName = publisherName;
    }

    public Publication() {
    }

    public Publication(int noOfPages, long price, String publisherName) {
        this.noOfPages = noOfPages;
        this.price = price;
        this.publisherName = publisherName;
    }

    public void printDetails() {
        System.out.println("Name: " + publisherName);
        System.out.println("Price: " + price + " ,No.of pages: " + noOfPages);
        System.out.println();
    }
}

class Book extends Publication {

    public Book() {
    }

    public Book(int noOfPages, long price, String publisherName) {
        super(noOfPages, price, publisherName);
    }
}

class Journal extends Publication {
    public Journal() {
    }

    public Journal(int noOfPages, long price, String publisherName) {
        super(noOfPages, price, publisherName);
    }
}

class Library {

    public static void main(String[] args) {
        Journal j1 = new Journal(300, 80, "Peter Lang");
        Journal j2 = new Journal(580, 100, "BlackWell");

        Book b1 = new Book(1200, 700, "Selina Publishers");
        Book b2 = new Book(500, 300, "Chaya Prokashoni");
        Book b3 = new Book(1700, 600, "Penguin Publications");

        j1.printDetails();
        j2.printDetails();

        b1.printDetails();
        b2.printDetails();
        b3.printDetails();
    }
}