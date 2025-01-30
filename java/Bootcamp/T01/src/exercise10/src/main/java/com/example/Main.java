package com.example;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        List<User> users = new ArrayList<>();
        try (Scanner scanner = new Scanner(System.in)) {
            readUsers(users, scanner);
            List<User> only18plus = users.stream()
                    .filter(user -> user.getAge() >= 18)
                    .toList();
            printUsersName(only18plus);
        }
    }

    private static void readUsers(List<User> users, Scanner scanner) {
        int size = inputNumber(scanner);
        int index = 0;
        while (index < size) {
            String name = scanner.nextLine();
            int age;
            if (scanner.hasNextInt()) {
                age = scanner.nextInt();
                scanner.nextLine();
            } else {
                System.out.println("Couldn't parse a number. Please, try again");
                scanner.nextLine();
                continue;
            }
            if (age <= 0) {
                System.out.println("Incorrect input. Age <= 0");
            } else {
                users.add(new User(name, age));
                index++;
            }
        }
    }

    private static void printUsersName(List<User> Users) {
        for (int i = 0; i < Users.size(); ++i) {
            System.out.print(Users.get(i).getName().trim());
            if (i < Users.size() - 1)
                System.out.print(", ");
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