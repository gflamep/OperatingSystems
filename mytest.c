#include "types.h"
#include "user.h"
#include "stat.h"

// Function to perform a busy wait, simulating CPU work
void busy_wait(int duration) {
    volatile int i;
    for(i = 0; i < duration; i++) {
        ; // Do nothing, just loop
    }
}

int main() {
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
}
