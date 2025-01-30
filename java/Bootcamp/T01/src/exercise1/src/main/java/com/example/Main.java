package com.example;

import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        double[] coordinatesPoints = new double[6];
        int index = 0;
        try (Scanner scanner = new Scanner(System.in)) {
            scanner.useLocale(Locale.US);
            while (index < 6) {
                coordinatesPoints[index] = inputDouble(scanner);
                ++index;
            }
        }

        double side_a = calcSideLength(coordinatesPoints[0], coordinatesPoints[1], coordinatesPoints[2], coordinatesPoints[3]);
        double side_b = calcSideLength(coordinatesPoints[2], coordinatesPoints[3], coordinatesPoints[4], coordinatesPoints[5]);
        double side_c = calcSideLength(coordinatesPoints[0], coordinatesPoints[1], coordinatesPoints[4], coordinatesPoints[5]);

        if (isTriangle(side_a, side_b, side_c)) {
            System.out.printf("Perimeter: %.3f%n", side_a + side_b + side_c);
        } else {
            System.out.println("It isn't triangle");
        }

    }

    private static double calcSideLength(double x1, double y1, double x2, double y2) {
        return Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
    }

    private static boolean isTriangle(double a, double b, double c) {
        return a + b > c && b + c > a && a + c > b;
    }

    private static double inputDouble(Scanner scanner) {
        double number;
        while (true) {
            if (scanner.hasNextDouble()) {
                number = scanner.nextDouble();
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