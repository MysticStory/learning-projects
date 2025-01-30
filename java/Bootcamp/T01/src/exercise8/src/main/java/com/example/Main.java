package com.example;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            if (scanner.hasNextInt()) {
                findSequence(scanner);
            } else {
                System.out.println("Input error");
            }
        }
    }

    private static void findSequence(Scanner scanner) {
        int sequenceLast = scanner.nextInt();
        int index = 1;
        while (scanner.hasNext()) {
            if (scanner.hasNextInt()) {
                int newElement = scanner.nextInt();
                if (newElement > sequenceLast) {
                    sequenceLast = newElement;
                    ++index;
                } else {
                    System.out.println("The sequence is not ordered from the ordinal number of the number " + index);
                    break;
                }
            } else {
                System.out.println("The sequence is ordered in ascending order");
                break;
            }
        }
    }
}