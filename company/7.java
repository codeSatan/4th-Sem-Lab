/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/**
 * 7) Implement a class for “Date”. Write member functions for (i) getting the
 * previous day, (iv) getting the next day, (iii) printing a day There should be
 * four constructors: (i) day, month and year are initialized to 01, 01, 1970;
 * (ii) day is initialized to user specified value but month and year are
 * initialized to 01, 1970; (iii) day, month are initialized to user specified
 * value but year is initialized to 1970; (iv) day, month and year are
 * initialized to user defined values. Also, write a main() function to (i)
 * create a date object; (ii) print the next and the previous day.
 */

class Main_Q7 {

    static class Date {

        private int day, month, year;

        private static int days_of_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        public Date() {
            this.day = this.month = 1;
            this.year = 1970;
        }

        public Date(int day) {
            this.day = day;
            this.month = 1;
            this.year = 1970;
        }

        public Date(int day, int month) {
            this.day = day;
            this.month = month;
            this.year = 1970;
        }

        public Date(int day, int month, int year) {
            this.day = day;
            this.month = month;
            this.year = year;
            if (Date.isLeap(year)) {
                days_of_month[2] = 29;
            }
        }

        Date getCurrentDate() {
            return this;
        }

        private static boolean isLeap(int yy) {
            // utility function to check leap year or not
            return (yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0);
        }

        Date getPreviousDay() {
            int dd = this.day, mm = this.month, yy = this.year;
            if (dd > 1) {
                --dd;
            } else if (mm > 1) {
                if (Date.isLeap(yy)) {
                    days_of_month[2] = 29;
                }
                dd = days_of_month[--mm];
            } else {
                // current date = 01/01/yyyy
                dd = 31;
                mm = 12;
                --yy;
            }
            return new Date(dd, mm, yy);
        }

        Date getNextDate() {
            int dd = this.day, mm = this.month, yy = this.year;
            if (Date.isLeap(yy)) {
                days_of_month[2] = 29;
            }
            if (mm == 12) {
                mm = dd = 1;
                ++yy;
            } else if (mm < 12 && dd == days_of_month[mm]) {
                dd = 1;
                ++mm;
            } else {
                ++dd;
            }
            return new Date(dd, mm, yy);
        }

        void printDate() {
            System.out.println(this.day + "/" + this.month + "/" + this.year);
        }

        public static void main(String[] args) {
            Date currDate = new Date(15, 3, 2021);
            Date prev = currDate.getPreviousDay();
            Date next = currDate.getNextDate();
            System.out.print("Current date: ");
            currDate.printDate();
            System.out.print("Previous date: ");
            prev.printDate();
            System.out.print("Next date: ");
            next.printDate();
        }
    }
}