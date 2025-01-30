package com.example;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int numberOfNumbers = inputNumber(scanner);
            if (numberOfNumbers > 0) {
                int[] array = enterArray(numberOfNumbers, scanner);
                int[] findingNumbers = new int[array.length];
                int size = findNumbers(array, findingNumbers);
                printArray(findingNumbers, size);
            } else {
                System.out.println("Input error. Size <= 0");
            }
        }
    }

    private static int findNumbers(int[] array, int[] findingNumbers) {
        int index = 0;
        for (int element : array) {
            if (isEqualsLastFirst(element)) {
                findingNumbers[index] = element;
                ++index;
            }
        }
        return index;
    }

    private static boolean isEqualsLastFirst(int number) {
        if (number < 0) number = -number;
        int first = number % 10;
        int last = first;
        while (number > 0) {
            last = number % 10;
            number /= 10;
        }
        return first == last;
    }

    private static void printArray(int[] array, int size) {
        if (size <= 0) {
            System.out.println("There are no such elements");
        } else {
            for (int i = 0; i < size; i++) {
                System.out.print(array[i]);
                if (i < size - 1) System.out.print(" ");
            }
        }
    }

    private static int[] enterArray(int size, Scanner scanner) {
        int[] array = new int[size];
        while (true) {
            int i = 0;
            for (; i < size && scanner.hasNextInt(); ++i) {
                array[i] = scanner.nextInt();
            }
            if (scanner.nextLine().trim().isEmpty() && i == size) {
                break;
            } else {
                System.out.println("Couldn't parse a number. Please, try again");
            }
        }
        return array;
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
}