#include <stdio.h>
#include<string.h>

char taskList[100][100];
int taskCount = 0;
    
int i=0;

void Initialize() {
    FILE *tasks = fopen("tasks.bin", "r");
    if (tasks != NULL) {
        // Read the last value of i from the file
        char line[100];
        while (fgets(line, sizeof(line), tasks) != NULL) {
            sscanf(line, "%d-", &i); // Update i with the last value in the file
        }
        fclose(tasks);
    }
}

void AddTask()
{
    if (taskCount < 100)
    {  printf("Enter your task: ");
        scanf("%s", taskList[taskCount]);
        taskCount++;
        printf("\nTask added successfully!\n");
        i++;
      FILE *tasks = fopen("tasks.bin","a");
      fprintf(tasks, "%d- %s \n",i,taskList[taskCount-1]);
      fclose(tasks);
     

    }

     else
      {
        printf("Task list is full. Cannot add more tasks.\n");
      }


}

void ShowTasks()
{
    FILE *tasks = fopen("tasks.bin","r");
    char line[256];
    while (fgets(line, sizeof(line), tasks))
    {
        printf("%s", line);
    }

    fclose(tasks);
}



void DeleteTask()
{

    FILE *tasks = fopen("tasks.bin","rb");
    char line[256];
    fseek(tasks, 0, SEEK_END);
    if(ftell(tasks)==0)
    {
        printf("There are no tasks in your task list!\n");

    }
    else
    {
    fseek(tasks,0,SEEK_SET);

        int taskNumber;
        printf("\nEnter the task number to delete: ");
        scanf("%d", &taskNumber);

        if (taskNumber >= 1 && taskNumber <= taskCount)
        {
            for (int i = taskNumber - 1; i < taskCount - 1; i++)
            {
                strcpy(taskList[i], taskList[i + 1]);
            }
            taskCount--;

            
            FILE *tasks = fopen("tasks.bin", "w");
            for (int j = 0; j < taskCount; j++)
            {
                fprintf(tasks, "%d- %s \n", j+1, taskList[j]);
            }
            fclose(tasks);
        }
    }
}




void EditTask()
{
    FILE *tasks = fopen("tasks.bin","rb");
    char line[256];
    fseek(tasks, 0, SEEK_END);
    if(ftell(tasks)==0)
    {
        printf("There are no tasks in your task list!\n");

    }
    
    else
    {
    fseek(tasks,0,SEEK_SET);

        printf("Enter the task number to edit: ");
        int taskNumber;
        scanf("%d", &taskNumber);
        if (taskNumber >= 1 && taskNumber <= taskCount)
        {
            printf("Enter the new task description: ");
            char newTask[100];
            scanf("%s", newTask);
            strcpy(taskList[taskNumber - 1], newTask);
            printf("Task edited successfully!\n");

            
            FILE *tasks = fopen("tasks.bin", "w");
            for (int j = 0; j < taskCount; j++)
            {
                fprintf(tasks, "%d- %s \n", j+1, taskList[j]);
            }
            fclose(tasks);
        }
    }
}



int main()
{
    Initialize();
    int choice;
    do {
        printf("\nSelect what you want to do!\n");
        printf("Enter your choice:\n");
        printf("1 => Add task\n");
        printf("2 => Show tasks\n");
        printf("3 => Delete task\n");
        printf("4 => Edit task\n");
        printf("5 => Quit\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                AddTask();
                break;
            case 2:
                ShowTasks();
                break;
            case 3:
                DeleteTask();
                break;
            case 4:
                EditTask();
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 5);

return 0;
}