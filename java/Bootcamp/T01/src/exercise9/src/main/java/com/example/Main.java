package com.example;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        List<String> lines = new ArrayList<>();
        List<String> filteredLines = new ArrayList<>();
        String filterLine;
        try (Scanner scanner = new Scanner(System.in)) {
            readLines(lines, scanner);
            filterLine = scanner.nextLine();
        }
        filterLines(lines, filteredLines, filterLine);
        printLines(filteredLines);
    }

    private static void printLines(List<String> filteredLines) {
        for (int i = 0; i < filteredLines.size(); ++i) {
            System.out.print(filteredLines.get(i).trim());
            if (i < filteredLines.size() - 1)
                System.out.print(", ");
        }
    }

    private static void filterLines(List<String> lines, List<String> filteredLines, String filterLine) {
        for (String line : lines) {
            if (line.contains(filterLine)) {
                filteredLines.add(line);
            }
        }
    }

    private static void readLines(List<String> lines, Scanner scanner) {
        int size = inputNumber(scanner);
        for (int i = 0; i < size; i++) {
            lines.add(scanner.nextLine());
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
}