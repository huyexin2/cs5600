#  Explore Synchronization Problem
##  Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University

The Dining Philosopher illustrates the concurrency problem of multiple processes sharing a limited set of resources to perform a task. The problem describes a group of philosophers sitting at a table either eating or thinking. The philosopher can only perform one of the two tasks at a time. The problem states that the philosophers are sitting at a round table, and each has spaghetti in front of them, however they would need a pair of chopsticks to eat the spaghetti. There is a single chopstick placed between two philosophers, to eat the spaghetti, the philosophers would need to pick up the chopsticks adjacent to them. Each chopstick may be picked up by any one of its adjacent followers but not both.

The most common solution to solve the concurrency problem is using semaphore, which is a mechanism that can be used to control access to shared resources. In this Dining Philosopher problem, the philosopher needs to get the left chopstick and the right chopstick and then start to eat. This mechanism requires philosopher to pick up both chopsticks or none of the chopsticks and avoid deadlock. A deadlock can happen when all of the philosophers pick up the chopsticks on their left-hand side and start to wait on the chopsticks on the right. In case a philosopher does not have access to both chopsticks, then the philosopher must wait until both chopsticks become available. 

In solving The Dining Philosopher, it would need a mutex to ensure the chopstick can only be picked up or release by one philosopher at a time and needs an array to control the behavior of the philosophers.

Below are the steps to solve the he Dining Philosopher using semaphores:
•    Begin by initializing semaphores to 1 to indicate its availability for each chopstick.
•    Initialize a binary semaphore (mutex) to 1 to control the philosophers’ behavior, ensuring that only one philosopher can attempt to pick up a chopstick at any given time.

Create an individual thread for each philosopher to execute the following:

•    While true:

o    The philosopher thinks for some time.
o    Acquire the mutex semaphore to ensure exclusive access for chopstick pickup attempts.
o    Try to acquire the semaphore for the left chopstick.
•    If successful, proceed to acquire the semaphore for the right chopstick.
•    If both forks are successfully acquired, dine for a random period and then release both semaphores.
•    In case of failure to acquire both chopsticks, release the left chopstick's semaphore (if acquired), release the mutex semaphore, and return to thinking.
•    Execute the philosopher threads concurrently, allowing them to dine and think while ensuring mutual exclusion during chopstick pickup attempts.

Reference:
Shenoy, Prashant, and Armand Halbert. "Dining Philosophers Problem Lecture 10." UMass Amherest, 7 Oct. 2013. Lecture.

Biswas, Subham. "Dining Philosopher Problem Using Semaphores." Geeksforgeeks, 23 Sept. 2023, www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/. Accessed 9 Oct. 2023.
