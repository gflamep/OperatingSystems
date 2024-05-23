#include "types.h"
#include "user.h"
#include "stat.h"

#define NCHILDREN 3

void busy_wait(int duration) {
    volatile int i;
    for(i = 0; i < duration; i++) {
        if(i == duration/2) wait();
        ; // Do nothing, just loop
    }
}

int main() {
    /*
    int pid = getpid(); // Get the current process ID

    printf(1, "Process %d is starting with default nice value.\n", pid);
    printf(1, "Increasing CPU runtime with busy wait...\n");

    // Perform a busy wait to simulate CPU work and increase runtime
    busy_wait(500000000);
        ps(0);
    // Change the nice value to a higher priority and observe the difference
    if(setnice(pid, 5) < 0) {
        printf(2, "setnice call failed. Ensure system call is implemented correctly.\n");
    } else {
        printf(1, "Nice value of process %d set to 5. Performing more work...\n", pid);
    }


    // Perform more work with the new nice value
    busy_wait(500000000);
        printf(1, "\nFinal process states:\n");
        ps(0);
    printf(1, "Work done. Exiting...\n");
    exit();
    */


    int n, pid;

    printf(1, "Starting multitest with nice value adjustments...\n");

    for (n = 0; n < NCHILDREN; n++) {
        pid = fork();
        if (pid < 0) {
            printf(2, "fork failed\n");
            exit();
        }

        // Child process
        if (pid == 0) {
            // Set a unique nice value for each child
            int myNiceValue = n * 4; // Varies from 5 to 25
            setnice(getpid(), myNiceValue);
            printf(1, "Child %d (PID: %d) with nice value %d doing work...\n", n, getpid(), myNiceValue);
            busy_wait(500000000); // Vary duration to observe differences
            printf(1, "Child %d (PID: %d) finished work\n", n, getpid());
            ps(0);
            exit(); // Child exits
        }
    }

    // Parent process waits a bit before listing processes
    sleep(50); // Using sleep to give children time to start
    printf(1, "\nCalling ps() after setting nice values...\n");
    ps(0); // Assuming ps(0) lists all processes with their states

    // Parent waits for all children to complete
    for (n = 0; n < NCHILDREN; n++) {
        wait();
    }

    printf(1, "All children completed. Parent exiting.\n");

    ps(2);
    exit();

}