#include <iostream>
#include <vector>
#include <map>

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

TaskStatus &operator++(TaskStatus &ts) {
    int tmp = static_cast<int>(ts);
    ++tmp;
    ts = static_cast<TaskStatus>(tmp);
    return ts;
}

TaskStatus operator+(const TaskStatus &ts, int i) {
    int tmp = static_cast<int>(ts);
    tmp = tmp + i;
    return static_cast<TaskStatus>(tmp);;
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
private:
    std::map<std::string, TasksInfo> m_tasks;

    std::vector<TaskStatus> map_to_vector_tasks_status(const TasksInfo &m) {
        std::vector<TaskStatus> v;
        for (auto i : m) {
            while (i.second--) {
                v.push_back(i.first);
            }
        }
        return v;
    }

public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const std::string &person) const {
        return m_tasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const std::string &person) {
        ++m_tasks[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const std::string &person, int task_count) {

        auto prev_tasks = m_tasks[person];

        TasksInfo new_tasks;
        int cnt = task_count;
        for (auto st = TaskStatus::NEW; st != TaskStatus::DONE; ++st) {
            if (!cnt) break;
            new_tasks[st + 1] = std::min(cnt, prev_tasks[st]);
            cnt -= new_tasks[st + 1];
        }

        TasksInfo old_tasks;
        for (auto st = TaskStatus::NEW; st != TaskStatus::DONE; ++st) {
            old_tasks[st] = prev_tasks[st] - new_tasks[st + 1];
            prev_tasks[st] += new_tasks[st] - new_tasks[st + 1];
        }

        m_tasks[person] = prev_tasks;

        return {new_tasks, old_tasks};
    }
};

void PrintTasksInfo(TasksInfo tasks_info) {
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
              ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
              ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
              ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    std::cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    std::cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    /*
    Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
    Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
    Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done
    Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
    Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done
    Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done
     */
}
