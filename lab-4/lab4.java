// COSC 439-003
// FCFC and RR scheduling algorithms

// Group Members:
// Shannon Ioffe
// Novoa Champion
// Katherine Lim

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
        return name + " - arrival time = " + arrivalTime + ", burst time = " + burstTime;
    }
}

public class lab4 {
    public static void main(String args[]) {

        System.out.println(
                "\n************************************** PROCESS SCHEDULING SIMULATION **************************************\n");

        Queue<Process> processQueue = new LinkedList<Process>();

        Scanner input = new Scanner(System.in);
        int choice;

        System.out.println("SELECT AN OPTION\n");
        System.out.println("1) Load processes from file");
        System.out.println("2) Enter your own");
        choice = input.nextInt();

        while (choice < 1 || choice > 2) {
            System.out.print("\nPlease enter 1 or 2:\n");
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

        System.out.println("\nProcesses loaded:\n");
        for (Process p : processQueue) {
            System.out.println(p);
        }

        // sort processes in order of their arrival time
        processQueue = sortProcesses(processQueue);

        System.out.println("\nSELECT A SCHEDULING ALGORITHM:\n");
        System.out.println("1) First Come First Serve (FCFS)");
        System.out.println("2) Round Robin\n");
    
        choice = 0;
        while(choice < 1 || choice > 2){
            System.out.print("\nPlease enter 1 or 2:\n");
            choice = input.nextInt();
        }
    
        switch (choice) {
            case 1:
                FCFS(processQueue);
                break;
            case 2:
                roundRobin(processQueue);
                break;
        }
        
        System.out.println("\nEnd of process queue.\n");
        input.close();
    }

    public static Queue<Process> loadByFile() {
        
        System.out.println("\nLoading file . . .");

        Queue<Process> queue = new LinkedList<>();

        int arrival;
        int burst;
        String file = "input.txt";

        // set the process no.
        int i = 1;

        try (Scanner scanner = new Scanner(new File(file))) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                // Read ints delineated by spaces
                String[] nums = line.split(" ");
                arrival = Integer.parseInt(nums[0]);
                burst = Integer.parseInt(nums[1]);
                Process process = new Process("P" + i, arrival, burst);
                queue.offer(process);
                i++;
            }
            scanner.close();
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
        
        int numProcesses = 0;
        int arrival;
        int burst;

        Scanner input = new Scanner(System.in);
        System.out.print("\nHow many processes do you need (between 0 and 20): \n");
        numProcesses = input.nextInt();

        while (numProcesses < 1 || numProcesses >= 20) {
            System.out.print("\nMust be a number greater than zero and less than 20: \n");
            numProcesses = input.nextInt();
        }

        Queue<Process> queue = new LinkedList<>();

        Random random = new Random();

        for (int i = 0; i < numProcesses; i++) {
            // Generate random arrival and burst times for each process
            arrival = random.nextInt(100);
            burst = random.nextInt(50);

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
        System.out.println("\nSort processes in order of arrival time:\n");
        for (Process p : processList) {
            System.out.println(p);
        }
        return sortedQueue;
    }

    /*
     * First Come First Serve scheduler
     */
    public static void FCFS(Queue<Process> processQueue) {

        System.out.println(
        "\n************************************** FIRST COME FIRST SERVE (FCFS) **************************************\n");

        int currentTime = processQueue.peek().arrivalTime; // current time starts at 0
        while(!processQueue.isEmpty()) { // process are already in order of arrival

            // get the first process from the queue
            Process currentProcess = processQueue.poll();

            // check to see if any processes are still executing
            // if no processes are executing then jump to arrival time
            // of the current process (wait time will be 0)
            if (currentTime < currentProcess.arrivalTime) {
                currentTime = currentProcess.arrivalTime;
            }

            // calculate the process WT and TT
            currentProcess.waitTime = currentTime - currentProcess.arrivalTime;
            currentProcess.termTime = currentTime + currentProcess.burstTime;
            
            // print results
            System.out.println(currentProcess.name + " is executing . . .\nWait time: " + currentProcess.waitTime + "\nTermination time: " + currentProcess.termTime + "\n");

            // start execution of next process
            currentTime = currentProcess.termTime;
        }
    }

    /*
     * Round Robin scheduler
     */
    public static void roundRobin(Queue<Process> processQueue) {
        int timeQuantum = 0;
        System.out.println("\n************************************** ROUND ROBIN **************************************\n");
    
        Scanner input = new Scanner(System.in);

        System.out.println("\nGive a time slice between 1 and 100 milliseconds: \n");
        timeQuantum = input.nextInt();

        while(timeQuantum < 1 || timeQuantum > 100){
            System.out.println("\nPlease enter a valid time slice\n");
            timeQuantum = input.nextInt();
        }

        Queue<Process> queue = new LinkedList<>(processQueue);
        int currentTime = 0;
    
        while (!queue.isEmpty()) {
            Process currentProcess = queue.poll();

            if (currentProcess.burstTime > timeQuantum) {
                // Execute the process for the time quantum
                currentTime += timeQuantum;
                currentProcess.burstTime -= timeQuantum;
                // Re-add the process to the end of the queue
                queue.add(currentProcess);
            } else {
                // Execute the remaining burst time
                currentTime += currentProcess.burstTime;
                currentProcess.termTime = currentTime;
                currentProcess.waitTime = currentProcess.termTime - currentProcess.arrivalTime;
            }
            System.out.println(currentProcess.name + " is executing. . .");
        }
    
        for (Process process : processQueue) {
            System.out.println("\n" + process.name + "\nWait time: " + Math.max(0, process.waitTime) + "\nTermination time: " + process.termTime + "\n");
        }
        
        input.close();
    }
}

