/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
16) A bookshop maintains the inventory of books that are being sold at the shop. The list
includes details such as author, title, publisher, cost and stock position. Whenever a customer
wants a book, the sales person inputs the title and author and the system searches the list and
displays whether it is available or not. If it is not, an appropriate message is displayed. If it is,
then the system displays the book details and details and requests for the number of copies
required. If the required copies are available, the total cost of the requested copies is displayed,
otherwise the message “requires copies not in stock” is displayed. Design a system using a class
called “Book” with suitable member methods and constructors.
*/

import java.util.ArrayList;

class BookShop {

    static class Book {

        private String author;
        private String title;
        private String publisher;
        private double cost;
        private int stock;

        Book(String author, String title, String publisher, double cost, int stock) {
            this.author = author;
            this.title = title;
            this.publisher = publisher;
            this.cost = cost;
            this.stock = stock;
        }

        String getAuthor() {
            return author;
        }

        String getTitle() {
            return title;
        }

        String getPublisher() {
            return publisher;
        }

        double getCost() {
            return cost;
        }

        int getStock() {
            return stock;
        }

        void getDetails() {
            System.out.println("Author : " + this.getAuthor());
            System.out.println("Title : " + this.getTitle());
            System.out.println("Publisher : " + this.getPublisher());
            System.out.println("Price : " + this.getCost());
        }
    }

    private ArrayList<Book> books = new ArrayList<Book>();

    public void addBook(String author, String title, String publisher, double cost, int stock) {
        books.add(new Book(author, title, publisher, cost, stock));
    }

    public boolean isBookAvailable(String author, String title) {
        for (Book it : books) {
            if (it.getAuthor().equals(author) && it.getTitle().equals(title))
                return true;
        }
        return false;
    }

    public boolean isStockAvailable(String author, String title, int copies) {
        for (Book it : books) {
            if (it.getAuthor().equals(author) && it.getTitle().equals(title))
                return copies <= it.getStock();
        }
        return false;
    }

    public double totalCost(String author, String title, int copies) {
        for (Book it : books) {
            if (it.getAuthor().equals(author) && it.getTitle().equals(title))
                return it.getCost() * copies;
        }
        return 0;
    }

    public void getDetails(String author, String title) {
        for (Book it : books) {
            if (it.getAuthor().equals(author) && it.getTitle().equals(title))
                it.getDetails();
        }
    }
}

class Main_Q16 {
    public static void main(String[] args) {
        BookShop TechnoBookHouse = new BookShop();
        TechnoBookHouse.addBook("Sudarshan, Korth", "Database Management System", "McGraw-Hill", 200.0, 10);
        TechnoBookHouse.addBook("Andrew Ng", "Machine Learning Yearning", "Springer", 250.0, 15);
        TechnoBookHouse.addBook("Herbert Schildt", "Java: The Complete Reference", "McGraw-Hill", 300.0, 8);

        System.out.println("Searching the book...\nTitle : Java: The Complete Reference, Author : Herbert Schildt");
        if (TechnoBookHouse.isBookAvailable("Herbert Schildt", "Java: The Complete Reference")) {
            System.out.println("\nBook is available");
            System.out.println("Book Details :");
            TechnoBookHouse.getDetails("Herbert Schildt", "Java: The Complete Reference");
            System.out.println("\nNow, searching 6 copies of the book");
            if (TechnoBookHouse.isStockAvailable("Herbert Schildt", "Java: The Complete Reference", 6)) {
                System.out.println("Total Cost : "
                        + TechnoBookHouse.totalCost("Herbert Schildt", "Java: The Complete Reference", 6));
            } else
                System.out.println("Required number of copies not available");
        } else
            System.out.println("Book not available");
    }
}
