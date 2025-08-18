# Philosophers 🍝

## 📖 Overview
This project aims to explore the basics of **multithreading** and **synchronization** in C.  
The challenge is to implement the classic **Dining Philosophers Problem**, ensuring that philosophers can eat, sleep, and think without falling into **deadlock**, **starvation** or **race conditions**.

---

## 🤔 The Problem
- A group of philosophers sits at a round table.
- Each philosopher alternates between **eating**, **sleeping** and **thinking**.
- To eat, a philosopher needs **two forks**, one on the left and one on the right.
- The challenge is to manage these actions using **threads** and **mutexes** without causing:
  - Deadlocks
  - Starvation
  - Data races

---

## 📜 Mandatory Rules
- Each philosopher is represented by a **thread**.
- **Forks** are represented by **mutexes**.
- The simulation must stop if:
  - A philosopher dies (fails to eat within a given time).
  - All philosophers have eaten a minimum required number of times (if specified).

---

## ⚙️ Implementation Details 
This implementation uses the following strategy:

- **Odd and even philosophers** pick up forks in a different order
  - This alternating sequence prevents a circular waiting condition (classic cause of deadlocks).
- When the number of philosophers is **odd**, a small desynchronization (delay) is introduced so that not all philosophers try to pick up forks at the same time.  
  - This makes the simulation **fairer** and reduces the chance of starvation.

### ⏱️ Custom `usleep` Implementation
The default `usleep` function can introduce unwanted delays and reduce timing precision.  
To achieve more accurate control over the simulation, a **custom sleep function** was implemented:

- This ensures that the philosopher’s actions (`time_to_eat`, `time_to_sleep`, `time_to_die`) are respected with **higher precision**.

---

## 💻 Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

---

## 🔗 Resources
- [Oceano](https://www.youtube.com/watch?v=zOpzGHwJ3MU)
- [Zaynab Zakiyah](https://www.youtube.com/watch?v=VSkvwzqo-Pk)
- [André Carvalho](https://www.youtube.com/watch?v=g9zEqwSZd4o&t=519s)
- [Sah](https://www.youtube.com/watch?v=H2uAhD2qjKY)
- [Nem TI Conto](https://www.youtube.com/watch?v=hYD8raEyhSw)
