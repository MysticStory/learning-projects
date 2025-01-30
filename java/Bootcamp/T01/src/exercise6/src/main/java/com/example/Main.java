package com.example;

import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            scanner.useLocale(Locale.US);
            int numberOfNumbers = inputNumber(scanner);
            if (numberOfNumbers > 0) {
                double[] array = enterArray(numberOfNumbers, scanner);
                sort(array);
                printArray(array);

            } else {
                System.out.println("Input error. Size <= 0");
            }
        }
    }

    private static void sort(double[] array) {
        int n = array.length;
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) swap(array, i, minIndex);
        }
    }

    private static void swap(double[] array, int i, int j) {
        double tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    private static void printArray(double[] array) {
        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i]);
            if (i < array.length - 1) System.out.print(" ");
        }
    }

    private static double[] enterArray(int size, Scanner scanner) {
        double[] array = new double[size];
        while (true) {
            int i = 0;
            for (; i < size && scanner.hasNextDouble(); ++i) {
                array[i] = scanner.nextDouble();
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