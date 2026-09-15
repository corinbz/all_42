# Philosophers

![42](https://img.shields.io/badge/42-project-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-brightgreen?style=flat-square)

A classic implementation of the dining philosophers problem using
POSIX threads and mutexes: `N` philosophers sit around a table with `N`
forks (one mutex per fork), and must alternately think, eat and sleep
without starving or deadlocking.

## Usage

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
# e.g.
./philo 5 800 200 200
```

- `number_of_philosophers`: also the number of forks.
- `time_to_die` (ms): if a philosopher doesn't start eating within this
  window of their last meal, they die and the simulation stops.
- `time_to_eat` / `time_to_sleep` (ms): how long a philosopher holds both
  forks / sleeps for, each cycle.
- Optional `number_of_times_each_philosopher_must_eat`: simulation stops
  successfully once every philosopher has reached this count.

## Design

- One `pthread_t` per philosopher (`philo_routine`), plus one dedicated
  monitor thread (`monitor_routine`) that watches every philosopher's
  `last_meal_time` and flags `stop_simulation` if anyone starves.
- One `pthread_mutex_t` per fork (`forks_mut`), taken in a consistent
  order to avoid deadlock; a `print_mut` serializes status output so
  messages from different threads don't interleave; `stop_sim_mut` /
  `last_meal_time_mut` guard the shared stop flag and per-philosopher
  timestamp against data races.
- Timing (`get_current_time`, `ft_usleep`) uses `gettimeofday`, in
  milliseconds, with a busy-wait-friendly sleep loop precise enough to
  avoid false-positive deaths.

## Build

```sh
cd philo
make        # builds philo
make clean
make fclean
make re
```

## Files (`philo/`)

| File | Role |
|------|------|
| `main.c` | Entry point |
| `init_data.c` / `init_philos.c` | Build the shared `t_data` and per-philosopher `t_philo` structures, init mutexes |
| `parsing_utils.c` | Argument validation |
| `start_sim.c` | Spawns philosopher + monitor threads |
| `philo_routine.c` | Per-philosopher loop: think, take both forks, eat, sleep |
| `monitor_routine.c` | Starvation watchdog / meal-count win condition |
| `print_utils.c` | Thread-safe, timestamped status printing |
| `time_utils.c` | Millisecond clock and sleep helpers |
| `memory_utils.c` / `cleanup.c` | Allocation and mutex teardown |
| `philos.h` | `t_data` / `t_philo` structs and prototypes |
