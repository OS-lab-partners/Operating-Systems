// COSC 439-003
// FCFC and RR scheduling algorithms

// used for process queue
import java.util.Queue;
import java.util.Random;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.io.*;

/*
 * The Process class definition
 */
class Process {

    // Declare Process class variables
    String name;
    int arrivalTime;
    int burstTime;
    int waitTime;
    int termTime;

    // Process constructor
    public Process(String n, int arrival, int burst) {
        name = n;
        arrivalTime = arrival;
        burstTime = burst;
        waitTime = 0;
        termTime = 0;
    }

    public String toString() {
        return name + " - arrival time: " + arrivalTime + " & burst time: " + burstTime;
    }
}

public class lab4 {
   

    public static void main(String args[]) {
        System.out.println("Current working directory: "+new File(".").getAbsolutePath());

        System.out.println(
                "\n************************************** PROCESS SCHEDULING SIMULATION **************************************\n");

        Queue<Process> processQueue = new LinkedList<Process>();

        Scanner input = new Scanner(System.in);
        int choice = 0;

        System.out.println("SELECT AN OPTION");
        System.out.println("1) Load processes from file");
        System.out.println("2) Enter your own");
        System.out.println("Please Enter 1 or 2");

        if (input.hasNextInt()) {
            choice = input.nextInt();
        } else {
            input.next();
            System.out.println("Invalid input. Please Enter \"1\" for option 1 or \"2\" for option 2");
        }

        while (choice < 1 || choice > 2) {
            System.out.print("\nSelect option 1 or 2");
            choice = input.nextInt();
        }

        switch (choice) {
            case 1:
                processQueue = loadByFile();
                break;
            case 2:
                processQueue = getUserInput();
                break;
        }

        // sort process arrival time
        processQueue = sortProcesses(processQueue);

        // will simulate FCFS
        FCFS(processQueue);

        // round robin
        roundRobin(processQueue);

        input.close();
    }

    public static Queue<Process> loadByFile() {

        Queue<Process> queue = new LinkedList<>();
        // int arrival;
        // int burst;
        // String file =
        // "/Users/novoachampion/Documents/GitHub/Operating-Systems/lab-4/file/input.txt";
        String file = "input.txt";
        int i = 0;

        try (Scanner scanner = new Scanner(new File(file))) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] nums = line.split(" ");
                int arrival = Integer.parseInt(nums[0]);
                int burst = Integer.parseInt(nums[1]);
                Process process = new Process("P" + i, arrival, burst);
                queue.offer(process);
                i++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return queue;
    }

    /*
     * Prompts user for number of processes and randomly generates arrival and burst
     * times
     */
    public static Queue<Process> getUserInput() {
        Scanner input = new Scanner(System.in);
        System.out.print("How many processes need to be entered (between 0 and 20):");
        int numProcesses = 0;
        // int arrival;
        // int burst;

        if (input.hasNextInt()) {
            numProcesses = input.nextInt();
        } else {
            input.next();
            System.out.println("Invalid input. Please enter a number (between 0 and 20");
        }

        while (numProcesses < 0 || numProcesses > 20) {
            System.out.print("\nProcess number must be between 0 and 20: ");
            if (input.hasNextInt()) {
                numProcesses = input.nextInt();
            } else {
                input.next();
                System.out.println("Invalid input. Please enter a number (between 0 and 20:");
            }
        }

        Queue<Process> queue = new LinkedList<>();

        System.out.println("\nRandomly generating arrival & burst times . . .");

        Random random = new Random();

        for (int i = 0; i < numProcesses; i++) {
            // Generate random arrival and burst times for each process
            int arrival = random.nextInt(100);
            int burst = random.nextInt(50);

            // Create a new Process and add it to the queue
            Process process = new Process("P" + i, arrival, burst);
            queue.offer(process);
        }

        input.close();
        return queue;
    }

    /*
     * Sorts processes by arrival time
     */
    public static Queue<Process> sortProcesses(Queue<Process> queue) {

        // convert the Queue to a List
        List<Process> processList = new ArrayList<>(queue);

        // create a custom comparator based on the arrival time
        Comparator<Process> arrivalComparator = Comparator.comparingInt(process -> process.arrivalTime);

        // sort the list using the custom comparator
        Collections.sort(processList, arrivalComparator);

        // convert the sorted list back to a queue
        Queue<Process> sortedQueue = new LinkedList<>(processList);

        // continue to print queue head until queue is empty
        for (Process p : processList) {
            System.out.println(p);
        }
        return sortedQueue;
    }

    // will simulate FCFS
    public static void FCFS(Queue<Process> processQueue) {

    }

    // will simulate roundrobin
    public static void roundRobin(Queue<Process> processQueue) {

    }

}
