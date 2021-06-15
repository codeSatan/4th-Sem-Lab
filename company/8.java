/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/**
 * 8) Implement a class for a “Book”. Book contains a title (a String), a list
 * of authors (array of authors), number of pages (an integer), price (floating
 * point number), publisher (a String) etc. Write suitable constructor and
 * accessor/modifier methods. Implement a class for “Library”. A library
 * contains a list of books (array of Book). Write add (to add a book) and
 * remove (to delete a book) methods for library. Write a main() function to
 * create a “Library” and add five “Book” to library. Print the total price of
 * all books.
 */

class Main_Q8 {

    static class Book {
        private String title, publisher;
        private String[] authors;
        private int num_pages;
        private double price;

        public Book(String title, String publisher, String[] authors, int num_pages, double price) {
            this.title = title;
            this.publisher = publisher;
            this.num_pages = num_pages;
            this.price = price;
            this.authors = new String[authors.length];
            for (int i = 0; i < authors.length; i++) {
                this.authors[i] = authors[i];
            }
        }

        public String getTitle() {
            return title;
        }

        public void setTitle(String title) {
            this.title = title;
        }

        public String getPublisher() {
            return publisher;
        }

        public void setPublisher(String publisher) {
            this.publisher = publisher;
        }

        public String[] getAuthors() {
            return authors;
        }

        public void setAuthors(String[] authors) {
            this.authors = new String[authors.length];
            for (int i = 0; i < authors.length; i++) {
                this.authors[i] = authors[i];
            }
        }

        public int getNum_pages() {
            return num_pages;
        }

        public void setNum_pages(int num_pages) {
            this.num_pages = num_pages;
        }

        public double getPrice() {
            return price;
        }

        public void setPrice(double price) {
            this.price = price;
        }

        public String getAuthorString() {
            String auths = "";
            for (String auth : this.getAuthors()) {
                auths += auth;
                auths += ",";
            }
            return auths.substring(0, auths.length() - 1);
        }

        public void printBookDetails() {
            if (this != null) {
                System.out.println("Title: " + this.getTitle());
                System.out.println("Publisher: " + this.getPublisher());
                System.out.println("Authors: " + this.getAuthorString());
                System.out.println("Number of pages: " + this.getNum_pages());
                System.out.println("Price: " + this.getPrice());
            }
        }
    }

    static class Library {
        private Book[] books;
        private int idx, lim;

        public Library(int num) {
            lim = num;
            idx = -1;
            books = new Book[lim];
        }

        public void add(Book b) {
            if (idx == -1) {
                // library is empty
                books[++idx] = b;
                System.out.println("Book added successfully: " + b.getTitle());
            } else {
                int flag = 0;
                for (int i = 0; i <= idx; i++) {
                    if (books[i] == null) {
                        books[i] = b;
                        flag = 1;
                        System.out.println("Book added successfully: " + b.getTitle());
                        break;
                    }
                }
                if (flag == 0) {
                    // no intermediate space left
                    if (idx < lim - 1) {
                        books[++idx] = b;
                        System.out.println("Book added successfully: " + b.getTitle());
                    } else {
                        // library is full
                        System.out.println("Library is full !");
                    }
                }
            }
        }

        public void delete(String title) {
            if (idx == -1) {
                System.out.println("Library is empty !");
            } else {
                int flag = 0;
                for (int i = 0; i < lim; i++) {
                    if (books[i] != null && title.equalsIgnoreCase(books[i].getTitle())) {
                        books[i] = null;
                        flag = 1;
                        System.out.println("Book deleted successfully: " + title);
                        break;
                    }
                }
                if (flag == 0) {
                    System.out.println("Title not found !");
                }
            }
        }

        public void printLibrary() {
            System.out.println("\n ---------------------------LIBRARY------------------------------------\n");
            for (int i = 0; i < this.lim; i++) {
                if (this.books[i] != null) {
                    this.books[i].printBookDetails();
                    System.out.println();
                }
            }
            System.out.println("\n\n");
        }

        public double totalPriceLibrary() {
            double tot = 0.0;
            for (int i = 0; i < lim; i++) {
                if (books[i] != null)
                    tot += books[i].getPrice();
            }
            return tot;
        }
    }

    public static void main(String[] args) {
        String a1[] = { "Chinua Achebe" };
        String a2[] = { "Arundhati Roy" };
        String a3[] = { "Toni Morrision" };
        String a4[] = { "Margaret Atwood"};
        String a5[] = { "Cormac McCarthy" };
        String a6[] = { "Rohinton Mistry" };
        String a7[] = { "Sir Arthur C. Doyle" };
        String a8[] = { "J. K. Rowling" };

        Book b1 = new Book("Things Fall Apart", "Penguin Publishers", a1, 1050, 700);
        Book b2 = new Book("The God of Small Things", "Bloomsbury", a2, 378, 400);
        Book b3 = new Book("Beloved", "Springer", a3, 538, 300);
        Book b4 = new Book("The Handmaid's Tale", "Vintage Publications", a4, 340, 525);
        Book b5 = new Book("Blood Meridian", "Picador Classics", a5, 825, 340);
        Book b6 = new Book("A Fine Balance", "Penguin Publishers", a6, 850, 940);
        Book b7 = new Book("The Complete Sherlock Holmes", "Vintage Classics", a7, 994, 149.00);
        Book b8 = new Book("Harry Potter and the Half Blood Prince", "Bloomsbury", a8, 490, 799);

        Library lib = new Library(10);
        lib.add(b1);
        lib.add(b2);
        lib.add(b3);
        lib.add(b4);

        lib.printLibrary();

        lib.delete("Blood Meridian");
        lib.add(b5);
        lib.add(b6);

        lib.printLibrary();

        lib.delete("Things Fall Apart");
        lib.delete("Beloved");
        lib.add(b7);
        lib.add(b8);
        lib.delete("A Fine Balance");

        lib.printLibrary();

        // print total price of all books
        System.out.println("Total price of all books in library at current time = " + lib.totalPriceLibrary());
    }
}
