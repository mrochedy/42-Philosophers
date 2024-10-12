# 42-Philosophers, by Maxime Rochedy

Welcome to my implementation of **Philosophers**, a core project completed as part of my studies at **École 42**. This project explores key concurrency concepts, inspired by the **Dining Philosophers problem**, and earned a top score of **125/100**, with all **bonus features** fully implemented.

In this repository, you’ll find my complete version of the **Philosophers** project, carefully crafted and evaluated by peers. While I aimed to make this solution as bug-free as possible, challenges in concurrency are always complex, and feedback is greatly appreciated.

<img width="198" alt="125/100 grade" src="https://github.com/user-attachments/assets/708486c1-c045-40d6-ab0c-e5dc3650a50d">

## About the Project

This repository offers a **comprehensive implementation** of the **Philosophers** project from the 42 curriculum. The project is designed to help students understand complex concurrency issues, including synchronization, deadlocks, and efficient resource sharing in C. It was coded by **Maxime Rochedy** under the login **mrochedy**.

The project involves simulating the classic **Dining Philosophers problem**, which uses multiple threads and shared resources (forks). The goal is to prevent deadlocks and ensure all philosophers can eat without conflict. My solution includes both the **mandatory** and **bonus** parts, where I transformed the threads into **processes**, and replaced **mutexes** with **semaphores**, diving deep into a lesser-documented and highly challenging aspect of this project.

Please note that while this repository is available for **learning purposes**, it should not be copied for personal submissions. Use this responsibly to enhance your understanding of parallel programming and inter-process communication. Please respect **École 42**'s policies on plagiarism.

## Implementation Details

One of the standout aspects of this project is the **bonus** implementation, which involved some of the most challenging changes, requiring a shift in both the **concurrency model** and the **communication logic** between philosophers. While the mandatory part of the **Philosophers** project uses **threads** and **mutexes**, the bonus version required using **processes** and **semaphores** to manage synchronization and communication. Given the high number of resources explaining how to deal with the mandatory part, I decided not to do it, but to explain how I tackled the **bonus challenges**, especially given the scarcity of clear resources online. You can of course still go through my code or even submit an issue if you have any question.

### Sharing Information between Processes

For the bonus version, the challenge was to share information effectively between processes. The key difficulty was determining:

1. **Whether a philosopher has died**.
2. **Whether all philosophers have eaten sufficiently**.

Given that shared memory and signal handling were prohibited, I used two distinct approaches to handle these situations:

#### 1. Parent Detection

To determine whether a philosopher has died or if all philosophers have eaten enough, I used two semaphores:

- **`dead_sem`** initialized to 1.
- **`meals_count_sem`** initialized to `n`, where `n` is the number of philosophers.

Each philosopher **waits** on the corresponding semaphore if they either die or eat sufficiently. The challenge was for the **parent process** to detect whether any semaphore was "full" (meaning its value had reached 0). Here's how I approached this:

- In a loop, for each semaphore (`dead_sem` and `meals_count_sem`), I alternatively launched a **monitoring thread**. This thread would wait for a set time interval (20 times 50 microseconds).
- After launching the thread, I performed a **wait** on the semaphore. If the wait passes immediately, it means the semaphore isn’t full, and the monitoring thread is instructed to stop, indicating that no philosopher has died or that not all have eaten enough. In this case, I post the semaphore to reset its value and prevent blocking.
- If the thread completes the full wait time (indicating the semaphore is locked), it implies that a philosopher has either died or all have eaten sufficiently. In this case, I **post** the semaphore to unblock it, but now I also have the necessary information: one semaphore being full means action is needed by the parent process.

#### 2. Parent Communication to Philos

Once the **parent process** detects that either a philosopher has died or all philosophers have eaten enough, it must notify all philosophers to **stop**. To accomplish this, I used an additional semaphore called **`is_over_sem`**:

- **`is_over_sem`** was initialized to 1, and immediately **waited** to set its value to 0.
- Upon creating each philosopher process, I started a **thread** in each philosopher that attempted to wait on **`is_over_sem`**. Since its value was 0, all these threads remained blocked.
- When the main process detects the end condition (a death or all philosophers being fed), it **posts** on **`is_over_sem`**, allowing one of these threads to proceed and effectively signal that the philosopher should stop. This thread, after proceeding, **posts** the semaphore again so that all philosopher processes get the stop signal in turn.

### Conclusion

The bonus part of the **Philosophers** project is considered one of the **most difficult** to complete during the common core at **42** due to the substantial changes required in the underlying logic and the lack of comprehensive tutorials online. The switch from **threads** to **processes** and the replacement of **mutexes** with **semaphores** requires a different mindset for managing concurrent operations, especially without the luxury of shared memory. I made my best trying to **vulgarize** the techniques I used, but if you feel like you're still missing on something, please get a look at my code or feel free to create an **issue** so I can try to directly help you on your problem. I also know there are probably easier ways to tackle the bonus part so any **recommendation** would be highly appreciated.

## Getting Started

To run this project:

```bash
git clone https://github.com/mrochedy/42-Philosophers.git
cd 42-Philosophers
cd philo
make
```

For the **bonus** version, which features philosophers implemented as processes:

```bash
cd philo_bonus
make
```

To launch it, this format is required:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers and also the number of forks.
- `time_to_die`(in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

Please be aware that the program, either mandatory or bonus, can experience weird behaviors for more than dozens of philosophers.

## Contributing

If you found this repository useful, please feel free to ⭐️ **star** ⭐️ the project to support its visibility. Contributions are welcome through pull requests, particularly regarding additional **documentation** or improvements, but please do not submit this code as your own in any official 42 projects.

Thank you for visiting this repository, and happy coding with **Philosophers**!
