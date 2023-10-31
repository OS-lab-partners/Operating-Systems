// COSC 439-003
// FCFC and RR scheduling algorithms

// used for process queue
import java.util.Queue;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

class Process {
    String name;
    int arrivalTime;
    int burstTime;
    int waitTime;
    int termTime;

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
        Queue<Process> processQueue = new LinkedList<>();
        processQueue = getUserInput();
        // sort process arrival time
        processQueue = sortProcesses(processQueue);
    }

    public static Queue<Process> getUserInput() {
        Queue<Process> queue = new LinkedList();
        int numProcesses = 0;
        int arrival;
        int burst;
        Scanner input = new Scanner(System.in);
        System.out.print("How many processes need to be entered: ");
        numProcesses = input.nextInt();
        while(numProcesses < 0 || numProcesses > 20) {
            System.out.print("\nProcess number must be between 0 and 20: ");
            numProcesses = input.nextInt();
        }
        
        for(int i = 0; i < numProcesses; i++) {
                System.out.print("Enter arrival time for P" + (i + 1) + ": ");
                arrival = input.nextInt();
                System.out.print("Enter burst time for P" + (i + 1) + ": ");
                burst = input.nextInt();
                queue.add(new Process("P" + (i + 1), arrival, burst));
                System.out.println("------------------");
            }
        input.close();
        return queue;
    }

    public static Queue<Process> sortProcesses(Queue<Process> queue) {
        Queue<Process> temp = new LinkedList();

        // convert the Queue to a List
        List<Process> processList = new ArrayList<>(queue);

        // create a custom comparator based on the arrival time
        Comparator<Process> arrivalComparator = Comparator.comparingInt(process -> process.arrivalTime);

        // sort the list using the custom comparator
        Collections.sort(processList, arrivalComparator);

        // convert the sorted list back to a queue
        Queue<Process> sortedQueue = new LinkedList<>(processList);

        // DEBUGGING
        while (!sortedQueue.isEmpty()) {
            System.out.println(sortedQueue.poll());
        }
        return sortedQueue;
    }

    
    
    
}


