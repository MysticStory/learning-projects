package com.example;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int numberOfNumbers = inputNumber(scanner);
            if (numberOfNumbers > 0) {
                int[] array = enterArray(numberOfNumbers, scanner);
                printAvgNegativeNumbers(array);
            } else {
                System.out.println("Input error. Size <= 0");
            }
        }
    }

    private static void printAvgNegativeNumbers(int[] array) {
        int countNegativeNumber = 0;
        int sumNegativeNumber = 0;

        for (int element : array) {
            if (element < 0) {
                ++countNegativeNumber;
                sumNegativeNumber += element;
            }
        }
        if (countNegativeNumber != 0) {
            System.out.println(sumNegativeNumber / countNegativeNumber);
        } else {
            System.out.println("There are no negative elements");
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