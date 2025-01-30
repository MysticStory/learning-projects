package com.example;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        int numberFibonacci;
        try (Scanner scanner = new Scanner(System.in)) {
            numberFibonacci = inputNumber(scanner);
        }

        if (numberFibonacci <= 46) {
            System.out.println(Fibonacci(numberFibonacci));
        } else {
            System.out.println("Too large n");
        }


    }

    private static int inputNumber(Scanner scanner) {
        int number;
        while (true) {
            if (scanner.hasNextInt()) {
                number = scanner.nextInt();
                if (scanner.nextLine().trim().isEmpty()) {
                    break;
                }
            } else {
                if (scanner.hasNext()) scanner.nextLine();
            }
            System.out.println("Couldn't parse a number. Please, try again");
        }
        return number;
    }

    private static int Fibonacci(long i) {
        if (i <= 0) return 0;
        if (i == 1) return 1;
        if (i == 2) return 1;
        return Fibonacci(i - 1) + Fibonacci(i - 2);
    }
}