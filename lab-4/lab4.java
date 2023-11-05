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
        
        System.out.println("\n************************************** PROCESS SCHEDULING SIMULATION **************************************\n");

        Queue<Process> processQueue = new LinkedList<Process>();

        System.out.println("SELECT AN OPTION");
        System.out.println("1) Load processes from file");
        System.out.println("2) Enter your own");

        Scanner input = new Scanner(System.in);
        int choice = input.nextInt();

        while(choice < 1 || choice > 2) {
            System.out.print("\nSelect option 1 or 2");
            choice = input.nextInt();
        }

        switch (choice){
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
        int arrival;
        int burst;
        String file = "input.txt";
        int i = 0;

        try (Scanner scanner = new Scanner(new File(file))) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] nums = line.split(" ");
                arrival = Integer.parseInt(nums[0]);
                burst = Integer.parseInt(nums[1]);
                Process process = new Process("P"+i, arrival, burst);
                queue.offer(process);
                i++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return queue;
    }

    /*
     * Prompts user for number of processes and randomly generates arrival and burst times
     */
    public static Queue<Process> getUserInput() {
              
        int numProcesses;
        int arrival;
        int burst;

        Scanner input = new Scanner(System.in);
        System.out.print("How many processes need to be entered: ");
        numProcesses = input.nextInt();

        while(numProcesses < 0 || numProcesses > 20) {
            System.out.print("\nProcess number must be between 0 and 20: ");
            numProcesses = input.nextInt();
        }

        Queue<Process> queue = new LinkedList<>();

        System.out.println("\nRandomly generating arrival & burst times . . .");

        Random random = new Random();

        for (int i = 0; i < numProcesses; i++) {
            // Generate random arrival and burst times for each process
            arrival = random.nextInt(100);
            burst = random.nextInt(50);

            // Create a new Process and add it to the queue
            Process process = new Process("P"+i, arrival, burst);
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

        // Queue<Process> printQueue = sortedQueue;
        // // continue to print queue head until queue is empty
        // while (!printQueue.isEmpty()) {
        //     System.out.println(printQueue.poll());
        // }
        return sortedQueue;
    }

    //will simulate FCFS
    public static void FCFS(Queue<Process> processQueue) {
        int currentTime = processQueue.peek().arrivalTime; // current time starts at 0
        while(!processQueue.isEmpty()) { // process are already in order of arrival\
            // get the first process from the queue
            Process currentProcess = processQueue.poll();
            // for debugging
            System.out.println(currentProcess.toString());
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
            System.out.println(currentProcess.name + " is executing.\nWait time: " + currentProcess.waitTime + "\nTermination time: " + currentProcess.termTime + "\n");

            // start execution of next process
            currentTime = currentProcess.termTime;
        }

    }
    
    //will simulate roundrobin
    public static void roundRobin(Queue<Process> processQueue) {
        
    }
    
}


