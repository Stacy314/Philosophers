# 🧠 Philosophers

## 🗒️ Summary

The **Philosophers** project is a classic concurrency problem implemented in C using **threads** and **mutexes**. The goal is to simulate a number of philosophers sitting around a table, alternating between eating, sleeping, and thinking—all while competing for limited forks (resources).

This project is part of the 42 School curriculum and focuses on the use of **pthread** and **synchronization mechanisms** to avoid common concurrency pitfalls such as **deadlocks** and **race conditions**.

---

## 📦 Project Structure

- `philo/` – The directory containing all source files.
- `Makefile` – To compile the program with required rules (`all`, `clean`, `fclean`, `re`).
- `philo` – Executable file generated after compilation.

---

## 🔧 Compilation

To compile the project:

```bash
make
```
To recompile from scratch:

```bash
make re
```
To clean object files:

```bash
make clean
```
To remove everything including the executable:

```bash
make fclean
```
## 🧪 Usage
Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Arguments:
- number_of_philosophers – Total number of philosophers and forks.

- time_to_die – Time (in milliseconds) a philosopher can survive without eating.

- time_to_eat – Time (in milliseconds) it takes for a philosopher to eat.

- time_to_sleep – Time (in milliseconds) a philosopher spends sleeping.

- number_of_times_each_philosopher_must_eat (optional) – If specified, simulation ends when each philosopher has eaten this many times.

Example:
```bash
./philo 5 800 200 200
```
This starts 5 philosophers who die if they don’t eat for 800ms, take 200ms to eat, and sleep for 200ms.

## 🧵 Implementation Details
- Each philosopher is implemented as a thread.

- Forks are protected by mutexes to prevent concurrent access.

- Logging is synchronized to avoid interleaved output.

- Timestamps are displayed in milliseconds since the start of the simulation.

## 🧠 Philosopher Lifecycle
Each philosopher follows this routine in a loop:

- Think

- Pick up left and right forks

- Eat

- Put down both forks

- Sleep

## 📋 Output Format
All actions are printed to the console in the following format:

```bash
[timestamp_in_ms] [philosopher_number] is [action]
```
Example:

```bash
235 1 is thinking
236 1 has taken a fork
237 1 has taken a fork
238 1 is eating
```
## 💀 Death Condition
If a philosopher doesn’t start eating before time_to_die expires since their last meal, they die and the simulation ends immediately. The output will show:

```bash
[time] [philo_id] died
```
This message must appear within 10ms of the actual time of death.

## 🚫 Rules & Restrictions
- No global variables.

- No data races (ensure thread-safe behavior).

- You must use pthread and mutexes to control access to forks.

- Libft is not allowed in this project.

## ✅ Evaluation Checklist
- Correct thread creation and synchronization

- No deadlocks or starvation

- Clean output formatting

- Proper error handling

- Norm-compliant code

- No memory leaks (checked via valgrind or similar)

## 📚 Useful Concepts
- Threads (pthread_create, pthread_join)

- Mutexes (pthread_mutex_*)

- Timestamps (gettimeofday)

- Concurrency control

- Synchronization

- Deadlock prevention

## 🧠 About
This project simulates a philosophical dilemma where thinking too long without a fork can be fatal.

“I never thought philosophy would be so deadly.”

