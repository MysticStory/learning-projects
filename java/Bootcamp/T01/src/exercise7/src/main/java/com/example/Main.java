package com.example;


import java.io.*;
import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (Scanner file_scanner = new Scanner(System.in)) {
            File file = new File(file_scanner.nextLine());
            try (Scanner read_scanner = new Scanner(file)) {
                read_scanner.useLocale(Locale.US);
                int size = readSize(read_scanner);
                if (size > 0) {
                    fileProcessing(size, read_scanner, file);
                } else {
                    System.out.println("Input error. Size <= 0");
                }
            } catch (FileNotFoundException e) {
                System.out.println("Input error. File isn't exist");
            }
        }
    }

    private static void fileProcessing(int size, Scanner read_scanner, File file) {
        double[] array = new double[size];
        int readingSize = readArray(read_scanner, array);
        if (readingSize == size) {
            String path_result = file.toPath().getParent().toString() + "/result.txt";
            saveMinMax(array, path_result);
            System.out.println(size);
            printArray(array);
            System.out.println("Saving min and max values in file");

        } else {
            System.out.println("Input error. Insufficient number of elements");
        }
    }

    private static void saveMinMax(double[] array, String path_result) {
        double min = array[0];
        double max = array[0];
        for (double element : array) {
            if (element < min) min = element;
            if (element > max) max = element;
        }
        try (FileWriter writer = new FileWriter(path_result, false)) {
            writer.write(String.valueOf(min) + " " + String.valueOf(max) + "\n");
            writer.flush();
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }

    }

    private static void printArray(double[] array) {
        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i]);
            if (i < array.length - 1) System.out.print(" ");
        }
        System.out.println();
    }

    private static int readSize(Scanner scanner) {
        while (scanner.hasNext()) {
            if (scanner.hasNextInt()) {
                return scanner.nextInt();
            } else {
                scanner.next();
            }
        }
        return -1;
    }

    private static int readArray(Scanner scanner, double[] array) {
        int index = 0;
        while (scanner.hasNext()) {
            if (scanner.hasNextDouble()) {
                array[index] = scanner.nextDouble();
                ++index;
            } else {
                scanner.next();
            }
        }
        return index;
    }
}