package com.example;

import java.nio.channels.ScatteringByteChannel;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        long timeSeconds = -1;
        int[] TimeHHMMSS = new int[3];
        try (Scanner scanner = new Scanner(System.in)) {
            timeSeconds = inputNumber(scanner);
        }
        TimeHHMMSS = calcTimeHHMMSS(timeSeconds);
        printTime(TimeHHMMSS);
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

    private static int[] calcTimeHHMMSS(long timeSeconds) {
        int[] TimeHHMMSS = new int[3];
        if (timeSeconds < 0) {
            TimeHHMMSS[0] = -1;
        } else {
            TimeHHMMSS[0] = (int) (timeSeconds / 3600 % 24);
            TimeHHMMSS[1] = (int) (timeSeconds / 60 % 60);
            TimeHHMMSS[2] = (int) (timeSeconds % 60);
        }
        return TimeHHMMSS;
    }

    private static void printTime(int[] TimeHHMMSS) {
        if (TimeHHMMSS[0] < 0) {
            System.out.println("Incorrect time");
        } else {
            System.out.printf("%02d:%02d:%02d", TimeHHMMSS[0], TimeHHMMSS[1], TimeHHMMSS[2]);
        }
    }
}